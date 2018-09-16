#pragma once
#include <vector>
#include <map>
#include <gmp.h>
#include <decimal/decimal>
#include <iostream>
#include "element.hh"


class Element;

class BSON 
{
private:
    std::vector<char> bson_vector;
    static std::vector<char>::iterator it;
    std::map<std::string, Element*> grammar_map;
    std::vector<std::string> key_index;
    
    void element();
    std::string ename(); //done
    std::string cstring(); //done
    char subtype(); //done
    

    double elm_double(); // done 
    std::string elm_string(); //done
    BSON* embeled_document(); //done
    BSON* array_document(); //done 
    std::pair<char, std::string> binary(); //done
    //\x06 -> null
    std::string objectId(); //done
    bool elm_bool(); //done 
    int32_t datetime(); //done
    // \x0A -> null
    std::pair<std::string, std::string> regexp(); //done 
    std::pair<std::string, std::string> dbPointer(); //done
    std::string javaScriptCode(); //done 
    std::string symbol(); //done
    std::pair<std::string, BSON*> code_w_s(); //done 
    int32_t elm_int32(); // done
    uint64_t timestamp();// done
    int64_t elm_int64();// done
    std::decimal::decimal128 elm_decimal128(); //done
    
    // \x13 -> decimal128 : lire spec
    // \xFF -> Min key
    // \x7F -> Max key
    
    char getItValue(); //get iterator value and increment iterator
    std::string byteReader(uint32_t size);

public:

    BSON(std::vector<char>& bson_vector);
    BSON(std::vector<char>& bson_vector, std::vector<char>::iterator& it);
    void parse();
    void Dump();

    std::vector<char>::iterator getIt();
};

