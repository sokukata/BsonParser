#include <assert.h>
#include <iostream>
#include "bson.hh"

std::vector<char>::iterator BSON::it;

BSON::BSON(std::vector<char>& bson_vector)
{
    this->bson_vector = bson_vector;
    it = this->bson_vector.begin();
}

BSON::BSON(std::vector<char>& bson_vector, std::vector<char>::iterator& it)
{
    this->bson_vector = bson_vector;
    this->it = it;
}

char BSON::getItValue()
{
    char val = (char) *it;
    
    it++;
    
    return val;
}

std::vector<char>::iterator BSON::getIt()
{
    return this->it;
}

std::string BSON::byteReader(uint32_t size)
{
    std::string res;
    for(int i = size; i > 0; i--)
        res.push_back(getItValue());
    return res;
}

void BSON::element()
{
    std::cout << "element " << std::endl; 
    char token = getItValue();
    std::string name = ename();
    Element *elm;
    switch(token)
    {
        case '\x01':
            std::cout << "01" << std::endl; 
            elm = new ElmDouble(elm_double());
            break;
        case '\x02':
            std::cout << "02" << std::endl;
            elm = new ElmString(elm_string());
            break;
        case '\x03':
            std::cout << "03" << std::endl;
            elm = new ElmEmbeddedDoc(embeled_document());
            break;
        case '\x04':
            std::cout << "04" << std::endl;
            elm = new ElmArray(array_document());
            break;
        case '\x05':
            std::cout << "05" << std::endl;
            elm = new ElmBinary(binary());
            break;
        case '\x06':
            std::cout << "06" << std::endl;
            elm = new Element();
            break;
        case '\x07':
            std::cout << "07" << std::endl;
            elm = new ElmObjectId(objectId());
            break;
        case '\x08':
            std::cout << "08" << std::endl;
            elm = new ElmBoolean(elm_bool());
            break;
        case '\x09':
            std::cout << "09" << std::endl;
            elm = new ElmDatetime(datetime());
            break;
        case '\x0A':
            std::cout << "0A" << std::endl;
            elm = new Element();
            break;
        case '\x0B':
            std::cout << "0B" << std::endl;
            elm = new ElmRegExp(regexp());
            break;
        case '\x0C':
            std::cout << "0C" << std::endl;
            elm = new ElmDbPointer(dbPointer());
            break;
        case '\x0D':
            std::cout << "0D" << std::endl;
            elm = new ElmJavaScript(javaScriptCode());
            break;
        case '\x0E':
            std::cout << "0E" << std::endl;
            elm = new ElmSymbol(symbol());
            break;
        case '\x0F':
            std::cout << "0F" << std::endl;
            elm = new ElmCodeWS(code_w_s());
            break;
        case '\x10':
            std::cout << "10" << std::endl;
            elm = new ElmInt32(elm_int32());
            break;
        case '\x11':
            std::cout << "11" << std::endl;
            elm = new ElmUInt64(timestamp());
            break;
        case '\x12':
            std::cout << "12" << std::endl;
            elm = new ElmInt32(elm_int64());
            break;
        case '\x13':
            std::cout << "13" << std::endl;
            elm = new Element();
            break;
        case '\xFF':
            std::cout << "FF" << std::endl;
            elm = new ElmMinKey();
            break;
        case '\x7F':
            std::cout << "7F" << std::endl;
            elm = new ElmMaxKey();
            break;
        default:
            break;
    }
    grammar_map.insert({name, elm});
    key_index.push_back(name);
}

BSON* BSON::embeled_document()
{
    std::cout << "embeled document" << std::endl;   
    BSON* res =  new BSON(bson_vector, it);
    res->parse();
    return res;
}


BSON* BSON::array_document()
{
    std::cout << "array" << std::endl;
    BSON* res =  new BSON(bson_vector, it);
    res->parse();
    std::cout << "array END" << std::endl;
    return res;
}

