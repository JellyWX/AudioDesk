#include "audiodesk.hpp"

AudioDesk::AudioDesk(int argc, char** argv, std::string name)
{
    this->app = Gtk::Application::create(argc, argv, name);

    this->run_setup();
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

}