#include "sound.hpp"

#include <utility>

Sound::Sound(std::string name, unsigned short plays, unsigned int id): name(std::move(name)), plays(plays), id(id) {}
