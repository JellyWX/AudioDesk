#pragma once

#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include "pstream.h"


class DeviceQuerier
{
public:
    DeviceQuerier();

    bool device_exists(std::string name);

    std::vector<std::string> devices;

private:
    void get_all_sources();
};