#pragma once

#include <string>

class Sound
{
public:
    Sound(std::string name, unsigned short plays);

    std::string get_name() const { return name; }

    unsigned short get_plays() const { return plays; }

private:
    std::string name;

    unsigned short plays;
};
