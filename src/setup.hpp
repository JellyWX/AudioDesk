#include "inih.h"
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

class Setup
{
public:
    Setup();

    bool cache_size = 0;
    float volume = 1.0;
    int bitrate = 36000; 
    std::string default_device = NULL;
    std::string virtual_device = NULL;

private:
    enum ConfType
    {
        Loaded, Temporary
    };

    ConfType check_directory();

    int load_ini();
    int load_env();
}