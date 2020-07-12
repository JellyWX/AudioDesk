#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include <optional>

#include <cpr/cpr.h>
#include "jsoncpp/json/json.h"

#include "sound.hpp"
#include "utils.hpp"
#include "base64.h"

class SoundFX_API
{
public:
    SoundFX_API() = default;


    std::string download_sound(unsigned int id);

    void next_page();
    void prev_page();

    std::vector<Sound> get_page();

    void set_query(std::string new_query);

private:
    std::vector<Sound> get_sounds(unsigned short page_number, const std::optional<std::string>& search_query = std::nullopt);

    std::string API_ROOT = "http://localhost:5000";

    std::string API_SEARCH = API_ROOT + "/api/search/";
    std::string API_DOWNLOAD = API_ROOT + "/api/sound/";

    unsigned int current_page = 0;
    unsigned int max_page = -1;

    std::optional<std::string> query;
};
