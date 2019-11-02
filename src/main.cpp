#include <iostream>
#include <gtkmm.h>
#include "ini.hpp"

struct stat info;

enum SetupStatus {
    Uninitialized,
    PartiallySetup,
    Setup,
};

int main(int argc, char **argv)
{
    IniFile conf_file("templates/audiodesk.ini");

    IniSection* device = conf_file.get_section("Device");

    std::cout << device->get_entry("VIRTUAL")->get_value() << std::endl;

    auto app = Gtk::Application::create(argc, argv, "com.jellywx.audiodesk");

    auto setup_builder = Gtk::Builder::create_from_file("interfaces/setup.glade");

    Gtk::Window* setup;

    setup_builder->get_widget("setup", setup);

    return app->run(*setup);
}