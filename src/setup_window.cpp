#include "setup_window.hpp"

SetupWindow::SetupWindow(
    BaseObjectType* object, 
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->add_available_devices();

    Gtk::Button* button;
    this->builder->get_widget("new_vmic", button);

    button->signal_clicked().connect(
        sigc::mem_fun(*this, &SetupWindow::on_button_press)
    );
}

void SetupWindow::set_application(AudioDesk* application)
{
    this->application = application;
}

void SetupWindow::add_available_devices()
{
    ModelColumns columns;
    auto input_devices = Gtk::ListStore::create(columns);

    Gtk::ComboBox* combobox;
    this->builder->get_widget("combobox", combobox);
    combobox->set_model(input_devices);

    for (std::string input_name : this->application->device_query.devices)
    {
        std::cout << "Device available: " << input_name << std::endl;
        auto row = input_devices->append();

        row->set_value(0, input_name);
    }
}

void SetupWindow::on_button_press()
{
    Gtk::Entry* entry;
    this->builder->get_widget("comboentry", entry);
    std::string text = entry->get_text();

    if (text != "")
    {
        this->application->setup.DEFAULT_DEVICE = text;
        std::cout << "Default device has been set to " << text << std::endl;
        
        this->application->setup.save_to_ini();
    }
}