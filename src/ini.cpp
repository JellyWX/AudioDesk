#include "ini.hpp"

std::string IniEntry::serialize()
{
    std::ostringstream sstream;

    sstream << this->name << " = " << this->get_value() << std::endl;

    return sstream.str();
}

std::string IniSection::serialize()
{
    std::ostringstream sstream;

    sstream << "[" << this->name << "]" << std::endl;

    for (IniEntry entry : this->entries)
    {
        sstream << entry.serialize();
    }

    sstream << std::endl;

    return sstream.str();
}

void IniSection::add_entry(IniEntry entry)
{
    this->entries.push_back(entry);
}

void IniSection::add_entry(std::string name, std::string value)
{
    this->entries.push_back(IniEntry(name, value));
}

IniEntry* IniSection::get_entry(std::string name)
{
    for (
        std::vector<IniEntry>::iterator it = this->entries.begin();
        it != this->entries.end();
        ++it
        )
    {
        if (it->name == name)
        {
            return &(*it);
        }
    }

    return nullptr;
}

std::string IniFile::serialize()
{
    std::ostringstream sstream;

    for (IniSection section : this->sections)
    {
        sstream << section.serialize() << std::endl;
    }

    return sstream.str();
}

FileWriteStatus IniFile::serialize_to_file()
{
    std::fstream file;

    file.open(fpath, std::ios::out);

    if (file.is_open())
    {
        file << this->serialize();

        return WriteSuccess;
    }
    else
    {
        return WriteIOError;
    }
}

IniFile::IniFile(std::string fpath, bool exists) : fpath(fpath)
{
    if (exists)
    {
        FileLoadStatus l = this->deserialize_from_file();

        switch (l)
        {
            case IOError:
                std::cerr << "Failed to open INI file" << std::endl;
                break;

            case ParseError:
                std::cerr << "Failed to parse INI file" << std::endl;
                break;

            default:
                break;
        }
    }
}

FileLoadStatus IniFile::deserialize_from_file()
{
    std::fstream file;
    std::string line;

    LineLoadStatus lstatus = LSuccess;

    file.open(this->fpath, std::ios::in);

    if (file.is_open())
    {
        while (getline(file, line) and lstatus == LSuccess)
        {
            lstatus = this->deserialize_line(line);
        }

        if (lstatus == LSuccess)
        {
            return Success;
        }
        else
        {
            return ParseError;
        }
    }
    else
    {
        return IOError;
    }
}

LineLoadStatus IniFile::deserialize_line(std::string line)
{
    std::smatch match;

    // New section entered
    if (std::regex_search(line, match, std::regex("\\[(\\w+)\\]")))
    {
        std::string name = match.str(1);

        IniSection section = IniSection(name);

        this->add_section(section);

        return LSuccess;
    }
    // Match config assignment
    else if (std::regex_search(line, match, std::regex("([a-zA-Z_]+) = (.*)")) and this->sections.size() > 0)
    {
        IniSection* current_operating_section = this->get_last_section();

        std::string entry_name = match.str(1);
        std::string value = match.str(2);

        current_operating_section->add_entry(IniEntry(entry_name, value));

        return LSuccess;
    }
    // Match empty line
    else if (std::regex_match(line, std::regex("\\s*$")))
    {
        return LSuccess;
    }
    else
    {
        std::cerr << "Parser error on `" << line << "`" << std::endl;
        return LParseError;
    }
}

void IniFile::add_entry(std::string section_name, std::string name, std::string value)
{
    IniSection* section = this->get_section(section_name);
    if (section == nullptr)
    {
        this->add_section(section_name);
        this->get_last_section()->add_entry(name, value);
    }
    else
    {
        section->add_entry(name, value);
    }
}

void IniFile::add_section(IniSection section)
{
    this->sections.push_back(section);
}

void IniFile::add_section(std::string name)
{
    this->sections.push_back(IniSection(name));
}

std::string IniFile::get_value(std::string section, std::string name)
{
    return this->get_section(section)->get_entry(name)->get_value();
}

IniSection* IniFile::get_section(std::string name)
{
    for (
        std::vector<IniSection>::iterator it = this->sections.begin();
        it != this->sections.end();
        ++it)
    {
        if (it->name == name)
        {
            return &(*it);
        }
    }

    return nullptr;
}

IniSection* IniFile::get_last_section()
{
    return &this->sections.back();
}