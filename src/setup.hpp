#pragma once

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <fstream>
#include <cerrno>

#include "ini.hpp"
#include "utils.hpp"
#include "device_querier.hpp"

enum ConfType
{
    Loaded, New, FailedTemporary
};

class Setup
{
public:
    Setup();

    void start(DeviceQuerier* d_query);

    IniFile conf_loader = IniFile(get_usable_path_for("audiodesk.ini"), false);

    ConfType load_type = New;

    double VOLUME = 1.0;
    double MIC_VOLUME = 1.0;
    int BITRATE = 36000;

    bool CACHE_ENABLED = true;

    std::string DEFAULT_DEVICE = "";

    void save_to_ini();

private:
    static ConfType check_directory(const std::string& fpath);

    void load_from_ini(DeviceQuerier* d_query);
};
