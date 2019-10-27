#include <gtkmm.h>

int main(int argc, char **argv)
{
    auto app = gtkk::Application::create(argc, argv, "com.jellywx.audiodesk");

    Gtk::Window window;
    window.set_default_size(640, 480);

    return app->run(window);
}