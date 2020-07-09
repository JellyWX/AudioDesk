#include "main.hpp"

int main(int argc, char **argv)
{
    AudioDesk app = AudioDesk(argc, argv, "com.jellywx.audiodesk");

    auto css = Gtk::CssProvider::create();
    css->load_from_path("interfaces/css/style.css");

    Gtk::StyleContext::add_provider_for_screen(Gdk::Screen::get_default(), css, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    std::string font_path("interfaces/fonts/fa5-solid.otf");
    const FcChar8 * file = (const FcChar8 *)font_path.c_str();
    FcBool fontAddStatus = FcConfigAppFontAddFile(FcConfigGetCurrent(), file);

    if (!fontAddStatus)
    {
        std::cerr << "Failed to load FontAwesome" << std::endl;
    }

    app.run();

    return 0;
}
