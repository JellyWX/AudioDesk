#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object, 
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{

}

void MainWindow::set_application(AudioDesk* application)
{
    this->application = application;
}