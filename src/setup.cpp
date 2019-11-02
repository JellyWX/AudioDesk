#include "setup.hpp"

std::string get_usable_path_for(std::string location)
{
    std::string home = getenv("HOME");
    return home + "/.audiodesk/" + location;
}

Setup::Setup()
{
    std::cout << "Entering setup now" << std::endl;

    this->load_type = this->check_directory(get_usable_path_for(""));

    switch (this->load_type)
    {
        case Loaded:
            std::cout << "Setup already done (I hope). Attempting to load **now**!" << std::endl;
            this->load_from_ini();

            break;

        case New:
            std::cout << "New user! Creating a configuration file with default settings" << std::endl;
            this->create_conf();

            break;

        case FailedTemporary:
            std::cerr << "WARN: Something in setup failed. See above..." << std::endl;
            break;
    }
}

ConfType Setup::check_directory(std::string fpath)
{
    struct stat info;

    if ( stat(fpath.c_str(), &info) != 0 )
    {
        std::cout << "Configuration folder not existing yet..." << std::endl;

        if ( mkdir(fpath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0 )
        {
            std::cerr << "Failed to create a configuration folder:" <<
            " errno " << errno << "; " << strerror(errno) << std::endl;
            return FailedTemporary;
        }
        else
        {
            return New;
        }
    }
    else if ( info.st_mode & S_IFDIR )
    {
        return Loaded;
    }
    else
    {
        std::cerr << "Not a clue what's gone wrong here. Not going to load anything" << std::endl;
        return FailedTemporary;
    }
}

void Setup::create_conf()
{
    this->conf_loader.add_entry("Device", "DEFAULT", "");
    this->conf_loader.add_entry("Device", "VIRTUAL", "~/.audiodesk/virtmic");

    this->conf_loader.add_entry("Stream", "VOLUME", "1.0");
    this->conf_loader.add_entry("Stream", "BITRATE", "36000");

    this->conf_loader.add_entry("Storage", "CACHE_ENABLED", "true");

    FileWriteStatus fstatus = this->conf_loader.serialize_to_file();

    if (fstatus != WriteSuccess)
    {
        std::cerr << "Failed to write configuration file. Goodbye." << std::endl;
    }
}

void Setup::load_from_ini()
{
    FileLoadStatus fstatus = this->conf_loader.deserialize_from_file();
    if (fstatus != Success)
    {
        switch (fstatus)
        {
            case IOError:
                std::cerr << "IOError occured. This is unrecoverable. Goodbye." << std::endl;
                break;

            case ParseError:
                std::cerr << "Parser error: failed to parse" << 
                    "configuration file. See errors above." << std::endl <<
                    "We are going to beat the file to death." << std::endl;
                this->create_conf();
                break;
        }
    }
    else
    {
        this->VOLUME = std::stod(this->conf_loader.get_value("Stream", "VOLUME"));
        this->BITRATE = std::stoi(this->conf_loader.get_value("Stream", "BITRATE"));
        this->CACHE_ENABLED = this->conf_loader.get_value("Storage", "CACHE_ENABLED") == "true";

        std::string dd = this->conf_loader.get_value("Device", "DEFAULT");

        if (dd )
        {
            this->DEFAULT_DEVICE = nullptr;
        }
        else
        {
            this->DEFAULT_DEVICE = dd;
        }
    }
}