#include <fstream>
#include "setup.hpp"

Setup::Setup()
{
    this->load_type = this->check_directory("~/.audiodesk");
}

ConfType Setup::check_directory(std::string fpath)
{
    struct stat info;

    if ( stat(fpath.c_str(), &info) != 0 )
    {
        std::cerr << "Cannot access .audiodesk configuration folder" << std::endl;
        return FailedTemporary;
    }
    else if ( info.st_mode & S_IFDIR )
    {
        return Loaded;
    }
    else if ( mkdir(fpath.c_str(), 0777) != 0 )
    {
        std::cerr << "Failed to create a configuration folder" << std::endl;
        return FailedTemporary;
    }
    else
    {
        return New;
    }
}

void Setup::create_conf()
{
    std::ofstream conf_file;

    conf_file.open("~/.audiodesk/audiodesk.ini");

    if (conf_file.is_open())
    {
        conf_file << "" << std::endl;

        conf_file.close();
    }
    else
    {
        std::cerr << "Failed to open `audiodesk.ini` for writing" << std::endl;
    }
}