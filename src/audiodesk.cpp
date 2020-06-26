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

    this->main_window->add_sound_button("Die 0", "audio/hattrick.mp3");

    this->soundfx_api.get_sounds(0);
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
