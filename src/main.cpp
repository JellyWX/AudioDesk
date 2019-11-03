#include <iostream>
#include <gtkmm.h>
#include "setup.hpp"
#include "device_querier.hpp"


int main(int argc, char **argv)
{
    DeviceQuerier d_query;

    Setup configuration = Setup(&d_query);

    auto app = Gtk::Application::create(argc, argv, "com.jellywx.audiodesk");

    if (configuration.DEFAULT_DEVICE == nullptr)
    {
        auto setup_builder = Gtk::Builder::create_from_file("interfaces/setup.glade");
    
        Gtk::Window* setup;

        setup_builder->get_widget("setup", setup);

        app->run(*setup);
    }


    return 0;
}