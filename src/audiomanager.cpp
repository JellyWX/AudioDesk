#include "audiomanager.hpp"

AudioManager::AudioManager()
{
}

CacheStatus AudioManager::set_cache_location(std::string path)
{
    int result = sqlite3_open(path, this->db);

    if (result != SQLITE_OK)
    {
        return NoCache;
    }
    else
    {
        this->caching = true;
        return Caching;
    }
}

void AudioManager::stream_sound(std::string name, bool path)
{
    std::string fpath = "";
    if ( this->caching and not path )
    {
        fpath = this->search_cache(name);
    }
    else
    {
        fpath = name;
    }
}

std::string AudioManager::search_cache(std::string name)
{
    sqlite3_
}