#include "bson.hh"


BSON::BSON(std::vector<char> bson_vector)
{
    std::vector<char>::iterator it = bson_vector.begin();

    while(*it != '\x00')
    {
        this->grammar_map.insert({element(&it).first, element(&it).second}); 
    }
}


