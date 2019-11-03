#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fstream>
#include <cerrno>
#include "ini.hpp"
#include "device_querier.hpp"

std::string get_usable_path_for(std::string location);

enum ConfType
{
    Loaded, New, FailedTemporary
};

class Setup
{
public:
    Setup(DeviceQuerier* d_query);

    IniFile conf_loader = IniFile(get_usable_path_for("audiodesk.ini"), false);

    ConfType load_type = New;

    DeviceQuerier* device_querier;

    double VOLUME = 1.0;
    int BITRATE = 36000;

    bool CACHE_ENABLED = true;

    std::string DEFAULT_DEVICE = "";

    void save_to_ini();

private:
    ConfType check_directory(std::string fpath);

    void load_from_ini();
};