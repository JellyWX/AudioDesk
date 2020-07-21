#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <utility>
#include <optional>

#include <cpr/cpr.h>
#include "jsoncpp/json/json.h"
#include <gtkmm.h>

#include "setup.hpp"

#include "sound.hpp"
#include "utils.hpp"
#include "base64.h"

class SoundFX_API
{
public:
    explicit SoundFX_API(Setup &config):
        API_ROOT(config.API_ROOT), API_SEARCH(config.API_SEARCH), API_DOWNLOAD(config.API_DOWNLOAD) {};

    typedef sigc::signal<void> type_signal_connected;
    typedef sigc::signal<void> type_signal_disconnected;

    type_signal_connected signal_connected() { return m_signal_connected; };
    type_signal_disconnected signal_disconnected() { return m_signal_disconnected; };

    std::string download_sound(unsigned int id);

    std::vector<Sound> get_next_page();
    std::vector<Sound> get_current_page();

    void set_query(std::string new_query);

private:
    type_signal_connected m_signal_connected;
    type_signal_disconnected m_signal_disconnected;

    std::vector<Sound> get_sounds(unsigned short page_number, const std::optional<std::string>& search_query = std::nullopt);

    std::string API_ROOT = "http://localhost:5000/api";

    std::string API_SEARCH = API_ROOT + "/search/";
    std::string API_DOWNLOAD = API_ROOT + "/sound/";

    unsigned int current_page = 0;
    unsigned int max_page = -1;

    void set_connected(bool value);

    bool connected = true;

    std::optional<std::string> query;
};
