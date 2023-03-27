/*! \file
    \brief C/C++ string escapement
 */

#pragma once

#include <string>
#include <iterator>

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace marty_cpp
{



//----------------------------------------------------------------------------
template<typename CharType, typename OutputIterator> inline
void cEscapeStringImpl( const CharType *pStr, OutputIterator outIt )
{
    //typedef StringType                     string_type    ;
    //typedef string_type::value_type        value_type     ;
    //typedef value_type                     char_type      ;

    //string_type resStr;

    auto appendResStr = [&](const char* ccStr)
    {
        for(; *ccStr; ++ccStr)
        {
            //resStr.append(1, (char_type)*ccStr);
            *outIt++ = *ccStr;
        }
    };

    // https://en.cppreference.com/w/cpp/language/escape

    for(; *pStr; ++pStr)
    {
        switch(*pStr)
        {
            case '\'': appendResStr("\\'"); break;
            case '\"': appendResStr("\\\""); break;
            case '\\': appendResStr("\\\\"); break;
            case '\a': appendResStr("\\a"); break;
            case '\b': appendResStr("\\b"); break;
            case '\f': appendResStr("\\f"); break;
            case '\n': appendResStr("\\n"); break;
            case '\r': appendResStr("\\r"); break;
            case '\t': appendResStr("\\t"); break;
            case '\v': appendResStr("\\v"); break;
            // case '\t': appendResStr("\\t"); break;
            default: *outIt++ = *pStr;
        }
    }

}

//----------------------------------------------------------------------------
inline
std::string cEscapeString(const std::string &str)
{
    std::string resStr;
    cEscapeStringImpl(str.c_str(), std::back_inserter(resStr));
    return resStr;
}

//----------------------------------------------------------------------------
inline
std::wstring cEscapeString(const std::wstring &str)
{
    std::wstring resStr;
    cEscapeStringImpl(str.c_str(), std::back_inserter(resStr));
    return resStr;
}

//----------------------------------------------------------------------------
inline
std::string cEscapeString(const char *pStr)
{
    std::string resStr;
    cEscapeStringImpl(pStr, std::back_inserter(resStr));
    return resStr;
}

//----------------------------------------------------------------------------
inline
std::wstring cEscapeString(const wchar_t *pStr)
{
    std::wstring resStr;
    cEscapeStringImpl(pStr, std::back_inserter(resStr));
    return resStr;
}


//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

} // namespace marty_cpp




