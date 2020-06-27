#pragma once

#include "audiodesk.fwd.hpp"
#include "windows.fwd.hpp"

#include <gtkmm.h>
#include <dirent.h>
#include <cerrno>
#include <regex>

#include "device_querier.hpp"
#include "setup.hpp"
#include "setup_window.hpp"
#include "main_window.hpp"
#include "soundfx_api.hpp"


class AudioDesk
{
public:
    AudioDesk(int argc, char** argv, const std::string& name);

    Glib::RefPtr<Gtk::Application> app;

    DeviceQuerier device_query = DeviceQuerier();

    Setup setup = Setup();

    SoundFX_API soundfx_api = SoundFX_API();

    SetupWindow* setup_window;
    MainWindow* main_window;
    Gtk::Window* current_window = nullptr;

    int run();

    void switch_window(Gtk::Window* window);

private:
    void run_setup();

    void run_main();

    void read_sound_cache();

};
