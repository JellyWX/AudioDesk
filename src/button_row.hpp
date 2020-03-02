#pragma once

#include <gtkmm.h>
#include <sstream>
#include <iostream>

#include "utils.hpp"
#include "audiodesk.hpp"


class ButtonRow : public Gtk::ButtonBox
{
public:
    ButtonRow(const std::string& sound_name, const std::string& sound_path, AudioDesk* app);

    void play();

private:
    std::string name;

    std::string path;

    AudioDesk* audiodesk{};

};
