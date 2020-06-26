#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <cpr/cpr.h>
#include <cpr/ssl_options.h>
#include "jsoncpp/json/json.h"

#include "sound.hpp"
#include "utils.hpp"
#include "base64.h"

class SoundFX_API
{
public:
    SoundFX_API() = default;

    std::vector<Sound> get_sounds(unsigned short page_number);

    std::string download_sound(unsigned int id);

private:
    std::string API_ROOT = "https://localhost:5000/";

    std::string API_SEARCH = API_ROOT + "/api/search/";
    std::string API_DOWNLOAD = API_ROOT + "/api/sound/";
};
