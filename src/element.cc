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

std::string ElmDecimal128::ToString(std::decimal::decimal128 dn)
{
    long double d(std::decimal::decimal128_to_double(dn));
    std::ostringstream oss;
    oss << std::scientific << std::setprecision(37) << d;
    return oss.str();
}

