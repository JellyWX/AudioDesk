#include <iostream>
#include <gtkmm.h>
#include "setup.hpp"

struct stat info;

int main(int argc, char **argv)
{
    Setup configuration = Setup();

    auto app = Gtk::Application::create(argc, argv, "com.jellywx.audiodesk");

    auto setup_builder = Gtk::Builder::create_from_file("interfaces/setup.glade");

    Gtk::Window* setup;

    setup_builder->get_widget("setup", setup);

    return app->run(*setup);
}