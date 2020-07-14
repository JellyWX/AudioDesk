#pragma once

#include "windows.fwd.hpp"
#include "audiodesk.fwd.hpp"

#include <gtkmm.h>
#include <iostream>

#include "audiodesk.hpp"
#include "button_row.hpp"
#include "soundfx_api.hpp"


class MainWindow : public Gtk::Window
{
public:
    MainWindow(
        BaseObjectType* object,
        const Glib::RefPtr<Gtk::Builder>& builder
    );

    void set_application(AudioDesk* app);

    void clear_sound_box();
    void clear_online_sound_box();

    void add_sound_button(const std::string &sound_name, const std::string &sound_path);
    void add_online_sound_button(const Sound& sound);

    void on_change_mic_volume(double new_volume);

    void on_change_volume(double new_volume);

    void search_query();

private:
    const Glib::RefPtr<Gtk::Builder>& builder;

    AudioDesk* audiodesk{};

    Gtk::Box* sound_box;
    Gtk::Box* online_sound_box;

    Gtk::ScrolledWindow* online_scroll_area;

    Gtk::Button* next_page;

    Gtk::Entry* search_entry;
    Gtk::Button* search_button;

    Gtk::VolumeButton* volume_switch;
    Gtk::VolumeButton* mic_volume_switch;
};
