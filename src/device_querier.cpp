#include "device_querier.hpp"

DeviceQuerier::DeviceQuerier()
{
    this->get_all_sources();
}

void DeviceQuerier::get_all_sources()
{
    std::cout << "Setting up device query" << std::endl;

    redi::ipstream in("pacmd list-sources");
    std::string line;
    std::smatch match;

    while ( getline(in, line) )
    {
        if (std::regex_search(line, match, std::regex("^\\s+name: <(.*)>")))
        {
            std::cout << "Match: " << match.str(1) << std::endl;

            this->devices.push_back(match.str(1));
        }
    }
}

bool DeviceQuerier::device_exists(const std::string &name)
{
    for (const std::string &device : this->devices)
    {
        if (device == name)
        {
            return true;
        }
    }

    return false;
}