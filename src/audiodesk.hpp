#pragma once

#include "audiodesk.fwd.hpp"
#include "setup_window.fwd.hpp"

#include <gtkmm.h>
#include "device_querier.hpp"
#include "setup.hpp"
#include "setup_window.hpp"



class AudioDesk
{
public:
    AudioDesk(int argc, char** argv, std::string name);

    Glib::RefPtr<Gtk::Application> app;

    DeviceQuerier device_query = DeviceQuerier();

    Setup setup = Setup(&this->device_query);

    SetupWindow* setup_window;

    void run_setup();

    void run_main();
};