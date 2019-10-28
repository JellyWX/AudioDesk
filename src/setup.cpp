Setup::Setup()
{
    ConfType load_style = this->check_directory("~/.audiodesk");

    switch (load_style) {
        case Temporary:

            break;

        case Loaded:

            break;
    }
}

ConfType Setup::check_directory(char* fpath)
{
    if ( stat(fpath, &info) != 0 )
    {
        std::cerr << "Cannot access .audiodesk configuration folder" << std::endl;
        return Temporary;
    }
    else if ( info.st_mode & S_IFDIR )
    {
        return Loaded;
    }
    else if ( mkdir(fpath) != 0 )
    {
        std::cerr << "Failed to create a configuration folder" << std::endl;
        return Temporary;
    }
    else
    {
        return Loaded;
    }
}