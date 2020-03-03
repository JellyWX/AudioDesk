#include <iostream>
#include "button_row.hpp"


ButtonRow::ButtonRow(const std::string& sound_name, const std::string& sound_path, AudioDesk* app)
{
    this->name = sound_name;
    this->path = get_usable_path_for(sound_path);
    this->audiodesk = app;

    this->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->set_layout(Gtk::BUTTONBOX_START);

    auto label = new Gtk::Label(sound_name);
    this->pack_start(*label, true, true);

    auto play = new Gtk::Button();
    auto play_label = new Gtk::Label("Play Down Mic");
    play->add(*play_label);
    play->signal_clicked().connect(
        sigc::mem_fun(*this, &ButtonRow::play_mic)
    );
    this->pack_start(*play, true, true);
    this->set_child_secondary(*play, true);

    auto demo = new Gtk::Button();
    auto demo_label = new Gtk::Label("Demo");
    demo->add(*demo_label);
    demo->signal_clicked().connect(
        sigc::mem_fun(*this, &ButtonRow::play)
    );
    this->pack_start(*demo, true, true);
    this->set_child_secondary(*demo, true);
}

void ButtonRow::play()
{
    std::stringstream command_content;
    command_content << "scripts/bash/play_audio.sh " << this->path << " " << (short)(this->audiodesk->setup.VOLUME * 100) << " &";

    std::cout << command_content.str() << std::endl;

    system(command_content.str().c_str());
}

void ButtonRow::play_mic()
{
    std::stringstream command_content;
    command_content << "scripts/bash/stream_audio.sh " << this->path << " " << this->audiodesk->setup.MIC_VOLUME << " &";

    std::cout << command_content.str() << std::endl;

    system(command_content.str().c_str());
}
