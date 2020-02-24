#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object, 
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->audiodesk = nullptr;
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;
}