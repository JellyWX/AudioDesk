#include <string>

template <class V>
class IniEntry
{
public:
    IniEntry(std::string n, V d) : name(n), default_value(d) {};

    V get_value() { if (value == NULL) return default_value else return value };

    std::string name;

private:
    V value = NULL;

    V default_value;
};