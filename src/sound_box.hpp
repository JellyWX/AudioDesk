#pragma once

#include <gtkmm.h>
#include <gtkmm/box.h>

class SoundBox : public Gtk::Box
{
public:
    SoundBox(
        BaseObjectType* object,
        const Glib::RefPtr<Gtk::Builder>& builder
    );

};