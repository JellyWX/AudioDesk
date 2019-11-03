#include "device_querier.hpp"

DeviceQuerier::DeviceQuerier()
{
    this->get_all_sources();
}

void DeviceQuerier::get_all_sources()
{
    this->devices.empty();

    redi::ipstream in("pacmd list-sources");
    std::string line;
    std::smatch match;

    while ( getline(in, line) )
    {
        if (std::regex_search(line, match, std::regex("^\\s+name: <(.*)>")))
        {
            this->devices.push_back(match.str(1));
        }
    }   
}

bool DeviceQuerier::device_exists(std::string name)
{
    for (std::string device : this->devices)
    {
        if (device == name)
        {
            return true;
        }
    }

    return false;
}