#pragma once
#include <vector>
#include <map>
#include "node.hh"

class BSON 
{
private:
    std::map<std::string, Node*> grammar_map;
    
    std::pair<std::string, Node*> element(std::vector<char>::iterator *it);
    std::vector<char> ename(std::vector<char>::iterator *it);
    std::vector<char> cstring(std::vector<char>::iterator *it);
    char subtype(std::vector<char>::iterator *it);
    

    double elm_double(std::vector<char>::iterator *it); //\x01 
    std::string string(std::vector<char>::iterator *it);
    BSON embeled_document(std::vector<char>::iterator *it);
    BSON array_document(std::vector<char>::iterator *it);
    std::string binary(std::vector<char>::iterator *it);
    //\x06 -> null
    std::string objectId(std::vector<char>::iterator *it);
    bool elm_bool(std::vector<char>::iterator *it);
    std::string datetime(std::vector<char>::iterator *it);
    // \x0A -> null
    std::string regexp(std::vector<char>::iterator *it);
    std::string dbPointer(std::vector<char>::iterator *it);
    std::string javaScriptCode(std::vector<char>::iterator *it);
    std::string symbol(std::vector<char>::iterator *it);
    std::string code_w_s(std::vector<char>::iterator *it);
    int elm_int32(std::vector<char>::iterator *it);
    unsigned long timestamp(std::vector<char>::iterator *it);
    long elm_int64(std::vector<char>::iterator *it);
    // \x13 -> decimal128 : lire spec
    // \xFF -> Min key
    // \x7F -> Max keyy


public:

    BSON(std::vector<char> bson_vector);
    void Dump();
    
    
    

};
