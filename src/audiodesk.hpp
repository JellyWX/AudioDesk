#pragma once

#include "audiodesk.fwd.hpp"
#include "windows.fwd.hpp"

#include <gtkmm.h>
#include <dirent.h>
#include <cerrno>
#include <unordered_set>

#include <sys/inotify.h>
#include <poll.h>

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

    std::unordered_set<unsigned int> local_ids;

    SetupWindow* setup_window;
    MainWindow* main_window;
    Gtk::Window* current_window = nullptr;

    int fd;

    int run();

    void switch_window(Gtk::Window* window);

    void next_page();

    void add_online_page(const std::vector<Sound>& sounds) const;

private:
    void run_setup();

    void run_main();

    bool read_sound_cache();

    bool watch_sound_cache();

    bool check_cache_events();

};
