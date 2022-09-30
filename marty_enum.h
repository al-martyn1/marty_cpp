/*! \file
    \brief Helpers for enum
 */

#pragma once

#include <string>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <iterator>
#include <algorithm>
#include <sstream>

#include <cwctype>
#include <cctype>


//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// Requires
//   <marty_cpp/marty_cpp.h>
//   <map> or <unordered_map>
//   <exception>
//   <stdexcept>
// to be included


//----------------------------------------------------------------------------
#define MARTY_CPP_ENUM_SERIALIZE_BEGIN( enumTypeName, mapType, doUpper )     \
inline                                                                       \
std::string enum_serialize_##enumTypeName( enumTypeName v )                  \
{                                                                            \
    static mapType< enumTypeName, std::string >  _m;                         \
    if (_m.empty())                                                          \
    {

//------------------------------
#define MARTY_CPP_ENUM_SERIALIZE_ITEM( val, valStr )                         \
        _m[val] = valStr

//------------------------------
#define MARTY_CPP_ENUM_SERIALIZE_END( enumTypeName, mapType, doUpper )       \
    }                                                                        \
                                                                             \
    mapType< enumTypeName, std::string >::const_iterator it = _m.find(v);    \
    if (it==_m.end())                                                        \
        return std::string();                                                \
                                                                             \
    return it->second;                                                       \
}

//------------------------------
#define MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( enumTypeName, mapType, doUpper )\
        MARTY_CPP_ENUM_SERIALIZE_BEGIN( enumTypeName, mapType, doUpper )

#define MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( val, valStr )                   \
        MARTY_CPP_ENUM_SERIALIZE_ITEM( val, valStr )

#define MARTY_CPP_ENUM_CLASS_SERIALIZE_END( enumTypeName, mapType, doUpper ) \
        MARTY_CPP_ENUM_SERIALIZE_END( enumTypeName, mapType, doUpper )       \
inline                                                                       \
std::string enum_serialize( enumTypeName v )                                 \
{                                                                            \
    return enum_serialize_##enumTypeName(v);                                 \
}

//------------------------------
#define MARTY_CPP_ENUM_SERIALIZE_SET(enumTypeName, setType)                  \
                                                                             \
