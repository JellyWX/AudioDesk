#include "utils.hpp"

std::string get_usable_path_for(const std::string& location)
{
    std::string home = getenv("HOME");
    return home + "/.audiodesk/" + location;
}
