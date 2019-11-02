#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

enum ConfType
{
    Loaded, New, FailedTemporary
};

class Setup
{
public:
    Setup();

    bool cache = false;
    double volume = 1.0;
    int bitrate = 36000; 
    std::string default_device = NULL;
    std::string virtual_device = NULL;

    ConfType load_type = New;

private:
    ConfType check_directory(std::string fpath);

    int load_ini();
    int load_env();

    void create_conf();
};