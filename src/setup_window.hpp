#pragma once

#include "setup_window.fwd.hpp"
#include "audiodesk.fwd.hpp"

#include <gtkmm.h>
#include <iostream>
#include "setup.hpp"
#include "audiodesk.hpp"


class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:

    ModelColumns()
    { add(m_col_name); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
};

class SetupWindow : public Gtk::Window
{
public:
    SetupWindow(
        BaseObjectType* object,
        const Glib::RefPtr<Gtk::Builder>& builder
    );

    void set_application(AudioDesk* application);

private:
    const Glib::RefPtr<Gtk::Builder>& builder;

    AudioDesk* application;

    void add_available_devices();

    void on_button_press();
};