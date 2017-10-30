#pragma once
#include "bson.hh"

class BSON;

enum Type
{
    DOUBLE,
    STRING,
    DOCUMENT,
    ARRAY,
    BINARY,
    ENULL,
    OBJECT_ID,
    BOOLEAN,
    DATETIME,
    REG_EXP,
    DBPOINTER,
    JAVA_SCRIPT,
    SYMBOL,
    CODE_W_S,
    INT32,
    UINT64,
    INT64,
    DECIMAL128,
    MIN_KEY,
    MAX_KEY
};

class Element
{
protected:
  enum Type type;  

public:
    Element()
        : type(ENULL)
    {}

    Element(enum Type type)
        : type(type)
    {}

    Type GetType();

};

class ElmDouble : public Element
{
private:
    double d;

public:
    ElmDouble(double d)
        : Element(DOUBLE),
        d(d)
    {}

    double GetD();

};

class ElmString : public Element
{
private:
    std::string s;

public:
    ElmString(std::string s)
        : Element(STRING),
        s(s)
    {};

    std::string GetS();
};

class ElmEmbeddedDoc : public Element
{
private:
     BSON* document;

public:
    ElmEmbeddedDoc(BSON* document)
        : Element(DOCUMENT),
        document(document)
    {}

    BSON* GetDocument();
};

class ElmArray : public Element
{
private:
    BSON* document;

public:
    ElmArray(BSON* document)
        : Element(ARRAY),
        document(document)
    {}

    BSON* GetDocument();
};

class ElmBinary : public Element
{
private:
    char subtype;
    std::string data;
    std::string HR_subtype;

public:
    ElmBinary(std::pair<char, std::string> binary)
        : Element(BINARY),
        subtype(binary.first),
        data(binary.second)
    {
        switch(this->subtype)
        {
            case '\x00':
                HR_subtype = "Generic";
                break;
            case '\x01':
                HR_subtype = "Function";
                break;
            case '\x02':
                HR_subtype = "Binary (OLD)";
                break;
            case '\x03':
                HR_subtype = "UUID (OLD)";
                break;
            case '\x04':
                HR_subtype = "UUID";
                break;
            case '\x05':
                HR_subtype = "MD5";
                break;
            case '\x80':
                HR_subtype = "User defined";
                break;
            default:
                break;
        }
    }

    char GetSubType();
    std::string GetData();
    std::string GetHRSubType();
};

class ElmObjectId : public Element
{
private:
    std::string data;

public:
    ElmObjectId(std::string s)
        : Element(OBJECT_ID),
        data(s)
    {}

    std::string GetData();
};

class ElmBoolean : public Element
{
private:
    bool b;

public:
    ElmBoolean(bool b)
        : Element(BOOLEAN),
        b(b)
    {}

    bool GetBoolean();
};

class ElmDatetime : public Element
{
private:
    int32_t date;

public:
    ElmDatetime(int32_t date)
        : Element(DATETIME),
        date(date)
    {}

    int32_t GetDate();
};

class ElmRegExp : public Element
{
private:
    std::string expr;
    std::string opt;

public:
    ElmRegExp(std::pair<std::string, std::string> regExp)
        : Element(REG_EXP),
        expr(regExp.first),
        opt(regExp.second)
    {}

    std::string GetExpr();
    std::string GetOpt();
};

class ElmDbPointer : public Element
{
private:
    std::string s1;
    std::string s2;

public:
    ElmDbPointer(std::pair<std::string, std::string> dbPointer)
        : Element(DBPOINTER),
        s1(dbPointer.first),
        s2(dbPointer.second)
    {}

    std::string GetS1();
    std::string GetS2();
};

class ElmJavaScript : public Element
{
private:
    std::string code;

public:
    ElmJavaScript(std::string code)
        : Element(JAVA_SCRIPT),
        code(code)
    {}

    std::string GetCode();
};

class ElmSymbol : public Element
{
private:
    std::string symb;

public:
    ElmSymbol(std::string symb)
        : Element(SYMBOL),
        symb(symb)
    {}

    std::string GetSymb();
};

class ElmCodeWS : public Element
{
private:
    std::string code;
    BSON* scope;

public:
    ElmCodeWS(std::pair<std::string, BSON*> code_w_s)
        : Element(CODE_W_S),
        code(code_w_s.first),
        scope(code_w_s.second)
    {}

    std::string GetCode();
    BSON* GetScope();
};

class ElmInt32 : public Element
{
private:
    int32_t i;

public:
    ElmInt32(int32_t i)
        : Element(INT32),
        i(i)
    {}

    int32_t GetI();
};

class ElmUInt64 : public Element
{
private:
    uint64_t ui;

public:
    ElmUInt64(uint64_t ui)
        : Element(UINT64),
        ui(ui)
    {}

    uint32_t GetUi();
};

class ElmInt64 : public Element
{
private:
    int64_t i;

public:
    ElmInt64(int64_t i)
        : Element(INT64),
        i(i)
    {}

    int64_t GetI();
};

class ElmDecimal128 : public Element
{
private:
    std::decimal::decimal128 dn;

public:
    ElmDecimal128(std::decimal::decimal128 dn)
        : Element(DECIMAL128),
        dn(dn)
    {}

    std::decimal::decimal128 GetDn();
};

class ElmMinKey : public Element
{
private:

public:
    ElmMinKey()
        : Element(MIN_KEY)
    {}
};

class ElmMaxKey : public Element
{
private:

public:
    ElmMaxKey()
        : Element(MAX_KEY)
    {}
};
