#pragma once

#include <gtkmm.h>
#include <sstream>
#include <iostream>

#include "utils.hpp"

class ButtonRow : public Gtk::ButtonBox
{
public:
    ButtonRow(const std::string& sound_name, const std::string& sound_path);

    void play();

private:
    std::string name;

    std::string command;

    std::string path;
};
