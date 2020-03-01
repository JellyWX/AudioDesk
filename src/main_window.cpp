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
    auto row = new ButtonRow(sound_name, sound_path);

    this->sound_box->add(*row);
    row->show_all();
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;
}
