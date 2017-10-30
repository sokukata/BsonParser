#include "element.hh"

Type Element::GetType()
{
    return type;
}

double ElmDouble::GetD()
{
    return d;
}

std::string ElmString::GetS()
{
    return s;
}

BSON* ElmEmbeddedDoc::GetDocument()
{
    return document;
}

BSON* ElmArray::GetDocument()
{
    return document;
}

char ElmBinary::GetSubType()
{
    return subtype;
}

std::string ElmBinary::GetData()
{
    return data;
}

std::string ElmBinary::GetHRSubType()
{
    return HR_subtype;
}

std::string ElmObjectId::GetData()
{
    return data;
}

bool ElmBoolean::GetBoolean()
{
    return b; 
}


int32_t ElmDatetime::GetDate()
{
    return date;
}

std::string ElmRegExp::GetExpr()
{
    return expr;
}

std::string ElmRegExp::GetOpt()
{
    return opt;
}

std::string ElmDbPointer::GetS1()
{
    return s1;
}

std::string ElmDbPointer::GetS2()
{
    return s2;
}

std::string ElmJavaScript::GetCode()
{
    return code;
}

std::string ElmSymbol::GetSymb()
{
    return symb;
}

std::string ElmCodeWS::GetCode()
{
    return code;
}

BSON* ElmCodeWS::GetScope()
{
    return scope;
}

int32_t ElmInt32::GetI()
{
    return i;
}

uint32_t ElmUInt64::GetUi()
{
    return ui;
}

int64_t ElmInt64::GetI()
{
    return i;
}

std::decimal::decimal128 ElmDecimal128::GetDn()
{
    return dn;
}

