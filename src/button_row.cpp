#include "button_row.hpp"


ButtonRow::ButtonRow(const std::string& sound_name, const std::string& sound_path)
{
    this->name = sound_name;
    this->path = get_usable_path_for(sound_path);

    this->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->set_layout(Gtk::BUTTONBOX_START);

    auto label = new Gtk::Label(sound_name);
    this->pack_start(*label, true, true);

    auto play = new Gtk::Button();
    auto play_label = new Gtk::Label("Play Down Mic");
    play->add(*play_label);
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
    std::stringstream command;

    command << "scripts/bash/play_audio.sh " << this->path << " &";

    system(command.str().c_str());
}
