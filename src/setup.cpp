#include "setup.hpp"

Setup::Setup()
{
}

void Setup::start(DeviceQuerier* d_query)
{
    std::cout << "Entering setup now" << std::endl;

    this->load_type = this->check_directory(get_usable_path_for(""));

    switch (this->load_type)
    {
        case Loaded:
            std::cout << "Setup already done (I hope). Attempting to load now" << std::endl;
            this->load_from_ini(d_query);

            break;

        case New:
            std::cout << "New user! Creating a configuration file with default settings" << std::endl;
            this->save_to_ini();

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

void Setup::load_from_ini(DeviceQuerier* d_query)
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
                this->save_to_ini();
                break;
        }
    }
    else
    {
        this->VOLUME = std::stod(this->conf_loader.get_value("Stream", "VOLUME"));
        this->BITRATE = std::stoi(this->conf_loader.get_value("Stream", "BITRATE"));
        this->CACHE_ENABLED = this->conf_loader.get_value("Storage", "CACHE_ENABLED") == "true";

        std::string dd = this->conf_loader.get_value("Device", "DEFAULT");

        if (not d_query->device_exists(dd))
        {
            this->DEFAULT_DEVICE = "";
        }
        else
        {
            this->DEFAULT_DEVICE = dd;
        }
    }
}

void Setup::save_to_ini()
{
    if (this->DEFAULT_DEVICE != "")
        this->conf_loader.add_entry("Device", "DEFAULT", this->DEFAULT_DEVICE);
    else
        this->conf_loader.add_entry("Device", "DEFAULT", "");

    if (this->CACHE_ENABLED)
        this->conf_loader.add_entry("Storage", "CACHE_ENABLED", "true");
    else
        this->conf_loader.add_entry("Storage", "CACHE_ENABLED", "false");

    this->conf_loader.add_entry("Stream", "BITRATE", std::to_string(this->BITRATE));
    this->conf_loader.add_entry("Stream", "VOLUME", std::to_string(this->VOLUME));

    FileWriteStatus fstatus = this->conf_loader.serialize_to_file();

    if (fstatus != WriteSuccess)
    {
        std::cerr << "WARN: Failed to write configuration file." << std::endl;
    }
}