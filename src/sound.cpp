#include "sound.hpp"

#include <utility>

Sound::Sound(std::string name, unsigned short plays): name(std::move(name)), plays(plays) {}
