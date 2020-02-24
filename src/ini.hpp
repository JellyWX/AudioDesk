#pragma once

#include <fstream>
#include <sstream>
#include <utility>
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
    IniEntry(std::string n, std::string v) : name(std::move(n)), value(std::move(v)) {};

    std::string get_value() { return this->value; };
    void set_value(std::string v) { this->value = std::move(v); };

    std::string serialize();

    std::string name;

private:
    std::string value = "";
};

class IniSection
{
public:
    explicit IniSection(std::string n) : name(std::move(n)) {};

    std::string serialize();

    void add_entry(const IniEntry& entry);
    void add_entry(std::string new_name, std::string value);

    IniEntry* get_entry(const std::string& looking_for);

    std::string name;

private:
    std::vector<IniEntry> entries;
};

class IniFile
{
public:
    explicit IniFile(std::string fpath, bool exists = true);

    std::string serialize();
    
    FileLoadStatus deserialize_from_file();
    FileWriteStatus serialize_to_file();

    void add_section(const IniSection&);
    void add_section(std::string name);

    void add_entry(const std::string& section, const std::string& name, const std::string& value);

    std::string get_value(const std::string& section, const std::string& name);

    IniSection* get_section(const std::string& name);

    IniSection* get_last_section();

private:
    LineLoadStatus deserialize_line(const std::string& line);

    std::vector<IniSection> sections;

    std::string fpath;
};