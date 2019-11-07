#include "setup_window.hpp"

SetupWindow::SetupWindow(
    BaseObjectType* object, 
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    Gtk::Button* button;
    this->builder->get_widget("new_vmic", button);

    this->builder->get_widget("comboentry", this->entry);

    button->signal_clicked().connect(
        sigc::mem_fun(*this, &SetupWindow::on_button_press)
    );
}

void SetupWindow::set_application(AudioDesk* application)
{
    this->audiodesk = application;

    this->add_available_devices();
}

void SetupWindow::add_available_devices()
{
    ModelColumns columns;
    auto input_devices = Gtk::ListStore::create(columns);

    Gtk::ComboBox* combobox;
    this->builder->get_widget("combobox", combobox);
    combobox->set_model(input_devices);

    for (std::string input_name : this->audiodesk->device_query.devices)
    {
        std::cout << "Device available: " << input_name << std::endl;
        auto row = input_devices->append();

        row->set_value(0, input_name);
    }
}

void SetupWindow::on_button_press()
{
    std::string text = this->entry->get_text();

    std::cout << text << std::endl;

    if (text != "")
    {
        this->audiodesk->setup.DEFAULT_DEVICE = text;
        std::cout << "Default device has been set to " << text << std::endl;
        
        this->audiodesk->setup.save_to_ini();

        this->audiodesk->switch_window(this->audiodesk->main_window);
    }
}