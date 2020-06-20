#pragma once

#include "audiodesk.fwd.hpp"
#include "windows.fwd.hpp"

#include <gtkmm.h>
#include "device_querier.hpp"
#include "setup.hpp"
#include "setup_window.hpp"
#include "main_window.hpp"


class AudioDesk
{
public:
    AudioDesk(int argc, char** argv, const std::string& name);

    Glib::RefPtr<Gtk::Application> app;

    DeviceQuerier device_query = DeviceQuerier();

    Setup setup = Setup();

    SetupWindow* setup_window;
    MainWindow* main_window;
    Gtk::Window* current_window = nullptr;

    int run();

    void switch_window(Gtk::Window* window);

private:
    void run_setup();

    void run_main();

};
