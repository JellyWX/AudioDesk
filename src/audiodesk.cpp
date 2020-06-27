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

    this->read_sound_cache();

    for (const Sound& sound : this->soundfx_api.get_sounds(0))
    {
        this->main_window->add_online_sound_button(sound);
    }
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

void AudioDesk::read_sound_cache()
{
    DIR *dir;
    struct dirent *ent;

    std::string cache_path = get_usable_path_for("cache");

    if ((dir = opendir( cache_path.c_str() )) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            std::string d_name(ent->d_name);
            std::string path = cache_path + "/" + d_name;

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
        if (errno == ENOENT)
        {
            if ( mkdir(cache_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0 )
            {
                std::cerr << "Failed to create a cache folder:" <<
                " errno " << errno << "; " << strerror(errno) << std::endl;
            }
        }
        else
            std::cerr << "Error occured opening cache folder, errno " << errno << "; " << strerror(errno) << std::endl;
    }
}
