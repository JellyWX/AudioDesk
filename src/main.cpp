#include "main.hpp"

int main(int argc, char **argv)
{
    AudioDesk app = AudioDesk(argc, argv, "com.jellywx.audiodesk");

    if (app.configuration.DEFAULT_DEVICE == "")
    {
        app.run_setup();
    }

    return 0;
}