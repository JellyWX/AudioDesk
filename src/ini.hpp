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

class IniEntry
{
public:
    IniEntry(std::string n, std::string v) : name(n), value(v) {};

    std::string get_value() { return value; };

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

    IniEntry* get_entry(std::string name);

    std::string name;

private:
    std::vector<IniEntry> entries;
};

class IniFile
{
public:
    IniFile(std::string fpath);

    std::string serialize();

    void add_section(IniSection);

    IniSection* get_section(std::string name);

    IniSection* get_last_section();

private:
    FileLoadStatus deserialize_file(std::string fpath);
    LineLoadStatus deserialize_line(std::string line);

    std::vector<IniSection> sections;
};