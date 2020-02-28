#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object,
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->audiodesk = nullptr;

    builder->get_widget("sounds", this->sound_box);
}

void MainWindow::add_sound_button(const std::string& sound_name, const std::string& sound_path)
{
    auto row = new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL);
    row->set_layout(Gtk::BUTTONBOX_START);

    auto label = new Gtk::Label(sound_name);
    row->pack_start(*label, true, true);

    auto play = new Gtk::Button();
    auto play_label = new Gtk::Label("Play Down Mic");
    play->add(*play_label);
    row->pack_start(*play, true, true);
    row->set_child_secondary(*play, true);

    auto demo = new Gtk::Button();
    auto demo_label = new Gtk::Label("Demo");
    demo->add(*demo_label);
    row->pack_start(*demo, true, true);
    row->set_child_secondary(*demo, true);

    this->sound_box->add(*row);
    row->show_all();
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;
}
