#include <assert.h>
#include "bson.hh"


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
    char token = getItValue();
    std::string name = ename();
    Element *elm;

    switch(token)
    {
        case '\x01':
            elm = new ElmDouble(elm_double());
            break;
        case '\x02':
            elm = new ElmString(elm_string());
            break;
        case '\x03':
            elm = new ElmEmbeddedDoc(embeled_document());
            break;
        case '\x04':
            elm = new ElmArray(array_document());
            break;
        case '\x05':
            elm = new ElmBinary(binary());
            break;
        case '\x06':
            elm = new Element();
            break;
        case '\x07':
            elm = new ElmObjectId(objectId());
            break;
        case '\x08':
            elm = new ElmBoolean(elm_bool());
            break;
        case '\x09':
            elm = new ElmDatetime(datetime());
            break;
        case '\x0A':
            elm = new Element();
            break;
        case '\x0B':
            elm = new ElmRegExp(regexp());
            break;
        case '\x0C':
            elm = new ElmDbPointer(dbPointer());
            break;
        case '\x0D':
            elm = new ElmJavaScript(javaScriptCode());
            break;
        case '\x0E':
            elm = new ElmSymbol(symbol());
            break;
        case '\x0F':
            elm = new ElmCodeWS(code_w_s());
            break;
        case '\x10':
            elm = new ElmInt32(elm_int32());
            break;
        case '\x11':
            elm = new ElmUInt64(timestamp());
            break;
        case '\x12':
            elm = new ElmInt32(elm_int64());
            break;
        case '\x13':
            elm = new Element();
            break;
        case '\xFF':
            elm = new ElmMinKey();
            break;
        case '\x7F':
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
    BSON* res =  new BSON(bson_vector, it);
    res->parse();
    
    return res;
}


BSON* BSON::array_document()
{
    BSON* res =  new BSON(bson_vector, it);
    res->parse();

    return res;
}

std::string BSON::objectId()
{
    return byteReader(12);
}

bool BSON::elm_bool()
{
    return getItValue() == '\x01';
}

int32_t BSON::datetime()
{
    return elm_int64();
}

std::pair<std::string, std::string> BSON::regexp()
{
    std::string expr = cstring();
    std::string option = cstring();
   
    return make_pair(expr, option);

}


std::pair<std::string, std::string> BSON::dbPointer()
{
    std::string s1 = elm_string();
    std::string s2 = byteReader(12);

    return make_pair(s1, s2);
}

std::string BSON::javaScriptCode()
{
    return elm_string();
}

std::string BSON::symbol()
{
    return elm_string();
}



double BSON::elm_double()
{
    double res = double();
    char array[8];
    
    for (char &i : array)
    {
        i = getItValue();
    }

    return *((double *) &array[0]);
}

std::string BSON::ename()
{
    return cstring();
}

std::string BSON::elm_string()
{
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
    
    while (*it != '\x00')
    {
        res.push_back(getItValue());
    }
    
    assert(getItValue() == '\x00');
    
    return res;
}

std::pair<char, std::string> BSON::binary()
{
    std::string res;
    int size = elm_int32();
    char subtype = this->subtype();
    res = byteReader(size);

    return std::make_pair(subtype, res);
}

char BSON::subtype()
{
    return getItValue();
}

std::pair<std::string, BSON*> BSON::code_w_s()
{
    int size = elm_int32();
    std::string code = elm_string();
    
    BSON* scope =  new BSON(bson_vector, it);
    scope->parse();

    return std::make_pair(code, scope);
}

int32_t BSON::elm_int32()
{
    int res = int();
    char array[4];
    
    for (char &i : array)
        i = getItValue();

    return *((int *) &array[0]);
}


int64_t BSON::elm_int64()
{
    int64_t res = int64_t();
    char array[8];
    
    for (char &i : array)
        i = getItValue();

    return *((int64_t *) &array[0]);   
}

uint64_t BSON::timestamp()
{
    uint64_t res = uint64_t();
    char array[8];
    
    for (char &i : array)
        i = getItValue();

    return *((uint64_t *) &array[0]);   
}


std::decimal::decimal128 BSON::elm_decimal128()
{
    std::decimal::decimal128 res = std::decimal::decimal128();
    char array[16];

    for (char &i : array)
        i = getItValue();

    return *((std::decimal::decimal128 *) &array[0]);
}

void BSON::parse()
{
    int size = elm_int32();

    while(*it != '\x00')
        element();
}


