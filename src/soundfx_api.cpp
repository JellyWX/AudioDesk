#include "soundfx_api.hpp"

std::vector<Sound> SoundFX_API::get_sounds(unsigned short page_number, const std::optional<std::string>& search_query)
{
    std::cout << "Requesting page " << page_number << " of sounds from the API" << std::endl;

    std::vector<Sound> sounds;

    std::stringstream full_url;

    if (search_query.has_value())
        full_url << API_SEARCH << "?page=" << page_number << "&query=" << search_query.value();
    else
        full_url << API_SEARCH << "?page=" << page_number;

    cpr::Response api_response = cpr::Get(cpr::Url{full_url.str()});

    this->set_connected(api_response.status_code > 0);

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
            this->max_page = root["last_page"].asUInt();

            Json::Value sound_list = root["sounds"];

            for (Json::Value &sound : sound_list)
            {
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
    std::string meta_path = get_usable_path_for("cache/id_" + id_str + ".meta");

    cpr::Response api_response = cpr::Get(cpr::Url{API_DOWNLOAD + "?sound_id=" + id_str});

    this->set_connected(api_response.status_code > 0);

    if ( api_response.status_code == 200 )
    {
        Json::CharReaderBuilder builder;
        Json::Value root;
        JSONCPP_STRING err;

        const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

        if (!reader->parse(api_response.text.c_str(),api_response.text.c_str() + api_response.text.length(), &root, &err))
        {
            std::cerr << "Failed to read JSON response from SoundFX API" << std::endl;
        }
        else
        {
            std::string source = base64_decode(root["source"].asString());

            std::fstream file, meta_file;

            file.open(path, std::ios::out);
            meta_file.open(meta_path, std::ios::out);

            if (file.is_open() && meta_file.is_open())
            {
                file << source;

                Json::Value meta_root;

                meta_root["id"] = root["id"];
                meta_root["name"] = root["name"];

                meta_file << meta_root;
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

std::vector<Sound> SoundFX_API::get_next_page()
{
    if (this->current_page < this->max_page)
        ++this->current_page;

    std::vector<Sound> sounds = this->get_sounds(this->current_page, this->query);

    if ( sounds.empty() )
        --this->current_page;

    return sounds;
}

std::vector<Sound> SoundFX_API::get_current_page()
{
    return this->get_sounds(this->current_page, this->query);
}

void SoundFX_API::set_query(std::string new_query)
{
    if ( new_query.length() > 0 )
        this->query = std::move(new_query);
    else
        this->query = std::nullopt;

    this->current_page = 0;
    this->max_page = -1;
}

void SoundFX_API::set_connected(bool value)
{
    if (value != this->connected)
    {
        if (value)
            this->m_signal_connected.emit();
        else
            this->m_signal_disconnected.emit();

        this->connected = value;
    }
}