std::string BSON::objectId()
{
    std::cout << "object id" << std::endl;
    return byteReader(12);
}

bool BSON::elm_bool()
{
    std::cout << "bool" << std::endl;
    return getItValue() == '\x01';
}

int32_t BSON::datetime()
{
    std::cout << "datetime" << std::endl;
    return elm_int64();
}

std::pair<std::string, std::string> BSON::regexp()
{

    std::cout << "regexp" << std::endl;
    std::string expr = cstring();
    std::string option = cstring();
    return make_pair(expr, option);

}


std::pair<std::string, std::string> BSON::dbPointer()
{
    std::cout << "dbpointer" << std::endl;
    std::string s1 = elm_string();
    std::string s2 = byteReader(12);
    return make_pair(s1, s2);
}

std::string BSON::javaScriptCode()
{
    std::cout << "JSCode" << std::endl;
    return elm_string();
}

std::string BSON::symbol()
{
    std::cout << "symbol" << std::endl;
    return elm_string();
}



double BSON::elm_double()
{
    double res = double();
    char array[8];
    std::cout << "double" << std::endl;
    for (char &i : array)
    {
        i = getItValue();
    }

    return *((double *) &array[0]);
}

std::string BSON::ename()
{
    std::cout << "e_name" << std::endl; 
    std::string s = cstring();
    std::cout << s << std::endl;
    return s;
}

std::string BSON::elm_string()
{
    std::cout << "string" << std::endl; 
    std::string res = "";
    int size = elm_int32();
    for(int i = size; i > 1; i--)
        res.push_back(getItValue());

    assert(getItValue() == '\x00');

    return res;
}

std::string BSON::cstring()
{
    std::string res = "";
    std::cout << "Cstring" << std::endl; 
    while (*it != '\x00')
    {
        res.push_back(getItValue());
    }
    
    assert(getItValue() == '\x00');
    
    return res;
}

std::pair<char, std::string> BSON::binary()
{
    std::cout << "binary" << std::endl; 
    std::string res;
    int size = elm_int32();
    char subtype = this->subtype();
    res = byteReader(size);

    return std::make_pair(subtype, res);
}

char BSON::subtype()
{
    std::cout << "subtype" << std::endl; 
    return getItValue();
}

std::pair<std::string, BSON*> BSON::code_w_s()
{
    std::cout << "code_w_s" << std::endl; 
    int size = elm_int32();
    std::string code = elm_string();
    
    BSON* scope =  new BSON(bson_vector, it);
    scope->parse();

    return std::make_pair(code, scope);
}

int32_t BSON::elm_int32()
{
    std::cout << "int32" << std::endl; 
    int res = int();
    char array[4];
    
    for (char &i : array)
        i = getItValue();

    return *((int *) &array[0]);
}


int64_t BSON::elm_int64()
{
    std::cout << "int64" << std::endl; 
    int64_t res = int64_t();
    char array[8];
    
    for (char &i : array)
        i = getItValue();

    return *((int64_t *) &array[0]);   
}

uint64_t BSON::timestamp()
{
    std::cout << "timestamp" << std::endl; 
    uint64_t res = uint64_t();
    char array[8];
    
    for (char &i : array)
        i = getItValue();

    return *((uint64_t *) &array[0]);   
}


std::decimal::decimal128 BSON::elm_decimal128()
{
    std::cout << "decimal128" << std::endl; 
    std::decimal::decimal128 res = std::decimal::decimal128();
    char array[16];

    for (char &i : array)
        i = getItValue();

    return *((std::decimal::decimal128 *) &array[0]);
}

void BSON::parse()
{
    int size = elm_int32();
    
    std::cout << "Elist" << std::endl;

    while(*it != '\x00')
    {
        std::cout << "it value : " <<std::hex << (int)*it << std::endl; 
        element();
    }
    assert(getItValue() == '\x00');
}


