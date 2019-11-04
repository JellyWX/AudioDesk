#include "main.hpp"

int main(int argc, char **argv)
{
    AudioDesk app = AudioDesk(argc, argv, "com.jellywx.audiodesk");

    if (app.setup.DEFAULT_DEVICE == "")
    {
        app.run_setup();
    }
    else
    {
        app.run_main();
    }

    return 0;
}