#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iostream>

enum FileLoadStatus
{
    Success, ParseError, IOError,
};

enum LineLoadStatus
{
    LSuccess, LParseError,
};

enum FileWriteStatus
{
    WriteIOError, WriteSuccess,
};

class IniEntry
{
public:
    IniEntry(std::string n, std::string v) : name(n), value(v) {};

    std::string get_value() { return this->value; };
    std::string set_value(std::string v) { this->value = v; };

    std::string serialize();

    std::string name;

private:
    std::string value = "";
};

class IniSection
{
public:
    IniSection(std::string n) : name(n) {};

    std::string serialize();

    void add_entry(IniEntry entry);
    void add_entry(std::string name, std::string value);

    IniEntry* get_entry(std::string name);

    std::string name;

private:
    std::vector<IniEntry> entries;
};

class IniFile
{
public:
    IniFile(std::string fpath, bool exists = true);

    std::string serialize();
    
    FileLoadStatus deserialize_from_file();
    FileWriteStatus serialize_to_file();

    void add_section(IniSection);
    void add_section(std::string name);

    void add_entry(std::string section, std::string name, std::string value);

    std::string get_value(std::string section, std::string name);

    IniSection* get_section(std::string name);

    IniSection* get_last_section();

private:
    LineLoadStatus deserialize_line(std::string line);

    std::vector<IniSection> sections;

    std::string fpath;
};