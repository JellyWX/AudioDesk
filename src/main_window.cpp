#include "main_window.hpp"

MainWindow::MainWindow(
    BaseObjectType* object,
    const Glib::RefPtr<Gtk::Builder>& builder
    ) : Gtk::Window(object), builder(builder)
{
    this->audiodesk = nullptr;

    builder->get_widget("sounds", this->sound_box);
    builder->get_widget("online_sounds", this->online_sound_box);

    builder->get_widget("online_scroll_area", this->online_scroll_area);

    builder->get_widget("next_page", this->next_page);

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

    this->search_entry->signal_activate().connect(
        sigc::mem_fun(*this, &MainWindow::search_query)
    );
    this->search_button->signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::search_query)
    );

    this->audiodesk->soundfx_api.signal_connected().connect(
        sigc::mem_fun(*this, &MainWindow::set_connected)
    );
    this->audiodesk->soundfx_api.signal_disconnected().connect(
        sigc::mem_fun(*this, &MainWindow::set_disconnected)
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

    this->clear_online_sound_box();

    auto adjustment = this->online_scroll_area->get_vadjustment();
    adjustment->set_value(0);
    this->online_scroll_area->set_vadjustment(adjustment);

    this->audiodesk->soundfx_api.set_query(query);

    this->audiodesk->add_online_page(this->audiodesk->soundfx_api.get_current_page());
}

void MainWindow::set_connected()
{
    std::cout << "Received connection signal" << std::endl;

    this->next_page->set_label("Load More...");
}

void MainWindow::set_disconnected()
{
    std::cout << "Received disconnection signal" << std::endl;

    this->next_page->set_label("Disconnected. Retry connection...");
}
