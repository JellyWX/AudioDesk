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
    std::cout << "Loading button row component" << std::endl;

    this->row_builder = Gtk::Builder::create_from_file("interfaces/button_row.glade");
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;
}