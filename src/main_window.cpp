#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object,
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->audiodesk = nullptr;

    builder->get_widget("sounds", this->sound_box);
}

void MainWindow::create_row_builder(const std::string& resource_path)
{
    std::cout << "Loading button row component from resource " << resource_path << std::endl;

    this->row_builder = Gtk::Builder::create_from_file(resource_path);
}

void MainWindow::add_sound_button(const std::string& sound_name, const std::string& sound_path)
{
    auto row = new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL);

    auto label = new Gtk::Label(sound_name);
    row->add(*label);

    auto play = new Gtk::Button();
    auto play_label = new Gtk::Label("Play Down Mic");
    play->add(*play_label);
    row->add(*play);

    auto demo = new Gtk::Button();
    auto demo_label = new Gtk::Label("Demo");
    demo->add(*demo_label);
    row->add(*demo);

    this->sound_box->add(*row);
    row->show_all();
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;
}
