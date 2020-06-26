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

    void add_sound_button(const std::string &sound_name, const std::string &sound_path);

    void add_online_sound_button(const Sound& sound);

    void on_change_mic_volume(double new_volume);

    void on_change_volume(double new_volume);

private:
    const Glib::RefPtr<Gtk::Builder>& builder;

    AudioDesk* audiodesk{};

    Gtk::Box* sound_box;
    Gtk::Box* online_sound_box;

    Gtk::Button* next_page;
    Gtk::Button* prev_page;

    Gtk::VolumeButton* volume_switch;
    Gtk::VolumeButton* mic_volume_switch;

    Glib::RefPtr<Gtk::Builder> row_builder;
};
