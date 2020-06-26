#pragma once

#include <string>

class Sound
{
public:
    Sound(std::string name, unsigned short plays, unsigned int id);

    std::string get_name() const { return name; }

    unsigned short get_plays() const { return plays; }

    unsigned int get_id() const { return id; }

private:
    std::string name;

    unsigned short plays;

    unsigned int id;
};