inline                                                                       \
std::string enum_serialize_set_##enumTypeName( const setType<enumTypeName> &s, const char *seps = ",|+", char quotChar = '\'' ) \
{                                                                                                                \
    return marty_cpp::serializeEnumSetImpl(s, enum_serialize_##enumTypeName, seps, quotChar);                    \
}                                                                                                                \
                                                                                                                 \
inline                                                                                                           \
std::string enum_serialize_set_##enumTypeName( const setType<enumTypeName> &s, const std::string &seps, char quotChar = '\'' )  \
{                                                                                                                \
    return marty_cpp::serializeEnumSetImpl(s, enum_serialize_##enumTypeName, seps, quotChar);                    \
}

//------------------------------
#define MARTY_CPP_ENUM_CLASS_SERIALIZE_SET(enumTypeName, setType)                                                \
        MARTY_CPP_ENUM_SERIALIZE_SET(enumTypeName, setType)                                                      \
                                                                                                                 \
inline                                                                                                           \
std::string enum_serialize_set( const setType<enumTypeName> &s, const char *seps = ",|+", char quotChar = '\'' ) \
{                                                                                                                \
    return marty_cpp::serializeEnumSetImpl(s, enum_serialize_##enumTypeName, seps, quotChar);                    \
}                                                                                                                \
                                                                                                                 \
inline                                                                                                           \
std::string enum_serialize_set( const setType<enumTypeName> &s, const std::string &seps, char quotChar = '\'' )  \
{                                                                                                                \
    return marty_cpp::serializeEnumSetImpl(s, enum_serialize_##enumTypeName, seps, quotChar);                    \
}

//----------------------------------------------------------------------------





//----------------------------------------------------------------------------
#define MARTY_CPP_ENUM_DESERIALIZE_BEGIN( enumTypeName, mapType, doUpper )   \
inline                                                                       \
enumTypeName enum_deserialize_##enumTypeName( const std::string &str )       \
{                                                                            \
    static bool upperCaseConvert = doUpper ? true : false;                   \
    static mapType< std::string, enumTypeName >  _m;                         \
    if (_m.empty())                                                          \
    {

//------------------------------
#define MARTY_CPP_ENUM_DESERIALIZE_ITEM( val, valStr )                       \
        _m[upperCaseConvert ? marty_cpp::toUpper(std::string(valStr)) : std::string(valStr)] = val

//------------------------------
#define MARTY_CPP_ENUM_DESERIALIZE_END( enumTypeName, mapType, doUpper )     \
    }                                                                        \
                                                                             \
    mapType< std::string, enumTypeName >::const_iterator it = _m.find(upperCaseConvert ? marty_cpp::toUpper(str) : str); \
    if (it==_m.end())                                                        \
        throw std::runtime_error( #enumTypeName " - failed to deserialize value");\
                                                                             \
    return it->second;                                                       \
}                                                                            \
                                                                             \
inline                                                                       \
enumTypeName enum_deserialize_##enumTypeName( const std::string &str, enumTypeName defVal ) \
{                                                                            \
    try                                                                      \
    {                                                                        \
        return enum_deserialize_##enumTypeName( str );                       \
    }                                                                        \
    catch(...)                                                               \
    {                                                                        \
    }                                                                        \
                                                                             \
    return defVal;                                                           \
}

//------------------------------
#define MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( enumTypeName, mapType, doUpper )\
        MARTY_CPP_ENUM_DESERIALIZE_BEGIN( enumTypeName, mapType, doUpper )

#define MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( val, valStr ) \
        MARTY_CPP_ENUM_DESERIALIZE_ITEM( val, valStr )

#define MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( enumTypeName, mapType, doUpper ) \
        MARTY_CPP_ENUM_DESERIALIZE_END( enumTypeName, mapType, doUpper )     \
inline                                                                       \
void enum_deserialize( enumTypeName &deserializeTo, const std::string &str ) \
{                                                                            \
    deserializeTo = enum_deserialize_##enumTypeName(str);                    \
}                                                                            \
                                                                             \
inline                                                                       \
enumTypeName enum_deserialize( const std::string &str, enumTypeName defVal ) \
{                                                                            \
    return enum_deserialize_##enumTypeName(str, defVal);                     \
}

//------------------------------
#define MARTY_CPP_ENUM_DESERIALIZE_SET(enumTypeName, setType)                \
                                                                             \
inline                                                                       \
void enum_deserialize_set_##enumTypeName( setType<enumTypeName> &s, const std::string &str, const char *seps = ",|+", char quotChar = '\'' ) \
{                                                                            \
    auto deser = [](const std::string &str)                                  \
    { return enum_deserialize_##enumTypeName(str); };                        \
    return marty_cpp::deserializeEnumSetImpl(s, str, deser, seps, quotChar); \
}                                                                            \
                                                                             \
inline                                                                       \
void enum_deserialize_set_##enumTypeName( setType<enumTypeName> &s, const std::string &str, const std::string &seps, char quotChar = '\'' )  \
{                                                                            \
    auto deser = [](const std::string &str)                                  \
    { return enum_deserialize_##enumTypeName(str); };                        \
    return marty_cpp::deserializeEnumSetImpl(s, str, deser, seps, quotChar); \
}

//------------------------------
#define MARTY_CPP_ENUM_CLASS_DESERIALIZE_SET(enumTypeName, setType)          \
        MARTY_CPP_ENUM_DESERIALIZE_SET(enumTypeName, setType)                \
                                                                             \
inline                                                                       \
void enum_deserialize_set( setType<enumTypeName> &s, const std::string &str, const char *seps = ",|+", char quotChar = '\'' ) \
{                                                                            \
    return enum_deserialize_set_##enumTypeName(s, str, seps, quotChar);      \
}                                                                            \
                                                                             \
inline                                                                       \
void enum_deserialize_set( setType<enumTypeName> &s, const std::string &str, const std::string &seps, char quotChar = '\'' )  \
{                                                                            \
    return enum_deserialize_set_##enumTypeName(s, str, seps, quotChar);      \
}

//----------------------------------------------------------------------------






//----------------------------------------------------------------------------
namespace marty_cpp
{


#ifndef MARTY_CPP_TO_UPPER_TO_LOWER_DECLARED
#define MARTY_CPP_TO_UPPER_TO_LOWER_DECLARED

inline bool    isLower( char ch )     { return (ch>='a' && ch<='z'); }
inline bool    isUpper( char ch )     { return (ch>='A' && ch<='Z'); }

inline bool    isLower( wchar_t ch )  { return (ch>=L'a' && ch<=L'z'); }
inline bool    isUpper( wchar_t ch )  { return (ch>=L'A' && ch<=L'Z'); }

inline char    toLower( char ch )     { return isUpper(ch) ? ch-'A'+'a' : ch; }
inline char    toUpper( char ch )     { return isLower(ch) ? ch-'a'+'A' : ch; }

inline wchar_t toLower( wchar_t ch )  { return isUpper(ch) ? ch-L'A'+L'a' : ch; }
inline wchar_t toUpper( wchar_t ch )  { return isLower(ch) ? ch-L'a'+L'A' : ch; }

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toLower( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr;
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toLower(*it) );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toUpper( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::basic_string< CharT, Traits, Allocator > resStr;
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        resStr.append( 1, toUpper(*it) );
    }

    return resStr;
}

#endif // MARTY_CPP_TO_UPPER_TO_LOWER_DECLARED



// Прямо сейчас мне десериализация enum'ов не нужна. Допишу потом.
#if 0
template<typename StringType, typename HandlerType> inline
void splitEnumSetStringHelper( const StringType &str, const StringType &seps, typename StringType::value_type quotChar, HandlerType handler )
{
    typedef typename StringType::value_type   CharType;
    typedef typename StringType::size_type    PosType ;

    if (seps.empty()) // разделители не заданы вообще - строку не надо/не можем разделить
    {
        handler(str);
        return;
    }

    auto isPosValid = [&](auto pos)
        {
            return pos!=str.npos && pos!=str.size();
        };

    const CharType  spaces[] = { (CharType)' ', (CharType)'\t', 0 };

    PosType startPos = str.find_first_not_of(spaces, 0);
    while(isPosValid(startPos))
    {
        bool hasStartQuot = false;

        if (str[startPos]==quotChar)
        {
        }

    }
    
}
#endif


//-----------------------------------------------------------------------------
template< typename EnumSetType
        , typename EnumTypeSerializer
        > inline
std::string serializeEnumSetImpl( const EnumSetType &enumValsSet
                                , EnumTypeSerializer serializer
                                , const char *seps // используем только первый элемент
                                , char quotChar = '\''
                                )
{
    const char sepChar = (seps && seps[0]) ? '+' : seps[0];

    std::string res;

    for( auto enumVal : enumValsSet )
    {
        auto enumValStr = serializer(enumVal);

        if (enumValStr.empty()) // нужно ли сериализовать значения, которые сериализовались в пустую строку? Бросить исключение? Или добавить в кавычках?
            continue;

        if (!res.empty())
            res.append(1,sepChar);

        bool quoteVal = (enumValStr.find_first_of(' ')!=enumValStr.npos) ? true : false;

        if (!quoteVal && enumValStr.size()==1 && enumValStr[0]==sepChar)
            quoteVal = true;

        if (quotChar==0)
            quoteVal = false;

        if (quoteVal)
            res.append(1,quotChar);

        res.append(enumValStr);

        if (quoteVal)
            res.append(1,quotChar);
    }

    return res;
}

//-----------------------------------------------------------------------------
template< typename EnumSetType
        , typename EnumTypeSerializer
        > inline
std::string serializeEnumSetImpl( const EnumSetType &enumValsSet
                                , EnumTypeSerializer serializer
                                , const std::string &seps // используем только первый элемент
                                , char quotChar = '\''
                                )
{
    return serializeEnumSetImpl(enumValsSet, serializer, seps.c_str(), quotChar);
}

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
template< typename EnumSetType
        , typename EnumTypeDeserializer
        > inline
void deserializeEnumSetImpl( const EnumSetType &enumValsSet
                           , const std::string &str
                           , EnumTypeDeserializer deserializer
                           , const char *seps
                           , char quotChar = '\''
                           )
{
}

//-----------------------------------------------------------------------------
template< typename EnumSetType
        , typename EnumTypeDeserializer
        > inline
void deserializeEnumSetImpl( const EnumSetType &enumValsSet
                           , const std::string &str
                           , EnumTypeDeserializer deserializer
                           , const std::string &seps
                           , char quotChar = '\''
                           )
{
    return deserializeEnumSetImpl(enumValsSet, str, deserializer, seps.c_str(), quotChar);
}



//-----------------------------------------------------------------------------
} // namespace marty_cpp





