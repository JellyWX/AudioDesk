#include <gtkmm.h>

struct stat info;

enum SetupStatus {
    Uninitialized,
    PartiallySetup,
    Setup,
};

int main(int argc, char **argv)
{
    auto app = Gtk::Application::create(argc, argv, "com.jellywx.audiodesk");

    auto setup_builder = Gtk::Builder::create_from_file("interfaces/setup.glade");

    Gtk::Window* setup;

    setup_builder->get_widget("setup", setup);

    return app->run(*setup);
}