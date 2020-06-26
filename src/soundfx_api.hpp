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

    std::vector<Sound> get_sounds(unsigned short page_number);

    std::string download_sound();

private:
    std::string API_DOMAIN = "https://localhost:5000/";

    std::string API_SEARCH = "http://localhost:5000/api/search/";

};
