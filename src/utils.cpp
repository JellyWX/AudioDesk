#include "utils.hpp"

std::string get_usable_path_for(std::string location)
{
    std::string home = getenv("HOME");
    return home + "/.audiodesk/" + location;
}