#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <cpr/cpr.h>
#include <cpr/ssl_options.h>
#include "jsoncpp/json/json.h"

#include "sound.hpp"

class SoundFX_API
{
public:
    SoundFX_API() = default;

    std::vector<Sound> get_sounds();

    std::string download_sound();

private:
    std::string API_DOMAIN = "https://localhost:5000/";

#ifdef NDEBUG
    bool DEBUG_MODE = false;
#else
    bool DEBUG_MODE = true;
#endif

};
