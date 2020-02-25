#pragma once

#include "windows.fwd.hpp"
#include "audiodesk.fwd.hpp"

#include <gtkmm.h>
#include <iostream>
#include "audiodesk.hpp"


class MainWindow : public Gtk::Window
{
public:
    MainWindow(
        BaseObjectType* object,
        const Glib::RefPtr<Gtk::Builder>& builder
    );

    void set_application(AudioDesk* app);

    void create_row_builder(const std::string &resource_path);

private:
    const Glib::RefPtr<Gtk::Builder>& builder;

    AudioDesk* audiodesk{};

    Glib::RefPtr<Gtk::Builder> row_builder;
};