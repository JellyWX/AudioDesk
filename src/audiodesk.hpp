#include <gtkmm.h>
#include "device_querier.hpp"
#include "setup.hpp"

class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:

    ModelColumns()
    { add(m_col_name); }

    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
};

class AudioDesk
{
public:
    AudioDesk(int argc, char** argv, std::string name);

    Glib::RefPtr<Gtk::Application> app;

    DeviceQuerier device_query = DeviceQuerier();

    Setup configuration = Setup(&this->device_query);

    Glib::RefPtr<Gtk::Builder> current_builder = Gtk::Builder::create();

    void run_setup();

    void run_main();

    void set_audio_source();
};