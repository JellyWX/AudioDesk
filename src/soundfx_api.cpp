#include "soundfx_api.hpp"

std::vector<Sound> SoundFX_API::get_sounds(unsigned short page_number)
{
    std::cout << "Requesting page " << page_number << " of sounds from the API" << std::endl;

    std::vector<Sound> sounds;

    cpr::Response api_response = cpr::Get(cpr::Url{API_SEARCH});

    if ( api_response.status_code == 200 )
    {
        Json::Value root;
        Json::CharReaderBuilder builder;
        JSONCPP_STRING err;

        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        if (!reader->parse(api_response.text.c_str(),api_response.text.c_str() + api_response.text.length(), &root, &err))
        {
            std::cerr << "Failed to read JSON response from SoundFX API" << std::endl;
        }
        else
        {
            Json::Value sound_list = root["sounds"];

            for (Json::Value &sound : sound_list)
            {
                std::cout << sound["name"] << std::endl;

                sounds.emplace_back(sound["name"].asString(), sound["plays"].asUInt(), sound["id"].asUInt());
            }
        }
    }
    else
    {
        std::cerr << "Bad API response: " << api_response.status_code << "; " << api_response.text << std::endl;
    }

    std::cout << "Got " << sounds.size() << " sounds" << std::endl;
    return sounds;
}
