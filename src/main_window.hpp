#pragma once

#include "windows.fwd.hpp"
#include "audiodesk.fwd.hpp"

#include <gtkmm.h>
#include <iostream>
#include "audiodesk.hpp"
#include "button_row.hpp"


class MainWindow : public Gtk::Window
{
public:
    MainWindow(
        BaseObjectType* object,
        const Glib::RefPtr<Gtk::Builder>& builder
    );

    void set_application(AudioDesk* app);

    void add_sound_button(const std::string &sound_name, const std::string &sound_path);

private:
    const Glib::RefPtr<Gtk::Builder>& builder;

    AudioDesk* audiodesk{};

    Gtk::Box* sound_box;

    Glib::RefPtr<Gtk::Builder> row_builder;
};
