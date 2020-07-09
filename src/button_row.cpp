#include <iostream>
#include "button_row.hpp"


LocalButtonRow::LocalButtonRow(const std::string& sound_name, const std::string& sound_path, AudioDesk* app)
{
    this->name = sound_name;
    this->path = sound_path;
    this->audiodesk = app;

    this->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->set_layout(Gtk::BUTTONBOX_START);

    auto label = new Gtk::Label(sound_name);
    label->set_name("sound-name");
    label->set_halign(Gtk::ALIGN_START);
    this->pack_start(*label, true, true);

    auto play = new Gtk::Button();
    play->set_name("play-button");
    auto play_label = new Gtk::Label("microphone-alt");
    play_label->set_name("fa");
    play->add(*play_label);
    play->signal_clicked().connect(
        sigc::mem_fun(*this, &LocalButtonRow::play_mic)
    );
    this->pack_end(*play, false, false);
    this->set_child_non_homogeneous(*play, true);
    this->set_child_secondary(*play, true);

    auto demo = new Gtk::Button();
    demo->set_name("play-button");
    auto demo_label = new Gtk::Label("play");
    demo_label->set_name("fa");
    demo->add(*demo_label);
    demo->signal_clicked().connect(
        sigc::mem_fun(*this, &LocalButtonRow::play)
    );
    this->pack_end(*demo, false, false);
    this->set_child_non_homogeneous(*demo, true);
    this->set_child_secondary(*demo, true);
}

void LocalButtonRow::play()
{
    std::stringstream command_content;
    command_content << "scripts/bash/play_audio.sh " << this->path << " " << (short)(this->audiodesk->setup.VOLUME * 100) << " &";

    std::cout << command_content.str() << std::endl;

    system(command_content.str().c_str());
}

void LocalButtonRow::play_mic()
{
    std::stringstream command_content;
    command_content << "scripts/bash/stream_audio.sh " << this->path << " " << this->audiodesk->setup.MIC_VOLUME << " &";

    std::cout << command_content.str() << std::endl;

    system(command_content.str().c_str());
}

RemoteButtonRow::RemoteButtonRow(
        const Sound& sound,
        AudioDesk *app)

: audiodesk(app), sound(sound)
{
    this->set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    this->set_layout(Gtk::BUTTONBOX_START);

    auto label = new Gtk::Label(sound.get_name());
    this->pack_start(*label, true, true);

    if (app->local_ids.find(sound.get_id()) == app->local_ids.end())
    {
        auto download = new Gtk::Button();
        auto download_label = new Gtk::Label("Download");
        download->add(*download_label);
        download->signal_clicked().connect(
            sigc::mem_fun(*this, &RemoteButtonRow::download)
        );
        this->pack_start(*download, false, false);
        this->set_child_secondary(*download, true);
    }
}

void RemoteButtonRow::download()
{
    std::string new_path = this->audiodesk->soundfx_api.download_sound(this->sound.get_id());
}
