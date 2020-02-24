#include "ini.hpp"

#include <utility>

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

    return sstream.str();
}

void IniSection::add_entry(const IniEntry& entry)
{
    this->entries.push_back(entry);
}

void IniSection::add_entry(std::string new_name, std::string value)
{
    this->entries.emplace_back(IniEntry(std::move(new_name), std::move(value)));
}

IniEntry* IniSection::get_entry(const std::string& looking_for)
{
    for (
        auto it = this->entries.begin();
        it != this->entries.end();
        ++it
        )
    {
        if (it->name == looking_for)
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

IniFile::IniFile(std::string fpath, bool exists) : fpath(std::move(fpath))
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

LineLoadStatus IniFile::deserialize_line(const std::string& line)
{
    std::smatch match;

    // New section entered
    if (std::regex_search(line, match, std::regex(R"(\[(\w+)\])")))
    {
        std::string name = match.str(1);

        IniSection section = IniSection(name);

        this->add_section(section);

        return LSuccess;
    }
    // Match config assignment
    else if (std::regex_search(line, match, std::regex("([a-zA-Z_]+) = (.*)")) and not this->sections.empty())
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

void IniFile::add_entry(const std::string& section_name, const std::string& name, const std::string& value)
{
    IniSection* section = this->get_section(section_name);
    if (section == nullptr)
    {
        this->add_section(section_name);
        this->get_last_section()->add_entry(name, value);
    }
    else if (section->get_entry(name) == nullptr)
    {
        section->add_entry(name, value);
    }
    else
    {
        section->get_entry(name)->set_value(value);
    }
}

void IniFile::add_section(const IniSection& section)
{
    this->sections.push_back(section);
}

void IniFile::add_section(std::string name)
{
    this->sections.emplace_back(IniSection(std::move(name)));
}

std::string IniFile::get_value(const std::string& section, const std::string& name)
{
    return this->get_section(section)->get_entry(name)->get_value();
}

IniSection* IniFile::get_section(const std::string& name)
{
    for (
        auto it = this->sections.begin();
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