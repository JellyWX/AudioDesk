#include "audiodesk.hpp"

AudioDesk::AudioDesk(int argc, char** argv, const std::string& name)
{
    this->setup_window = nullptr;
    this->main_window = nullptr;

    this->setup.start(&this->device_query);

    this->app = Gtk::Application::create(argc, argv, name);
}

void AudioDesk::run_setup()
{
    std::cout << "Default device not set or not found. Loading setup screen." << std::endl;

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("interfaces/setup.glade");

    builder->get_widget_derived("setup", this->setup_window);

    this->setup_window->set_application(this);
}

void AudioDesk::run_main()
{
    std::cout << "run_main: Checking existing devices" << std::endl;

    if (not device_query.device_exists("audiodesk_mixer.monitor"))
    {
        std::cout << "run_main: No device found. Running install_virtmic.sh" << std::endl;

        system("scripts/bash/install_virtmic.sh");
    }
    else
    {
        std::cout << "run_main: Devices already set up" << std::endl;
    }

    std::cout << "run_main: Generating a primary window" << std::endl;

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("interfaces/main.glade");

    builder->get_widget_derived("main", this->main_window);

    this->main_window->set_application(this);

    if ( this->read_sound_cache() and this->watch_sound_cache() )
    {
        Glib::signal_timeout().connect_seconds(
                sigc::mem_fun(*this, &AudioDesk::check_cache_events),
                5
                );
    }

    this->read_sound_api();
}

int AudioDesk::run()
{
    std::cout << "Entering run" << std::endl;

    this->run_main();

    if (this->setup.DEFAULT_DEVICE.empty())
    {
        this->run_setup();

        this->current_window = this->setup_window;
    }
    else
    {
        this->current_window = this->main_window;
    }

    return this->app->run(*current_window);
}

void AudioDesk::switch_window(Gtk::Window* window)
{
    std::cout << "switch_window: Switching active window" << std::endl
              << "switch_window: Removing existing window" << std::endl;
    this->app->hold();

    this->current_window->hide();

    this->app->remove_window(*this->current_window);

    this->app->add_window(*window);

    window->show();

    this->app->release();

    std::cout << "switch_window: Current window successfully switched" << std::endl;
    this->current_window = window;
}

bool AudioDesk::read_sound_cache()
{
    this->main_window->clear_sound_box();

    bool directory_valid = false;

    DIR *dir;
    struct dirent *ent;

    std::string cache_path = get_usable_path_for("cache").append("/");

    if ((dir = opendir( cache_path.c_str() )) != NULL)
    {
        directory_valid = true;

        while ((ent = readdir(dir)) != NULL)
        {
            std::string d_name(ent->d_name);
            std::string path = cache_path + d_name;

            std::cout << "Searching path " << path << std::endl;

            struct stat s;
            if ( stat(path.c_str(), &s) == 0 )
            {
                if ( s.st_mode & S_IFREG )
                {
                    if (d_name.size() < 5 or d_name.substr(d_name.size()-5, 5) != std::string(".meta"))
                    {
                        std::fstream audio_file, meta_file;

                        audio_file.open(path, std::ios::in);
                        meta_file.open(path + ".meta", std::ios::in);

                        if (audio_file.is_open())
                        {
                            if (meta_file.is_open())
                            {
                                Json::Value root;
                                Json::CharReaderBuilder builder;
                                JSONCPP_STRING errs;
                                if (!parseFromStream(builder, meta_file, &root, &errs)) {
                                    std::cout << "Corrupt metadata on cache/" << d_name << ": " << errs << std::endl;
                                }
                                else
                                {
                                    this->local_ids.emplace(root["id"].asUInt());

                                    this->main_window->add_sound_button(root["name"].asString(), path);
                                }
                            }
                            else
                            {
                                this->main_window->add_sound_button(d_name, path);
                            }
                        }
                    }
                }
            }
        }
        closedir(dir);
    }
    else
    {
        // directory not present
        if (errno == ENOENT)
        {
            // try to create directory
            if ( mkdir( cache_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH ) != 0 )
            {
                perror("mkdir( cache_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH )");
            }
            else
            {
                directory_valid = true;
            }
        }
        // other error
        else
        {
            perror("opendir( cache_path.c_str() )");
        }
    }

    return directory_valid;
}

void AudioDesk::read_sound_api()
{
    this->main_window->clear_online_sound_box();

    for (const Sound& sound : this->soundfx_api.get_sounds(this->page_number))
    {
        this->main_window->add_online_sound_button(sound);
    }
}

bool AudioDesk::watch_sound_cache()
{
    fd = inotify_init();

    if (fd < 0)
    {
        perror("inotify_init()");
        return false;
    }
    else
    {
        int wd = inotify_add_watch(fd, get_usable_path_for("cache").c_str(), IN_CREATE | IN_DELETE | IN_MOVE );

        if (wd < 0 )
        {
            perror("inotify_add_watch()");
            return false;
        }
        else
        {
            std::cout << "inotify successfully set up" << std::endl;

            return true;
        }
    }
}

bool AudioDesk::check_cache_events()
{
    struct pollfd fds[1];
    int ret;

    fds[0].fd = fd;
    fds[0].events = POLLIN;

    ret = poll(fds, 1, 0);
    if (ret < 0)
        perror ("poll(fds, 1, 0)");
    else if (ret != 0)
    {
        std::cout << "flushing fd..." << std::endl;
        // wipe out the contents of the file descriptor so we don't re-read old data
        char c[64];
        while (poll(fds, 1, 0))
            read(fd, c, 64);

        std::cout << "file changed detected; re-reading cache" << std::endl;

        this->read_sound_cache();
    }

    return true;
}

void AudioDesk::next_page()
{
    ++this->page_number;

    this->read_sound_api();
}

void AudioDesk::prev_page()
{
    if (this->page_number > 0)
    {
        --this->page_number;

        this->read_sound_api();
    }
}
