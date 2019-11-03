#include "audiodesk.hpp"

AudioDesk::AudioDesk(int argc, char** argv, std::string name)
{
    this->app = Gtk::Application::create(argc, argv, name);
}

void AudioDesk::run_setup()
{
    std::cout << "Default device not set or not found. Loading setup screen." << std::endl;

    current_builder = Gtk::Builder::create_from_file("interfaces/setup.glade");

    Gtk::Window* setup;

    current_builder->get_widget("setup", setup);

    ModelColumns columns;
    auto input_devices = Gtk::ListStore::create(columns);

    Gtk::ComboBox* combobox;
    current_builder->get_widget("combobox", combobox);
    combobox->set_model(input_devices);

    for (std::string input_name : this->device_query.devices)
    {
        std::cout << "Device available: " << input_name << std::endl;
        auto row = input_devices->append();

        row->set_value(0, input_name);
    }

    Gtk::Button* set_source;
    current_builder->get_widget("new_vmic", set_source);

    set_source->signal_clicked().connect(
        sigc::mem_fun(*this, &AudioDesk::set_audio_source)
    );

    this->app->run(*setup);
}

void AudioDesk::run_main()
{
    
}

void AudioDesk::set_audio_source()
{
    Gtk::Entry* entry;
    current_builder->get_widget("comboentry", entry);
    std::string text = entry->get_text();

    if (text != "")
    {
        this->configuration.DEFAULT_DEVICE = text;
        std::cout << "Default device has been set to " << text << std::endl;
    }

    this->configuration.save_to_ini();
}