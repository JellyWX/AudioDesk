#include <iostream>
#include <sqlite3.h>
#include <fstream>

enum CacheStatus
{
    NoCache, Caching,
};

class AudioManager
{
public:
    AudioManager();

    CacheStatus set_cache_location(std::string path);

    void stream_sound(std::string name, bool path);

    void add_sound(std::string path);

private:
    sqlite3* db

    bool caching = false;


    void cache_sound();

    std::vector<char> cast_sound_to_pcm();

    std::string search_cache(std::string name);
};