#pragma once

#include <gtkmm.h>

class ButtonRow : public Gtk::ButtonBox
{
public:
    ButtonRow(
        BaseObjectType* object,
        const Glib::RefPtr<Gtk::Builder>& builder
    );

};
