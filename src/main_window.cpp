#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object,
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->audiodesk = nullptr;

    builder->get_widget("sounds", this->sound_box);
    builder->get_widget("online_sounds", this->online_sound_box);

    builder->get_widget("next_page", this->next_page);
    builder->get_widget("prev_page", this->prev_page);

    builder->get_widget("search_entry", this->search_entry);
    builder->get_widget("search_button", this->search_button);

    builder->get_widget("change_vol", this->volume_switch);
    builder->get_widget("change_mic", this->mic_volume_switch);
}

void MainWindow::set_application(AudioDesk* app)
{
    this->audiodesk = app;

    this->volume_switch->set_value(app->setup.VOLUME);
    this->mic_volume_switch->set_value(app->setup.MIC_VOLUME);

    this->volume_switch->signal_value_changed().connect(
        sigc::mem_fun(*this, &MainWindow::on_change_volume)
    );
    this->mic_volume_switch->signal_value_changed().connect(
        sigc::mem_fun(*this, &MainWindow::on_change_mic_volume)
    );

    this->next_page->signal_clicked().connect(
        sigc::mem_fun(this->audiodesk, &AudioDesk::next_page)
    );
    this->prev_page->signal_clicked().connect(
        sigc::mem_fun(this->audiodesk, &AudioDesk::prev_page)
    );

    this->search_button->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::search_query)
    );
}

void MainWindow::add_sound_button(const std::string& sound_name, const std::string& sound_path)
{
    auto row = new LocalButtonRow(sound_name, sound_path, this->audiodesk);
    row->set_name("row");

    this->sound_box->add(*row);
    row->show_all();
}

void MainWindow::add_online_sound_button(const Sound& sound)
{
    auto row = new RemoteButtonRow(sound, this->audiodesk);

    this->online_sound_box->add(*row);
    row->show_all();
}

void MainWindow::on_change_mic_volume(double new_volume)
{
    this->audiodesk->setup.MIC_VOLUME = new_volume;
    this->audiodesk->setup.save_to_ini();
}

void MainWindow::on_change_volume(double new_volume)
{
    this->audiodesk->setup.VOLUME = new_volume;
    this->audiodesk->setup.save_to_ini();
}

void MainWindow::clear_sound_box()
{
    std::vector<Gtk::Widget*> children = this->sound_box->get_children();

    for (auto child : children)
        this->sound_box->remove(*child);
}

void MainWindow::clear_online_sound_box()
{
    std::vector<Gtk::Widget*> children = this->online_sound_box->get_children();

    for (auto child : children)
        this->online_sound_box->remove(*child);
}

void MainWindow::search_query()
{
    std::string query = this->search_entry->get_text();

    this->audiodesk->soundfx_api.set_query(query);

    this->audiodesk->read_sound_api();
}
