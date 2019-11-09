#include "audiodesk.hpp"

AudioDesk::AudioDesk(int argc, char** argv, std::string name)
{
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
    std::cout << "Generating a primary window" << std::endl;

    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("interfaces/main.glade");

    builder->get_widget_derived("main", this->main_window);

    this->main_window->set_application(this);
}

int AudioDesk::run()
{
    std::cout << "Entering run" << std::endl;

    this->run_main();

    if (this->setup.DEFAULT_DEVICE == "")
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
    std::cout << "Switching active window" << std::endl
              << "Removing existing window" << std::endl;
    this->app->hold();

    this->current_window->hide();

    this->app->remove_window(*this->current_window);

    this->app->add_window(*window);

    window->show();

    this->app->release();

    std::cout << "Current window successfully switched" << std::endl;
    this->current_window = window;
}