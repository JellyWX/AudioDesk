#include "main.hpp"

int main(int argc, char **argv)
{
    AudioDesk app = AudioDesk(argc, argv, "com.jellywx.audiodesk");

    auto css = Gtk::CssProvider::create();
    css->load_from_path("interfaces/css/style.css");

    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    app.run();
    
    return 0;
}