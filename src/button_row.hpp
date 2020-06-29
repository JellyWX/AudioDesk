#pragma once

#include <gtkmm.h>
#include <sstream>
#include <iostream>

#include "utils.hpp"
#include "audiodesk.hpp"
#include "sound.hpp"


class LocalButtonRow : public Gtk::ButtonBox
{
public:
    LocalButtonRow(const std::string& sound_name, const std::string& sound_path, AudioDesk* app);

    void play();

    void play_mic();

private:
    std::string name;

    std::string path;

    AudioDesk* audiodesk{};

};


class RemoteButtonRow : public Gtk::ButtonBox
{
public:
    RemoteButtonRow(const Sound& sound, AudioDesk* app);

    void download();

private:
    Sound sound;

    AudioDesk* audiodesk{};

};
