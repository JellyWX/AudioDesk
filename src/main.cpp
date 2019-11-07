#include "main.hpp"

int main(int argc, char **argv)
{
    AudioDesk app = AudioDesk(argc, argv, "com.jellywx.audiodesk");

    for (std::string name : app.device_query.devices)
        std::cout << "D:" << name << std::endl;

    app.run();
    
    return 0;
}