#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object, 
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->audiodesk = nullptr;
}

void MainWindow::create_row_builder(const std::string& resource_path)
{
    std::cout << "Loading button row component from resource " << resource_path << std::endl;

    this->row_builder = Gtk::Builder::create_from_file(resource_path);
}

void MainWindow::add_sound_button(const std::string& sound_name, const std::string& sound_path)
{
    ButtonRow* row;
    this->row_builder->get_widget_derived("box", row);
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;
}