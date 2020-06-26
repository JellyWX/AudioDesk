#include "soundfx_api.hpp"

std::vector<Sound> SoundFX_API::get_sounds()
{
    std::vector<Sound> sounds;

    cpr::Response api_response;

    if ( DEBUG_MODE )
    {
        auto sslOpts = cpr::Ssl(cpr::ssl::VerifyHost(false));
        api_response = cpr::Get(cpr::Url(API_DOMAIN + "api/search"), sslOpts);
    }
    else
    {
        api_response = cpr::Get(cpr::Url(API_DOMAIN + "api/search"));
    }


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
            }
        }
    }

    return sounds;
}
