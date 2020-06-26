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

std::string SoundFX_API::download_sound(unsigned int id)
{
    std::string id_str = std::to_string(id);
    std::string path = get_usable_path_for("cache/id_" + id_str);

    cpr::Response api_response = cpr::Get(cpr::Url{API_DOWNLOAD + "?sound_id=" + id_str});

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
            std::string source = base64_decode(root["source"].asString());

            std::fstream file;

            file.open(path, std::ios::out);

            if (file.is_open())
            {
                file << source;
            }
            else
            {
                std::cerr << "Failed to write sound to file" << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Bad API response: " << api_response.status_code << "; " << api_response.text << std::endl;
    }

    return path;
}
