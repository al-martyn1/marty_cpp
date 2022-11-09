/*! \file
    \brief C++ (also good for other langs) identifiers style autodetect and format
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
namespace marty_cpp
{




//----------------------------------------------------------------------------
#ifndef MARTY_CPP_MAKE_STRING_DEFINED
#define MARTY_CPP_MAKE_STRING_DEFINED
//----------------------------------------------------------------------------
template<typename StringType> inline StringType make_string( )
{
    return StringType();
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из std::wstring (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const std::wstring &str )
{
    StringType res;
    for( std::wstring::const_iterator it = str.begin(); it != str.end(); ++it)
        res.append(1, (typename StringType::value_type)*it );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из std::string (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const std::string &str )
{
    StringType res;
    for( std::string::const_iterator it = str.begin(); it != str.end(); ++it)
        res.append(1, (typename StringType::value_type)*it );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из const wchar_t* (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const wchar_t *str )
{
    StringType res;
    for(; *str; str++)
        res.append(1, (typename StringType::value_type)*str );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из const char* (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( const char *str )
{
    StringType res;
    for(; *str; str++)
        res.append(1, (typename StringType::value_type)*str );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из sz wchar_t'ов (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( wchar_t ch, size_t sz = 1 )
{
    StringType res;
    res.append(sz, (typename StringType::value_type)ch );
    return res;
}

//-----------------------------------------------------------------------------
//! Создаёт строку StringType из sz char'ов (работает только для базового диапазона ASCII).
template<typename StringType> inline StringType make_string( char ch, size_t sz = 1 )
{
    StringType res;
    res.append(sz, (typename StringType::value_type)ch );
    return res;
}

//-----------------------------------------------------------------------------

#endif // MARTY_CPP_MAKE_STRING_DEFINED

//----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
// template<typename StringType> inline
// StringType toUpperCopy(StringType str)
// {
//     std::transform( str.begin(), str.end(), str.begin()
//                   , [](typename StringType::value_type ch)
//                     {
//                         typedef typename StringType::value_type CharType;
//                         return ch>=(CharType)'a' && ch<=(CharType)'z'
//                              ? ch-(CharType)'a'+(CharType)'A'
//                              : ch
//                              ;
//                     }
//                   );
//     return str;
// }

//-----------------------------------------------------------------------------




//----------------------------------------------------------------------------
enum class NameStyle
{
    begin                          = 0,

    unknownStyle                   = begin,
    defaultStyle                   = begin,
    invalidName                    = begin,
    invalid                        = begin,

    all                            , // Для enum генератора, генерить все имена

    hyphenStyle                    , // Для enum генератора, генерить имена, как cpp, только с минусом вместо подчеркивания
    cppStyle                       ,
    camelStyle                     ,
    pascalStyle                    ,
    hyphenCamelMixedStyle          ,
    hyphenPascalMixedStyle         ,
    cppCamelMixedStyle             ,
    cppPascalMixedStyle            ,
    defineStyle                    ,
    sqlStyle                         = defineStyle,

    // keep underscores while formatting
    hyphenUnderscoredStyle         ,

    cppUnderscoredStyle            ,
    camelUnderscoredStyle          ,
    pascalUnderscoredStyle         ,
    hyphenCamelMixedUnderscoredStyle  ,
    hyphenPascalMixedUnderscoredStyle ,
    cppCamelMixedUnderscoredStyle  ,
    cppPascalMixedUnderscoredStyle ,
    defineUnderscoredStyle         , 
    sqlUnderscoredStyle            = defineUnderscoredStyle,

    end

};

//------------------------------
struct NameStyleLess
{
    bool operator()( NameStyle n1, NameStyle n2 ) const
    {
        return (int)n1 < (int)n2;
    }
};

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
enum class NameCharClass
{
    unknown      ,
    digit        ,
    lower        ,
    upper        ,
    underscore
};

//------------------------------
template<typename StringType> inline
StringType toString( NameStyle ns, const StringType &unknownStr = make_string<StringType>("UnknownStyle") /* for compat */)
{
    switch(ns)
    {
        case NameStyle::invalidName                    : return make_string<StringType>("InvalidName");

        case NameStyle::all                            : return make_string<StringType>("All");

        case NameStyle::hyphenStyle                    : return make_string<StringType>("HyphenStyle");
        case NameStyle::cppStyle                       : return make_string<StringType>("CppStyle");
        case NameStyle::camelStyle                     : return make_string<StringType>("CamelStyle");
        case NameStyle::pascalStyle                    : return make_string<StringType>("PascalStyle");
        case NameStyle::hyphenCamelMixedStyle          : return make_string<StringType>("HyphenCamelMixedStyle");
        case NameStyle::hyphenPascalMixedStyle         : return make_string<StringType>("HyphenPascalMixedStyle");
        case NameStyle::cppCamelMixedStyle             : return make_string<StringType>("CppCamelMixedStyle");
        case NameStyle::cppPascalMixedStyle            : return make_string<StringType>("CppPascalMixedStyle");
        case NameStyle::defineStyle                    : return make_string<StringType>("DefineStyle");

        case NameStyle::hyphenUnderscoredStyle         : return make_string<StringType>("HyphenUnderscoredStyle");
        case NameStyle::cppUnderscoredStyle            : return make_string<StringType>("CppUnderscoredStyle");
        case NameStyle::camelUnderscoredStyle          : return make_string<StringType>("CamelUnderscoredStyle");
        case NameStyle::pascalUnderscoredStyle         : return make_string<StringType>("PascalUnderscoredStyle");
        case NameStyle::hyphenCamelMixedUnderscoredStyle  : return make_string<StringType>("HyphenCamelMixedUnderscoredStyle");
        case NameStyle::hyphenPascalMixedUnderscoredStyle : return make_string<StringType>("HyphenPascalMixedUnderscoredStyle");
        case NameStyle::cppCamelMixedUnderscoredStyle  : return make_string<StringType>("CppCamelMixedUnderscoredStyle");
        case NameStyle::cppPascalMixedUnderscoredStyle : return make_string<StringType>("CppPascalMixedUnderscoredStyle");
        case NameStyle::defineUnderscoredStyle         : return make_string<StringType>("DefineUnderscoredStyle");

        default                                        : return unknownStr;
    }
}

//------------------------------
template<typename StringType> inline
NameStyle fromString(const StringType &str, NameStyle defVal = NameStyle::invalid)
{
    static std::unordered_map<StringType,NameStyle> m;

    auto toUpper = [](StringType str)
    {
        std::transform( str.begin(), str.end(), str.begin()
                      , [](typename StringType::value_type ch)
                        {
                            typedef typename StringType::value_type CharType;
                            return ch>=(CharType)'a' && ch<=(CharType)'z'
                                 ? ch-(CharType)'a'+(CharType)'A'
                                 : ch
                                 ;
                        }
                      );
        return str;
    };

    if (m.empty())
    {
        for( unsigned i=(unsigned)NameStyle::begin; i!=(unsigned)NameStyle::end; ++i)
        {
            auto name = toString<StringType>((NameStyle)i, make_string<StringType>());
            if (name.empty())
                continue;
            name = toUpper(name);
            m[name] = (NameStyle)i;
        }
    }

    //std::unordered_map<StringType,NameStyle>::const_iterator 
    auto it = m.find(toUpper(str));
    if (it==m.end())
        return defVal;

    return it->second;
}

//------------------------------
inline NameStyle getNameStyleUnderlinedBuddy( NameStyle ns )
{
    switch(ns)
    {
        case NameStyle::hyphenStyle            : return NameStyle::hyphenUnderscoredStyle        ;
        case NameStyle::cppStyle               : return NameStyle::cppUnderscoredStyle           ;
        case NameStyle::camelStyle             : return NameStyle::camelUnderscoredStyle         ;
        case NameStyle::pascalStyle            : return NameStyle::pascalUnderscoredStyle        ;
        case NameStyle::hyphenCamelMixedStyle  : return NameStyle::hyphenCamelMixedUnderscoredStyle ;
        case NameStyle::hyphenPascalMixedStyle : return NameStyle::hyphenPascalMixedUnderscoredStyle;
        case NameStyle::cppCamelMixedStyle     : return NameStyle::cppCamelMixedUnderscoredStyle ;
        case NameStyle::cppPascalMixedStyle    : return NameStyle::cppPascalMixedUnderscoredStyle;
        case NameStyle::defineStyle            : return NameStyle::defineUnderscoredStyle        ;

        default                                : return ns; // return untouched value
    }
}

//------------------------------
inline NameStyle getNameStyleUnderscoredBuddy( NameStyle ns )
{
    return getNameStyleUnderlinedBuddy(ns);
}

//------------------------------
inline NameStyle getNameStyleNotUnderlinedBuddy( NameStyle ns )
{
    switch(ns)
    {
        case NameStyle::hyphenUnderscoredStyle            : return NameStyle::hyphenStyle        ;
        case NameStyle::cppUnderscoredStyle               : return NameStyle::cppStyle           ;
        case NameStyle::camelUnderscoredStyle             : return NameStyle::camelStyle         ;
        case NameStyle::pascalUnderscoredStyle            : return NameStyle::pascalStyle        ;
        case NameStyle::hyphenCamelMixedUnderscoredStyle  : return NameStyle::hyphenCamelMixedStyle ;
        case NameStyle::hyphenPascalMixedUnderscoredStyle : return NameStyle::hyphenPascalMixedStyle;
        case NameStyle::cppCamelMixedUnderscoredStyle     : return NameStyle::cppCamelMixedStyle ;
        case NameStyle::cppPascalMixedUnderscoredStyle    : return NameStyle::cppPascalMixedStyle;
        case NameStyle::defineUnderscoredStyle            : return NameStyle::defineStyle        ;

        default                                           : return ns; // return untouched value
    }
}

//------------------------------
inline NameStyle getNameStyleNotUnderscoredBuddy( NameStyle ns )
{
    return getNameStyleNotUnderlinedBuddy(ns);
}

//------------------------------
inline NameStyle getNameStyleBuddy( NameStyle ns, bool underlinedBuddy )
{
    if (underlinedBuddy)
        return getNameStyleUnderlinedBuddy(ns);
    else
        return getNameStyleNotUnderlinedBuddy(ns);
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
// typedef std::set< NameStyle, NameStyleLess, std::allocator<NameStyle> > NameStyleSet;
typedef std::set< NameStyle, NameStyleLess > NameStyleSet;

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
inline NameStyleSet makeAllNameStylesSet( bool onlyValidStyles=false )
{
    NameStyleSet allNameStyles;

    if (!onlyValidStyles)
    {
        allNameStyles.insert( NameStyle::unknownStyle               );
        allNameStyles.insert( NameStyle::invalidName                );
        allNameStyles.insert( NameStyle::all                        );
    }
    
    allNameStyles.insert( NameStyle::hyphenStyle                    );
    allNameStyles.insert( NameStyle::cppStyle                       );
    allNameStyles.insert( NameStyle::camelStyle                     );
    allNameStyles.insert( NameStyle::pascalStyle                    );
    
    allNameStyles.insert( NameStyle::hyphenCamelMixedStyle          );
    allNameStyles.insert( NameStyle::hyphenPascalMixedStyle         );
    allNameStyles.insert( NameStyle::cppCamelMixedStyle             );
    allNameStyles.insert( NameStyle::cppPascalMixedStyle            );
    allNameStyles.insert( NameStyle::defineStyle                    );
    allNameStyles.insert( NameStyle::hyphenUnderscoredStyle         );
    allNameStyles.insert( NameStyle::cppUnderscoredStyle            );
    allNameStyles.insert( NameStyle::camelUnderscoredStyle          );
    allNameStyles.insert( NameStyle::pascalUnderscoredStyle         );

    allNameStyles.insert( NameStyle::hyphenCamelMixedUnderscoredStyle );
    allNameStyles.insert( NameStyle::hyphenPascalMixedUnderscoredStyle);
    allNameStyles.insert( NameStyle::cppCamelMixedUnderscoredStyle  );
    allNameStyles.insert( NameStyle::cppPascalMixedUnderscoredStyle );
    allNameStyles.insert( NameStyle::defineUnderscoredStyle         );

    return allNameStyles;
}

inline NameStyleSet makeAllNameStyles( bool onlyValidStyles=false )
{
    return makeAllNameStylesSet();
}

//----------------------------------------------------------------------------


#if 0

// std::* functions fails on non-ascii chars (assertion failed)

inline bool    isAlpha( char ch )     { return std::isalpha( ch ) ? true : false; }
inline bool    isLower( char ch )     { return std::islower( ch ) ? true : false; }
inline bool    isUpper( char ch )     { return std::isupper( ch ) ? true : false; }
inline bool    isDigit( char ch )     { return std::isdigit( ch ) ? true : false; }
inline bool    getCase( char ch )     { return isUpper(ch); }
inline char    toLower( char ch )     { return (char)std::tolower(ch); }
inline char    toUpper( char ch )     { return (char)std::toupper(ch); }

inline bool    isAlpha( wchar_t ch )  { return std::iswalpha( ch ) ? true : false; }
inline bool    isLower( wchar_t ch )  { return std::iswlower( ch ) ? true : false; }
inline bool    isUpper( wchar_t ch )  { return std::iswupper( ch ) ? true : false; }
inline bool    isDigit( wchar_t ch )  { return std::iswdigit( ch ) ? true : false; }
inline bool    getCase( wchar_t ch )  { return isUpper(ch); }
inline wchar_t toLower( wchar_t ch )  { return (wchar_t)std::towlower(ch); }
inline wchar_t toUpper( wchar_t ch )  { return (wchar_t)std::towupper(ch); }
#endif


//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
inline bool    isAlpha( char ch )     { return isLower(ch) || isUpper(ch); }
inline bool    isDigit( char ch )     { return (ch>='0' && ch<='9'); }
inline bool    getCase( char ch )     { return isUpper(ch); }

inline bool    isAlpha( wchar_t ch )  { return isLower(ch) || isUpper(ch); }
inline bool    isDigit( wchar_t ch )  { return (ch>=L'0' && ch<=L'9'); }
inline bool    getCase( wchar_t ch )  { return isUpper(ch); }

//----------------------------------------------------------------------------
inline 
bool isValidIdentChar( char ch, bool allowNonAsciiIdents, const std::string &forceAllowedChars )
{
    if (forceAllowedChars.find(ch)!=forceAllowedChars.npos)
        return true; // Force allowed

    if ( (ch>=0 && ch<=' ') || ch==0x7F)
        return false; // space and control chars are invalid

    if (ch>0x7F || ch<0)
    {
        if (allowNonAsciiIdents)
            return true;
        else
            return false;
    }

    // 31 invalid char, 33 ctrl+space, 1 0x7f, and valid - 26 upper alphas, 26 lower alphas, 10 digits, 1 '_' : total 31+33+1+26+26+10+1=128
    static const char* invalidChars = "!\"#$%&\'()*+,-./:;<=>?@[\\]^`{|}~";

    if (std::strchr(invalidChars, ch)!=0)
        return false;

    return true; // Alphanum or '_' char
}

inline 
bool isValidIdentChar( wchar_t ch, bool allowNonAsciiIdents, const std::wstring &forceAllowedChars )
{
    if (forceAllowedChars.find(ch)!=forceAllowedChars.npos)
        return true; // Force allowed

    if ( (ch>=0 && ch<=L' ') || ch==0x7F)
        return false; // space and control chars are invalid

    if (ch>0x7F || ch<0)
    {
        if (allowNonAsciiIdents)
            return true;
        else
            return false;
    }

    // 31 invalid char, 33 ctrl+space, 1 0x7f, and valid - 26 upper alphas, 26 lower alphas, 10 digits, 1 '_' : total 31+33+1+26+26+10+1=128
    static const wchar_t* invalidChars = L"!\"#$%&\'()*+,-./:;<=>?@[\\]^`{|}~";

    if (std::wcschr(invalidChars, ch)!=0)
        return false;

    return true; // Alphanum or '_' char
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template <typename CharT> inline
NameCharClass getNameCharClass( CharT ch, NameCharClass digitCharClass = NameCharClass::digit ) // NameCharClass::lower
{
    if (ch==(CharT)'_')
        return NameCharClass::underscore;

    if (isDigit(ch))
        return digitCharClass;

    if (isLower(ch))
       return NameCharClass::lower;

    if (isUpper(ch))
       return NameCharClass::upper;

    return NameCharClass::unknown;
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline bool isUnderscoreString( const std::basic_string< CharT, Traits, Allocator > &str )
{
    for( auto it = str.begin(); it != str.end(); ++it )
    {
        if (*it!=(CharT)'_')
            return false;
    }

    return true;
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
toPascal( const std::basic_string< CharT, Traits, Allocator > &str )
{
    if (str.empty())
        return str;

    std::basic_string< CharT, Traits, Allocator > resStr = toLower(str);

    typename std::basic_string< CharT, Traits, Allocator >::iterator it = resStr.begin();
    for(; it!=resStr.end(); ++it)
    {
        auto charClass = getNameCharClass(*it);
        if (charClass==NameCharClass::lower || charClass==NameCharClass::upper)
            break;
    }

    if (it!=resStr.end())
        *it = toUpper(*it);

    return resStr;
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
makeExpandString( const std::basic_string< CharT, Traits, Allocator > &str, std::size_t expandToSize, CharT ch = (CharT)' ' )
{
    if (str.size() >= expandToSize)
        return std::basic_string< CharT, Traits, Allocator >();

    size_t expandStringSize = expandToSize - str.size();

    return std::basic_string< CharT, Traits, Allocator >( expandStringSize, ch );
}


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
expandAtFront( const std::basic_string< CharT, Traits, Allocator > &str, std::size_t expandToSize, CharT ch = (CharT)' ')
{
    return makeExpandString(str, expandToSize, ch) + str;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
expandAtBack( const std::basic_string< CharT, Traits, Allocator > &str, std::size_t expandToSize, CharT ch = (CharT)' ')
{
    return str + makeExpandString(str, expandToSize, ch);
}

inline std::string  expandAtFront( const char    * pStr, std::size_t expandToSize, char    ch =  ' ' ) { return expandAtFront( std::string(pStr ), expandToSize, ch ); }
inline std::wstring expandAtFront( const wchar_t * pStr, std::size_t expandToSize, wchar_t ch = L' ' ) { return expandAtFront( std::wstring(pStr), expandToSize, ch ); }

inline std::string  expandAtBack ( const char    * pStr, std::size_t expandToSize, char    ch =  ' ' ) { return expandAtBack ( std::string(pStr ), expandToSize, ch ); }
inline std::wstring expandAtBack ( const wchar_t * pStr, std::size_t expandToSize, wchar_t ch = L' ' ) { return expandAtBack ( std::wstring(pStr), expandToSize, ch ); }


template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
makeString( const char* pStr )
{
    std::basic_string< CharT, Traits, Allocator > resStr;
    for(; *pStr; ++pStr)
    {
        resStr.append( 1, (CharT)*pStr );
    }

    return resStr;
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
trimUnderscoresLeading( const std::basic_string< CharT, Traits, Allocator > &str )
{
    auto beginIt = str.begin();
    for(; beginIt!=str.end() && *beginIt==(CharT)'_'; ++beginIt ) {}

    auto endIt = str.end();

    return std::basic_string< CharT, Traits, Allocator >( beginIt, endIt );
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
trimUnderscoresTrailing( const std::basic_string< CharT, Traits, Allocator > &str )
{
    auto beginIt = str.begin();

    auto endIt = str.end();
    auto endItPrev = endIt;
    if (endItPrev!=str.begin())
       --endItPrev;
    
    for(; endIt!=beginIt && *endItPrev==(CharT)'_'; --endIt, --endItPrev ) { }

    return std::basic_string< CharT, Traits, Allocator >( beginIt, endIt );
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
trimUnderscores( const std::basic_string< CharT, Traits, Allocator > &str )
{
    return trimUnderscoresLeading( trimUnderscoresTrailing(str) );
}


inline std::string  trimUnderscoresLeading ( const char    * pStr ) { return trimUnderscoresLeading( std::string(pStr ) ); }
inline std::wstring trimUnderscoresLeading ( const wchar_t * pStr ) { return trimUnderscoresLeading( std::wstring(pStr) ); }
inline std::string  trimUnderscoresTrailing( const char    * pStr ) { return trimUnderscoresTrailing( std::string(pStr ) ); }
inline std::wstring trimUnderscoresTrailing( const wchar_t * pStr ) { return trimUnderscoresTrailing( std::wstring(pStr) ); }
inline std::string  trimUnderscores        ( const char    * pStr ) { return trimUnderscores( std::string(pStr ) ); }
inline std::wstring trimUnderscores        ( const wchar_t * pStr ) { return trimUnderscores( std::wstring(pStr) ); }



template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
NameStyle detectNameStyleImpl( const std::basic_string< CharT, Traits, Allocator > &str )
{
    bool isValid       = false;
    bool hasFirstUpper = false;
    bool hasLower      = false;
    bool hasUpper      = false;
    bool hasUnderscore = false;
    bool isFirstAlpha  = false;

    std::size_t charCount  = 0;
    std::size_t alphaCount = 0;

    const unsigned FlagHasLower      = 0x01;
    const unsigned FlagHasUpper      = 0x02;
    const unsigned FlagHasUnderscore = 0x04;
    const unsigned FlagFirstUpper    = 0x08;
    //const unsigned FlagFirstUpper    = 0x10;


    for( auto it = str.begin(); it != str.end(); ++it, ++charCount)
    {
        CharT ch = *it;

        if (isAlpha(ch))
        {
            if (!charCount)
            {
                isValid      = true;
                isFirstAlpha = true;
            }

            if (!alphaCount && isUpper(ch))
                hasFirstUpper = true;

            ++alphaCount;

            if (isLower(ch))
                hasLower = true;

            if (isUpper(ch))
                hasUpper = true;

        }

        if (ch==(CharT)'_')
        {
            if (!charCount)
                isValid = true;

            hasUnderscore = true;
        }
    }

    if (!isValid)
        return NameStyle::invalidName;


    unsigned flags = 0;

    if (hasUnderscore)
        flags |= FlagHasUnderscore;

    if (hasLower)
        flags |= FlagHasLower;

    if (hasUpper)
        flags |= FlagHasUpper;

    if (hasFirstUpper)
    {
        flags |= FlagHasUpper;
        flags |= FlagFirstUpper;
    }

    // if (hasFirstUpper)
    //     flags |= FlagFirstUpper;



    switch(flags)
    {
        case FlagHasLower                   :
        case FlagHasLower|FlagHasUnderscore :
             return NameStyle::cppStyle     ;

        case FlagHasUpper                   :
        case FlagHasUpper|FlagFirstUpper    :
        case FlagHasUpper|FlagHasUnderscore :
        case FlagHasUpper|FlagHasUnderscore|FlagFirstUpper :
             return NameStyle::defineStyle  ;

        case FlagHasLower|FlagHasUpper      :
             return NameStyle::camelStyle   ;

        case FlagHasLower|FlagHasUpper|FlagHasUnderscore :
             return NameStyle::cppCamelMixedStyle        ;

        case FlagFirstUpper|FlagHasLower|FlagHasUpper /* |FlagFirstUpper */     :
             return NameStyle::pascalStyle                              ;

        case FlagFirstUpper|FlagHasLower|FlagHasUpper|FlagHasUnderscore /* |FlagFirstUpper */  :
             return NameStyle::cppPascalMixedStyle                                     ;

        default: return NameStyle::unknownStyle;

    }
}

template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
NameStyle detectNameStyle( const std::basic_string< CharT, Traits, Allocator > &str )
{
    if (isUnderscoreString(str))
        return NameStyle::unknownStyle;

    std::basic_string< CharT, Traits, Allocator > ltUnderscoresRemoved = trimUnderscores(str);

    bool hasLeadingOrTrailingUnderscores = false;

    if (ltUnderscoresRemoved!=str)
    {
        hasLeadingOrTrailingUnderscores = true;
    }

    NameStyle baseStyle = detectNameStyleImpl(ltUnderscoresRemoved);

    if (!hasLeadingOrTrailingUnderscores)
        return baseStyle;

    switch(baseStyle)
    {
        case NameStyle::hyphenStyle           :  return NameStyle::hyphenUnderscoredStyle           ;
        case NameStyle::hyphenCamelMixedStyle :  return NameStyle::hyphenCamelMixedUnderscoredStyle ;
        case NameStyle::hyphenPascalMixedStyle:  return NameStyle::hyphenPascalMixedUnderscoredStyle;
        case NameStyle::cppStyle           :  return NameStyle::cppUnderscoredStyle           ;
        case NameStyle::camelStyle         :  return NameStyle::camelUnderscoredStyle         ;
        case NameStyle::pascalStyle        :  return NameStyle::pascalUnderscoredStyle        ;
        case NameStyle::cppCamelMixedStyle :  return NameStyle::cppCamelMixedUnderscoredStyle ;
        case NameStyle::cppPascalMixedStyle:  return NameStyle::cppPascalMixedUnderscoredStyle;
        case NameStyle::defineStyle        :  return NameStyle::defineUnderscoredStyle        ;
        default: return baseStyle;
    }

}
 
inline NameStyle detectNameStyle( const char    * pStr )   { return detectNameStyle( std::string(pStr ) ); }
inline NameStyle detectNameStyle( const wchar_t * pStr )   { return detectNameStyle( std::wstring(pStr) ); }



template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::vector< std::basic_string< CharT, Traits, Allocator > >
splitName( const std::basic_string< CharT, Traits, Allocator > &str )
{
    std::vector< std::basic_string< CharT, Traits, Allocator > > resVec;
    //std::basic_string< CharT, Traits, Allocator > postfixString;

    auto beginIt = str.begin();

    // Find undercsore prefix
    for(; beginIt!=str.end() && *beginIt==(CharT)'_'; ++beginIt ) {}

    if (beginIt!=str.begin())
    {
        resVec.push_back( std::basic_string< CharT, Traits, Allocator >( str.begin(), beginIt ) );
        // prefixString = std::basic_string< CharT, Traits, Allocator >( str.begin(), it );
    }

    // Find undercsore postfix
    auto endIt = str.end();
    auto endItPrev = endIt;
    if (endItPrev!=str.begin())
       --endItPrev;
    
    for(; endIt!=beginIt && *endItPrev==(CharT)'_'; --endIt, --endItPrev ) { }

    auto postfixBegin = str.end();
    auto postfixEnd   = str.end();

    if (endIt!=str.end())
    {
        // resVec.push_back( std::basic_string< CharT, Traits, Allocator >( endIt, str.end() ) );
        //postfixString = std::basic_string< CharT, Traits, Allocator >( postfixBegin, postfixEnd );
        postfixBegin = endIt;
    }


    NameCharClass prevCharClass = NameCharClass::unknown;
    if (beginIt!=endIt)
    {
        prevCharClass = getNameCharClass( *beginIt, NameCharClass::lower );
    }


    auto startIt = beginIt;
    auto it      = beginIt;

    for( ; it!=endIt; ++it)
    {
        auto curCharClass = getNameCharClass( *it, NameCharClass::lower );
        if (prevCharClass!=curCharClass && !(prevCharClass==NameCharClass::upper && curCharClass==NameCharClass::lower) )
        {
            auto curPartStr = std::basic_string< CharT, Traits, Allocator >(startIt, it);
            startIt = it;
            if (!isUnderscoreString(curPartStr))
            {
                resVec.push_back(curPartStr);
            }
        }

        prevCharClass = curCharClass;
    }

    if (startIt != it)
    {
        auto curPartStr = std::basic_string< CharT, Traits, Allocator >(startIt, it);
        if (!isUnderscoreString(curPartStr))
        {
            resVec.push_back(curPartStr);
        }
    }

    if (postfixBegin!=postfixEnd)
        resVec.push_back(std::basic_string< CharT, Traits, Allocator >( postfixBegin, postfixEnd ));


//  NameCharClass getNameCharClass( CharT ch, NameCharClass digitCharClass = NameCharClass::digit ) // NameCharClass::lower



    /*
    resVec.push_back( makeString<CharT, Traits, Allocator>( "__" ) );
    resVec.push_back( makeString<CharT, Traits, Allocator>( "Youuu" ) );
    resVec.push_back( makeString<CharT, Traits, Allocator>( "Man" ) );
    resVec.push_back( makeString<CharT, Traits, Allocator>( "__" ) );
    */

    return resVec;
}

inline std::vector< std::string  > splitName( const char    * pStr ) { return splitName( std::string(pStr ) ); }
inline std::vector< std::wstring > splitName( const wchar_t * pStr ) { return splitName( std::wstring(pStr) ); }

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
filterName( const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents, const std::basic_string< CharT, Traits, Allocator > &forceAllowedChars )
{
    typedef std::basic_string< CharT, Traits, Allocator >   string_type;

    string_type res; res.reserve(str.size());

    typename string_type::const_iterator it = str.begin();

    for(; it!=str.end(); ++it)
    {
        if (isValidIdentChar( *it, allowNonAsciiIdents, forceAllowedChars ))
            res.append(1, *it);
        else
            res.append(1, '_');
    }

    return res;

}

//------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
filterName( const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents = false)
{
    return filterName(str, allowNonAsciiIdents, std::basic_string< CharT, Traits, Allocator >() );
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template< class OutputIterator, class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline void
splitNamesNotNames( OutputIterator outIter, const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents, const std::basic_string< CharT, Traits, Allocator > &forceAllowedChars )
{
    typedef std::basic_string< CharT, Traits, Allocator >   string_type;

    string_type buf; buf.reserve(str.size());

    typename string_type::const_iterator it = str.begin();

    bool prevIsValidChar = false;

    for(; it!=str.end(); ++it)
    {
        bool curIsValidChar = isValidIdentChar( *it, allowNonAsciiIdents, forceAllowedChars );
        if (prevIsValidChar!=curIsValidChar)
        {
            prevIsValidChar = curIsValidChar;
            if (!buf.empty())
            {
                *outIter++ = buf;
                buf.clear();
            }
        }

        buf.append(1, *it);
    }

    *outIter++ = buf;
}

//------------------------------
template< class OutputIterator, class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline void
splitNamesNotNames( OutputIterator outIter, const std::basic_string< CharT, Traits, Allocator > &str, bool allowNonAsciiIdents = false)
{
    splitNamesNotNames(outIter, str, allowNonAsciiIdents, std::basic_string< CharT, Traits, Allocator >() );
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
fixName( const std::basic_string< CharT, Traits, Allocator > &str, bool fixStartDigit, const std::basic_string< CharT, Traits, Allocator > &forceAllowedChars )
{
    typedef std::basic_string< CharT, Traits, Allocator >   string_type;

    string_type res; res.reserve(str.size());

    auto appendFix = [&]( auto str )
    {
        if (!res.empty() && res.back()!=(CharT)'_')
            res.append(1,(CharT)'_');
        res.append(make_string<string_type>(str));
        res.append(1,(CharT)'_');
    };

    typename string_type::const_iterator it = str.begin();

    for(; it!=str.end(); ++it)
    {
        if (forceAllowedChars.find(*it)!=forceAllowedChars.npos) // forceAllowedChars.end())
        {
            res.append(1, *it);
        }
        else
        {
            switch(*it)
            {
                //L"()[]{}";
                case (CharT)'!': appendFix("exmark"); break;
                case (CharT)'@': appendFix("at"); break;
                case (CharT)'#': appendFix("hash"); break;
                case (CharT)'$': appendFix("usd"); break;
                case (CharT)'%': appendFix("percent"); break;
                case (CharT)'&': appendFix("amp"); break;
                case (CharT)'/': appendFix("slash"); break;
                case (CharT)'\\': appendFix("backslash"); break;
                case (CharT)'*': appendFix("mul"); break;
                case (CharT)'+': appendFix("plus"); break;
                //case (CharT)'-': appendFix("minus"); break;
                case (CharT)'-': appendFix("_"); break;
                case (CharT)'\'': appendFix("apos"); break;
                case (CharT)'\"': appendFix("quot"); break;
                case (CharT)',': appendFix("comma"); break;
                case (CharT)'.': appendFix("period"); break;
                case (CharT)':': appendFix("colon"); break;
                case (CharT)';': appendFix("semicolon"); break;
                case (CharT)'<': appendFix("less"); break;
                case (CharT)'=': appendFix("equal"); break;
                case (CharT)'>': appendFix("greater"); break;
                case (CharT)'?': appendFix("qmark"); break;
                case (CharT)'|': appendFix("bvb"); break;
                case (CharT)'^': appendFix("xormark"); break;
                case (CharT)'`': appendFix("acute"); break;
                case (CharT)'~': appendFix("tilde"); break;
                //case (CharT)'': appendFix(""); break;
                default: res.append(1, *it);
            }
        }
    }

    if (fixStartDigit)
    {
        if (!res.empty() && isDigit(res[0]))
        {
            res.insert(0, 1, (CharT)'_');
        }
    }

    return res;

}

//------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
fixName( const std::basic_string< CharT, Traits, Allocator > &str, bool fixStartDigit = true )
{
    return fixName(str, fixStartDigit, std::basic_string< CharT, Traits, Allocator >() );
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
template< class CharT, class Traits = std::char_traits<CharT>, class Allocator = std::allocator<CharT> >
inline std::basic_string< CharT, Traits, Allocator >
formatName( const std::basic_string< CharT, Traits, Allocator > &str, NameStyle nameStyle, bool fixStartDigit = true )
{
    typedef std::basic_string< CharT, Traits, Allocator >  StringType;
    std::vector< StringType > nameParts = splitName(str);

    if (nameParts.empty())
        return StringType();

    auto beginIt  = nameParts.begin();
    auto endIt    = nameParts.end();

    auto prefixIt = nameParts.end();
    if (isUnderscoreString(*beginIt))
    {
        prefixIt = beginIt;
        ++beginIt;
    }

    auto postfixIt = nameParts.end();
    if (nameParts.size()>1)
    {
        auto tmpIt = postfixIt;
        --tmpIt;
        if (isUnderscoreString(*tmpIt))
        {
            postfixIt = tmpIt;
            endIt     = postfixIt;
        }
    }


    std::basic_string< CharT, Traits, Allocator > strRes;
    bool isFirst = true;
    // make result here

    for(auto it = beginIt; it!=endIt; isFirst = false, ++it )
    {
        if (!strRes.empty())
        {
            if ( nameStyle==NameStyle::cppStyle
              || nameStyle==NameStyle::cppUnderscoredStyle
              || nameStyle==NameStyle::cppCamelMixedStyle
              || nameStyle==NameStyle::cppCamelMixedUnderscoredStyle
              || nameStyle==NameStyle::cppPascalMixedStyle
              || nameStyle==NameStyle::cppPascalMixedUnderscoredStyle
              || nameStyle==NameStyle::defineStyle
              || nameStyle==NameStyle::defineUnderscoredStyle
               )
            {
                strRes.append(1, (CharT)'_');
            }
            else if ( nameStyle==NameStyle::hyphenStyle 
              || nameStyle==NameStyle::hyphenUnderscoredStyle
              || nameStyle==NameStyle::hyphenCamelMixedStyle
              || nameStyle==NameStyle::hyphenCamelMixedUnderscoredStyle
              || nameStyle==NameStyle::hyphenPascalMixedStyle
              || nameStyle==NameStyle::hyphenPascalMixedUnderscoredStyle
              )
            {
                strRes.append(1, (CharT)'-');
            }

        }

        switch(nameStyle)
        {
            case NameStyle::hyphenStyle           :
            case NameStyle::hyphenUnderscoredStyle:
            case NameStyle::cppStyle              :
            case NameStyle::cppUnderscoredStyle   :
                 strRes.append(toLower(*it));
                 break;

            case NameStyle::hyphenCamelMixedStyle:
            case NameStyle::cppCamelMixedStyle   :
            case NameStyle::camelStyle           :
            case NameStyle::hyphenCamelMixedUnderscoredStyle:
            case NameStyle::cppCamelMixedUnderscoredStyle:
            case NameStyle::camelUnderscoredStyle:
                 if (isFirst)
                     strRes.append(toLower(*it));
                 else
                     strRes.append(toPascal(*it));
                 break;

            case NameStyle::hyphenPascalMixedStyle :
            case NameStyle::cppPascalMixedStyle :
            case NameStyle::pascalStyle         :
            case NameStyle::hyphenPascalMixedUnderscoredStyle:
            case NameStyle::cppPascalMixedUnderscoredStyle:
            case NameStyle::pascalUnderscoredStyle        :
                 strRes.append(toPascal(*it));
                 break;

            case NameStyle::defineStyle           :
            case NameStyle::defineUnderscoredStyle:
                 strRes.append(toUpper(*it));
                 break;

            default                             :
                 strRes.append(*it);

        
        }
    }


    switch(nameStyle)
    {
        //case NameStyle::unknownStyle       :
        //case NameStyle::invalidName        :
        case NameStyle::cppStyle           :
        case NameStyle::camelStyle         :
        case NameStyle::pascalStyle        :
        case NameStyle::cppCamelMixedStyle :
        case NameStyle::cppPascalMixedStyle:
        case NameStyle::defineStyle        :
             return fixName(strRes,fixStartDigit); // Don't add underscore prefix/suffix
        case NameStyle::hyphenStyle           :
        case NameStyle::hyphenUnderscoredStyle:
        case NameStyle::hyphenCamelMixedStyle :
        case NameStyle::hyphenPascalMixedStyle:
             return fixName(strRes, fixStartDigit, make_string<StringType>("-")); // Don't add underscore prefix/suffix
    }

    // add prefix
    if (prefixIt!=nameParts.end())
    {
        strRes = *prefixIt + strRes;
    }

    // add postfix
    if (postfixIt!=nameParts.end())
    {
        strRes = strRes + *postfixIt;
    }

    if ( nameStyle==NameStyle::hyphenStyle
      || nameStyle==NameStyle::hyphenUnderscoredStyle
      || nameStyle==NameStyle::hyphenCamelMixedStyle
      || nameStyle==NameStyle::hyphenCamelMixedUnderscoredStyle
      || nameStyle==NameStyle::hyphenPascalMixedStyle
      || nameStyle==NameStyle::hyphenPascalMixedUnderscoredStyle
      )
        return fixName(strRes, fixStartDigit, make_string<StringType>("-"));

    return fixName(strRes,fixStartDigit);
}

inline std::string  formatName( const char    * pStr, NameStyle nameStyle, bool fixStartDigit = true ) { return formatName( std::string(pStr ), nameStyle, fixStartDigit ); }
inline std::wstring formatName( const wchar_t * pStr, NameStyle nameStyle, bool fixStartDigit = true ) { return formatName( std::wstring(pStr), nameStyle, fixStartDigit ); }
                                   
//----------------------------------------------------------------------------






//----------------------------------------------------------------------------
#if 0
template<typename StringType, typename Iter, typename ToStringObj>
inline
StringType merge( Iter b, Iter e, const std::string &delim, const ToStringObj &stringifier )
{
    StringType _delim = make_string<StringType>(delim);
    StringType res;
    for( ; b!=e; ++b )
    {
        if (!res.empty()) res.append(_delim);
        res.append(stringifier(*b));
    }
    return res;
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter, typename ToStringObj>
inline
StringType merge( Iter b , Iter e, const std::wstring &delim, const ToStringObj &stringifier )
{
    StringType _delim = make_string<StringType>(delim);
    StringType res;
    for( ; b!=e; ++b )
    {
        if (!res.empty()) res.append(_delim);
        res.append(stringifier(*b));
    }
    return res;
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter, typename ToStringObj> inline
StringType merge( Iter b, Iter e, char delim, const ToStringObj &stringifier )
{
    return merge<StringType>( b, e, make_string<StringType>(delim,1), stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter, typename ToStringObj> inline
StringType merge( Iter b, Iter e, const char *delim, const ToStringObj &stringifier )
{
    return merge<StringType>( b, e, make_string<StringType>(delim), stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter, typename ToStringObj> inline
StringType merge( Iter b, Iter e, wchar_t delim, const ToStringObj &stringifier )
{
    return merge<StringType>( b, e, make_string<StringType>(delim,1), stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter, typename ToStringObj> inline
StringType merge( Iter b, Iter e, const wchar_t *delim, const ToStringObj &stringifier )
{
    return merge<StringType>( b, e, make_string<StringType>(delim), stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename ItemType, typename ToStringObj> inline
std::string merge( const std::vector<ItemType> &tokens, char delim, const ToStringObj &stringifier )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename ItemType, typename ToStringObj> inline
std::string merge( const std::vector<ItemType> &tokens, const char *delim, const ToStringObj &stringifier )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename ItemType, typename ToStringObj> inline
std::string merge( const std::vector<ItemType> &tokens, const std::string &delim, const ToStringObj &stringifier )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename ItemType, typename ToStringObj> inline
std::string merge( const std::vector<ItemType> &tokens, wchar_t delim, const ToStringObj &stringifier )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename ItemType, typename ToStringObj> inline
std::string merge( const std::vector<ItemType> &tokens, const wchar_t *delim, const ToStringObj &stringifier )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, stringifier );
}

//----------------------------------------------------------------------------
template<typename StringType, typename ItemType, typename ToStringObj> inline
std::string merge( const std::vector<ItemType> &tokens, const std::wstring &delim, const ToStringObj &stringifier )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, stringifier );
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
//! Просто возвращает свой аргумент. Типа вместо лямбды
template <typename T>
struct lambda_return_arg
{
    //! Возвращает свой аргумент
    T operator()( const T &t ) const {  return t; }
};

//------------------------------
//! Возвращает true, если объект empty(). Типа вместо лямбды
template <typename T>
struct lambda_is_empty
{
    //! Возвращает результат вызова empty() для своего аргумента
    bool operator()( const T &t ) const  { return t.empty(); }
};

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template<typename StringType, typename Iter> inline
StringType merge( Iter b, Iter e, char delim )
{
    return merge<StringType>( b, e, delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter> inline
StringType merge( Iter b, Iter e, const char *delim )
{
    return merge<StringType>( b, e, delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter> inline
StringType merge( Iter b, Iter e, const std::string &delim )
{
    return merge<StringType>( b, e, delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter> inline
StringType merge( Iter b, Iter e, wchar_t delim )
{
    return merge<StringType>( b, e, delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter> inline
StringType merge( Iter b, Iter e, const wchar_t *delim )
{
    return merge<StringType>( b, e, delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType, typename Iter> inline
StringType merge( Iter b, Iter e, const std::wstring &delim )
{
    return merge<StringType>( b, e, delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType> inline
StringType merge( const std::vector<StringType> &tokens, char delim )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType> inline
StringType merge( const std::vector<std::string> &tokens, const char *delim )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType> inline
StringType merge( const std::vector<std::string> &tokens, const std::string &delim )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType> inline
StringType merge( const std::vector<StringType> &tokens, wchar_t delim )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType> inline
StringType merge( const std::vector<std::string> &tokens, const wchar_t *delim )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, lambda_return_arg<StringType>() );
}

//----------------------------------------------------------------------------
template<typename StringType> inline
StringType merge( const std::vector<std::string> &tokens, const std::wstring &delim )
{
    return merge<StringType>( tokens.begin(), tokens.end(), delim, lambda_return_arg<StringType>() );
}

//-----------------------------------------------------------------------------
#endif


//-----------------------------------------------------------------------------
//! Расширение строки до нужной длины
template<typename StringType> inline
void expand( StringType &str                                                            //!< Расширяемая строка
           , typename StringType::size_type sz                                          //!< Требуемый размер
           , typename StringType::value_type ch = (typename StringType::value_type)' '  //!< Символ заполнения
           )
{
    if (str.size()>=sz)
        return;

    typename StringType::size_type numCharsToAdd = sz - str.size();
    str.append( numCharsToAdd, ch );
}

//------------------------------
//! Расширение копии строки до нужной длины. \returns Расширеную строку.
template<typename StringType> inline
StringType expand_copy( const StringType &str                                                      //!< Расширяемая строка
                      , typename StringType::size_type sz                                          //!< Требуемый размер
                      , typename StringType::value_type ch = (typename StringType::value_type)' '  //!< Символ заполнения
                      )
{
    std::string res = str;
    expand(res, sz, ch);
    return res;
}

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
#ifndef MARTY_CPP_SIMPLE_STRING_SPLIT_DECLARED
#define MARTY_CPP_SIMPLE_STRING_SPLIT_DECLARED
//-----------------------------------------------------------------------------
template<typename StringType> inline
std::vector<StringType> simple_string_split(const StringType &str, const StringType &delim, typename StringType::size_type nSplits = -1)
{
    // std::string s = "scott>=tiger>=mushroom";
    // std::string delimiter = ">=";

    // txt = "apple#banana#cherry#orange"
    // # setting the maxsplit parameter to 1, will return a list with 2 elements!
    // x = txt.split("#", 1)

    std::vector<StringType> res;

    typename StringType::size_type curPos  = 0;
    typename StringType::size_type prevPos = 0;
    //StringType token;
    while (res.size()!=nSplits && (curPos = str.find(delim, prevPos)) != StringType::npos)
    {
        res.emplace_back(str, prevPos, curPos-prevPos);
        prevPos = curPos+delim.size();
    }

    res.emplace_back(str, prevPos);

    return res;
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
std::vector<StringType> simple_string_split(const StringType &str, const typename StringType::value_type *delim, typename StringType::size_type nSplits = -1)
{
    return simple_string_split( str, StringType(delim), nSplits);
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
std::vector<StringType> simple_string_split(const StringType &str, const typename StringType::value_type delim, typename StringType::size_type nSplits = -1)
{
    typename StringType::value_type tmpDelimStr[2] = { delim, 0 };
    return simple_string_split( str, tmpDelimStr, nSplits);
}

//-----------------------------------------------------------------------------
#endif // MARTY_CPP_SIMPLE_STRING_SPLIT_DECLARED
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
#ifndef MARTY_CPP_SIMPLE_STRING_REPLACE_DECLARED
#define MARTY_CPP_SIMPLE_STRING_REPLACE_DECLARED
//-----------------------------------------------------------------------------
template<typename StringType> inline
StringType simple_string_replace(const StringType &str, const StringType &searchFor, const StringType &replaceWith, typename StringType::size_type nSplits = -1)
{
    typename StringType::size_type replaceCounter = 0;

    typename StringType::size_type curPos  = 0;
    typename StringType::size_type prevPos = 0;

    StringType res; res.reserve(str.size());

    for(; replaceCounter!=nSplits && (curPos = str.find(searchFor, prevPos)) != StringType::npos; ++replaceCounter)
    {
        res.append(str, prevPos, curPos-prevPos);
        prevPos = curPos+searchFor.size();
        res.append(replaceWith);
    }

    res.append(str, prevPos);

    return res;
}

//-----------------------------------------------------------------------------
#endif // MARTY_CPP_SIMPLE_STRING_REPLACE_DECLARED
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
#ifndef MARTY_CPP_SIMPLE_SEQ_FILTER_DECLARED
#define MARTY_CPP_SIMPLE_SEQ_FILTER_DECLARED
//-----------------------------------------------------------------------------
template<typename InputIterType, typename OutputIterType, typename FilterAllowPred> inline
void simple_seq_filter(InputIterType b, InputIterType e, OutputIterType o, const FilterAllowPred &allowPred)
{
    for(; b!=e; ++b)
    {
        if (allowPred(*b))
            *o++ = *b;
    }
}

//-----------------------------------------------------------------------------
template<typename ItemType, typename FilterAllowPred> inline
std::vector<ItemType> simple_seq_filter( const std::vector<ItemType> &v, const FilterAllowPred &allowPred )
{
    std::vector<ItemType> res;
    simple_seq_filter(v.cbegin(), v.cend(), std::back_inserter(res), allowPred);
    return res;
}
//-----------------------------------------------------------------------------
#endif // MARTY_CPP_SIMPLE_SEQ_FILTER_DECLARED
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
#ifndef MARTY_CPP_SIMPLE_TRIM_DECLARED
#define MARTY_CPP_SIMPLE_TRIM_DECLARED
//-----------------------------------------------------------------------------
template<typename IterType, typename ConditionType> inline
IterType trim_iter_impl( IterType b, IterType e, const ConditionType &trimCondition )
{
    for(; b!=e && trimCondition(*b); ++b) {}
    return b;
}

//-----------------------------------------------------------------------------
template<typename StringType, typename ConditionType> inline
StringType simple_trim(const StringType &str, const ConditionType &trimCondition)
{
    // if (str.empty())
    //     return str;
    auto e = trim_iter_impl(str.crbegin(), str.crend(), trimCondition).base();
    auto b = trim_iter_impl(str.cbegin(), e, trimCondition);
    return StringType(b,e);
}

//-----------------------------------------------------------------------------
#endif // MARTY_CPP_SIMPLE_TRIM_DECLARED
//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
template<typename CharType>
inline CharType get_char_pair( CharType brCh )
{
    switch(brCh)
    {
        case (CharType)'<' : return (CharType)'>' ;
        case (CharType)'>' : return (CharType)'<' ;

        case (CharType)'[' : return (CharType)']' ;
        case (CharType)']' : return (CharType)'[' ;

        case (CharType)'{' : return (CharType)'}' ;
        case (CharType)'}' : return (CharType)'{' ;

        case (CharType)'(' : return (CharType)')' ;
        case (CharType)')' : return (CharType)'(' ;

        case (CharType)'\'': return (CharType)'\'';
        case (CharType)'\"': return (CharType)'\"';

        case (CharType)'%': return (CharType)'%';
        case (CharType)'$': return (CharType)'$';

        case (CharType)'@': return (CharType)'@';
        case (CharType)'#': return (CharType)'#';

        case (CharType)'_': return (CharType)'_';

        default  : return 0;
    };
}

//-----------------------------------------------------------------------------
template<typename CharType> inline bool has_pair( CharType brCh )
{
    CharType pr = get_char_pair(brCh);
    return pr != 0;
}

//-----------------------------------------------------------------------------
template<typename CharType> inline bool is_openclose_char( CharType brCh )
{
    CharType pr = get_char_pair(brCh);
    return pr!=0 && pr!=brCh;
}

//-----------------------------------------------------------------------------
template<typename CharType> inline bool is_open_brace_char( CharType brCh )
{
    CharType pr = get_char_pair(brCh);

    if (pr==0)
        return false;

    if (pr==brCh) // такая же, а не парная
        return false;

    return brCh < pr; // Символ переданный аргументом - левее найденного в ASCII - значит открывающая
}

//-----------------------------------------------------------------------------
template<typename CharType> CharType get_pair_left_char(CharType ch)
{
    CharType pr = get_char_pair(ch);

    if (pr==0) // нет предусмотренной пары вообще никакой
        return ch;

    if (pr==ch) // такая же, а не парная
        return ch;

    return pr<ch ? pr : ch;
}

//-----------------------------------------------------------------------------
template<typename CharType> CharType get_pair_right_char(CharType ch)
{
    CharType pr = get_char_pair(ch);

    if (pr==0) // нет предусмотренной пары вообще никакой
        return ch;

    if (pr==ch) // такая же, а не парная
        return ch;

    return pr>ch ? pr : ch;
}

//-----------------------------------------------------------------------------
//! Возвращает раскавыченную строку
/*! 
    Строка заключена в одинаковые символы кавычек, внутри они дублируются
    Используется в bat-файлах, и тп
 */
template<typename StringType> inline
bool unquoteSimpleQuoted( StringType &str //!< Строка для раскавычивания
                        )
{
    if (str.size()<2)
        return str;

    const typename StringType::value_type quotChar = str.front();

    if (str.front()!=quotChar || str.back()!=quotChar)
        return str;

    std::string::size_type pos = 1, endPos = str.size()-1;

    std::string res; res.reserve(endPos-pos);

    bool prevQuot = false;

    for( ; pos!=endPos; ++pos )
    {
        auto ch = str[pos];

        if (prevQuot)
        {
            if (ch==quotChar)
            {
                res.append(1,quotChar); // remove diplicated quots
            }
            else
            {
                res.append(1,quotChar);
                res.append(1,ch); // не знаю, что это, просто игнорим
            }
            prevQuot = false;
        }
        else
        {
            res.append(1,ch);
        }
    }

    if (prevQuot)
    {
        res.append(1,quotChar);
    }

    return res;

}

//-----------------------------------------------------------------------------
//! Возвращает true, если строка закавычена. 
/*! 
    Если quotEnd не равен нулю, то кавычки используются как задано, иначе - автоопределение.
 */
template<typename StringType> inline
bool is_quoted( const StringType &s                        //!< Строка для проверки
              , typename StringType::value_type quotStart    //!< Открывающая кавычка
              , typename StringType::value_type quotEnd = 0  //!< Закрывающая кавычка, если 0 - то срабатывает автоопределение обоих кавычек (используются парные символы по открывающией кавычке)
              )
{
    if (s.size()<2)
        return false;

    if (quotEnd==0)
    {
        quotEnd   = get_pair_right_char(quotStart);
        quotStart = get_pair_left_char (quotStart);
    }

    if (s[0]==quotStart && s[s.size()-1]==quotEnd)
        return true;

    return false;
}

//-----------------------------------------------------------------------------
//! Возвращает true, если строка была закавычена, и раскавычивает её. 
/*! 
    Если quotEnd не равен нулю, то кавычки используются как задано, иначе - автоопределение.
 */
template<typename StringType> inline
bool unquote( StringType &s                               //!< Строка для раскавычивания
            , typename StringType::value_type quotStart   //!< Открывающая кавычка
            , typename StringType::value_type quotEnd = 0 //!< Закрывающая кавычка, если 0 - то срабатывает автоопределение обоих кавычек (используются парные символы по открывающией кавычке)
            )
{
    if (!is_quoted(s, quotStart, quotEnd))
        return false;
    
    s.erase( s.size()-1 );
    s.erase( 0, 1 );
    trim(s);
    return true;
    
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
StringType unquoted( StringType &s                        //!< Строка для раскавычивания
            , typename StringType::value_type quotStart   //!< Открывающая кавычка
            , typename StringType::value_type quotEnd = 0 //!< Закрывающая кавычка, если 0 - то срабатывает автоопределение обоих кавычек (используются парные символы по открывающией кавычке)
            )
{
    unquote(s,quotStart,quotEnd);
    return s;
}

//-----------------------------------------------------------------------------
//! Возвращает true, если строка была закавычена, и раскавычивает её. 
/*! 
    Используются первые символы параметров strStart и strEnd. Если quotEnd не равен нулю, то кавычки используются как задано, иначе - автоопределение.
 */
template<typename StringType> inline
bool unquote( StringType &s                           //!< Строка для раскавычивания
            , const StringType &strStart              //!< Открывающая кавычка
            , const StringType &strEnd = StringType() //!< Закрывающая кавычка, если пустая строка - то срабатывает автоопределение обоих кавычек (используются парные символы по открывающией кавычке)
            )
{
    if (strStart.empty())
        return false;

    if (strEnd.empty())
       return unquote( s, strStart[0], 0 );

    return unquote( s, strStart[0], strEnd[0] );
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
StringType unquoted( StringType &s                    //!< Строка для раскавычивания
            , const StringType &strStart              //!< Открывающая кавычка
            , const StringType &strEnd = StringType() //!< Закрывающая кавычка, если пустая строка - то срабатывает автоопределение обоих кавычек (используются парные символы по открывающией кавычке)
            )
{
    unquote(s,strStart,strEnd);
    return s;
}
//-----------------------------------------------------------------------------






//----------------------------------------------------------------------------
#ifndef MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL
    #define MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL( streamTypeName, fmtStr, fmtTypeName ) \
            streamTypeName & operator<<( fmtTypeName v)       \
            {                                                 \
                char buf[128];                                \
                std::sprintf(buf, fmtStr, v);                 \
                m_str.append(make_string<string_type>(buf));  \
                return *this;                                 \
            }
#endif

#ifndef MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTERS_BASIC_INTEGRAL_TYPES_IMPL
    #define MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTERS_BASIC_INTEGRAL_TYPES_IMPL( streamTypeName )           \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%d"  , int)                  \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%ld" , long)                 \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%lld", long long)            \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%u"  , unsigned)             \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%lu" , unsigned long)        \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%llu", unsigned long long)   \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%f"  , float)                \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%f"  , double)               \
            MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTER_IMPL(streamTypeName, "%Lf" , long double)
#endif

//----------------------------------------------------------------------------
#ifndef MARTY_CPP_SIMPLE_STRING_STREAM__DEFINED
#define MARTY_CPP_SIMPLE_STRING_STREAM__DEFINED
template<typename StringType>
class SimpleStringRefStream
{
    StringType          &m_str;

public:

    typedef StringType  string_type;

    typedef typename string_type::value_type         char_type        ;
    typedef typename string_type::value_type         value_type       ;
    typedef typename string_type::traits_type        traits_type      ;
    typedef typename string_type::allocator_type     allocator_type   ;
    typedef typename string_type::size_type          size_type        ;
    typedef typename string_type::difference_type    difference_type  ;
    //typedef typename string_type::


    SimpleStringRefStream( string_type &str ) : m_str(str) {}
    SimpleStringRefStream() = delete;
    SimpleStringRefStream(const SimpleStringRefStream&) = delete;
    SimpleStringRefStream(SimpleStringRefStream&&) = delete;
    SimpleStringRefStream& operator=(const SimpleStringRefStream&) = delete;

    const string_type& str() const { return m_str; }

    SimpleStringRefStream& operator<<( const char_type *str )
    {
        m_str.append(str);
        return *this;
    }

    SimpleStringRefStream& operator<<( char_type ch )
    {
        m_str.append(1, ch);
        return *this;
    }

    SimpleStringRefStream& operator<<( const string_type &str )
    {
        m_str.append(str);
        return *this;
    }

    SimpleStringRefStream& operator<<( bool b )
    {
        m_str.append(make_string<string_type>(b ? "true" : "false"));
        return *this;
    }

    MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTERS_BASIC_INTEGRAL_TYPES_IMPL(SimpleStringRefStream)


}; // template<StringType> class SimpleStringRefStream

//----------------------------------------------------------------------------
template<typename StringType>
class SimpleStringStream
{
    StringType          m_str;

public:

    typedef StringType  string_type;

    typedef typename string_type::value_type         char_type        ;
    typedef typename string_type::value_type         value_type       ;
    typedef typename string_type::traits_type        traits_type      ;
    typedef typename string_type::allocator_type     allocator_type   ;
    typedef typename string_type::size_type          size_type        ;
    typedef typename string_type::difference_type    difference_type  ;
    //typedef typename string_type::


    SimpleStringStream() = default;
    SimpleStringStream(const SimpleStringStream&) = delete;
    SimpleStringStream(SimpleStringStream&&) = delete;
    SimpleStringStream& operator=(const SimpleStringStream&) = delete;

    const string_type& str() const { return m_str; }

    SimpleStringStream& operator<<( const char_type *str )
    {
        m_str.append(str);
        return *this;
    }

    SimpleStringStream& operator<<( char_type ch )
    {
        m_str.append(1, ch);
        return *this;
    }

    SimpleStringStream& operator<<( const string_type &str )
    {
        m_str.append(str);
        return *this;
    }

    SimpleStringStream& operator<<( bool b )
    {
        m_str.append(make_string<string_type>(b ? "true" : "false"));
        return *this;
    }

    MARTY_CPP_MARTY_CPP_SIMPLE_STRING_STREAM_INSERTERS_BASIC_INTEGRAL_TYPES_IMPL(SimpleStringStream)


}; // template<StringType> class SimpleStringStream

#endif // MARTY_CPP_SIMPLE_STRING_STREAM__DEFINED

//-----------------------------------------------------------------------------





//-----------------------------------------------------------------------------
/*
    enum генератор

    Надо генерить имена begin, end, invalid - если их нет - это должно быть опционально.
    Версия, принимающая вектор пар - ничего такого не должна делать, это только для
    более упрощенной версии, которая парсит строку с определением enum'а.

    А оно вообще надо? Я begin/end использовал, когда делал сериализацию enum'ов
    средствами плюсов и макросов, для перечисления всех значений, а тут вроде не нужно.
    Пока отложим.

    Что для знаковых, что для беззнаковых - значение -1 всегда будем писать как знаковое


 */
//-----------------------------------------------------------------------------
struct EnumGeneratorOptionFlags
{
    static const unsigned enumClass                    = 0x00000001;
    static const unsigned unsignedVals                 = 0x00000002;
    static const unsigned useUnorderedMap              = 0x00000004;
    static const unsigned singleDef                    = 0x00000008;
    static const unsigned noExtraLinefeed              = 0x00000010;
    static const unsigned lowercaseDeserelialize       = 0x00000020;
    static const unsigned integerDeserelialize         = 0x00000040;

    static const unsigned enumFlags                    = 0x00000080;

    static const unsigned generateDefSerialize         = 0x00010000;
    static const unsigned generateDefDeserialize       = 0x00020000;
    static const unsigned generateDefType              = 0x00040000;
    static const unsigned generateDefSerializeSet      = 0x00100000;
    static const unsigned generateDefDeserializeSet    = 0x00200000;

    // complex flags
    static const unsigned generateDefSerializeBoth     = 0x00030000; // generateDefSerialize | generateDefDeserialize
    static const unsigned generateDefSerializeBothDir  = 0x00030000; // generateDefSerialize | generateDefDeserialize
    static const unsigned generateDefAll               = 0x00070000; // generateDefSerialize | generateDefDeserialize | generateDefType
    static const unsigned generateDefSerializeExtra    = 0x00300000;

    //unsigned unsignedVals = 0x02;

};

//-----------------------------------------------------------------------------
template<typename StringType>
struct EnumGeneratorTemplate
{
    StringType declBeginTemplate           ; // $(INDENT)enum $(CLASS) $(NAME)
    StringType declBeginUnderlyingTemplate ; // $(INDENT)enum $(CLASS) $(NAME) : $(UNDERLAYED)

    StringType declClass                   ; // class

    StringType castTemplate                ;

    StringType scopeBeginTemplate          ; // $(INDENT){
    StringType scopeEndTemplate            ; // $(INDENT)}; // $(DECLBEGIN)

    StringType declItemSepBeforeFirst      ; // \n
    StringType declItemSepBefore           ; // ,\n
    StringType declItemSepAfter            ;

    StringType declItemTemplate            ; // $(ITEMINDENT)$(NAME) = $(VAL)

    StringType declFlagsTemplate           ;


    StringType serializeBeginTemplate      ;
    StringType serializeEndTemplate        ;
    StringType serializeItemTemplate       ;

    StringType deserializeBeginTemplate    ;
    StringType deserializeEndTemplate      ;
    StringType deserializeItemTemplate     ;

    StringType serializeItemSepBeforeFirst ;
    StringType serializeItemSepBefore      ;
    StringType serializeItemSepAfter       ;

    StringType serializeSetTemplate        ;
    StringType deserializeSetTemplate      ;

    StringType setSerializeSetType         ;

    static
    EnumGeneratorTemplate defaultCpp()
    {
        EnumGeneratorTemplate res;

        res.declBeginTemplate            = make_string<StringType>(" enum $(CLASS) $(ENAMNAME)");
        res.declBeginUnderlyingTemplate  = make_string<StringType>(" enum $(CLASS) $(ENAMNAME) : $(UNDERLYING)");

        res.declClass                    = make_string<StringType>("class");

        res.castTemplate                 = make_string<StringType>("($(UNDERLYING))($(ITEMVAL))");

        res.scopeBeginTemplate           = make_string<StringType>("\n$(INDENT){");
        res.scopeEndTemplate             = make_string<StringType>("\n\n$(INDENT)}; // $(DECLBEGIN)\n");

        //res.itemValAssign           = make_string<StringType>("=");
        res.declItemSepBeforeFirst       = make_string<StringType>("\n");
        res.declItemSepBefore            = make_string<StringType>(",\n");
        res.declItemSepAfter             = make_string<StringType>("");

        res.declItemTemplate             = make_string<StringType>(" $(ITEMNAME) = $(ITEMVAL)");

        res.declFlagsTemplate            = make_string<StringType>("MARTY_CPP_MAKE_ENUM_FLAGS($(ENAMNAME))\n");

        res.serializeBeginTemplate       = make_string<StringType>(" MARTY_CPP_ENUM$(PPCLASS)_SERIALIZE_BEGIN( $(ENAMNAME), $(MAPTYPE), $(UPPERFLAG) )\n");
        res.serializeEndTemplate         = make_string<StringType>(" MARTY_CPP_ENUM$(PPCLASS)_SERIALIZE_END( $(ENAMNAME), $(MAPTYPE), $(UPPERFLAG) )\n");
        res.serializeItemTemplate        = make_string<StringType>(" MARTY_CPP_ENUM$(PPCLASS)_SERIALIZE_ITEM( $(ITEMNAME), $(ITEMVAL) )"  );

        res.deserializeBeginTemplate     = make_string<StringType>(" MARTY_CPP_ENUM$(PPCLASS)_DESERIALIZE_BEGIN( $(ENAMNAME), $(MAPTYPE), $(UPPERFLAG) )\n");
        res.deserializeEndTemplate       = make_string<StringType>(" MARTY_CPP_ENUM$(PPCLASS)_DESERIALIZE_END( $(ENAMNAME), $(MAPTYPE), $(UPPERFLAG) )\n");
        res.deserializeItemTemplate      = make_string<StringType>(" MARTY_CPP_ENUM$(PPCLASS)_DESERIALIZE_ITEM( $(ITEMNAME), $(ITEMVAL) )" );

        res.serializeItemSepBeforeFirst  = make_string<StringType>("");
        res.serializeItemSepBefore       = make_string<StringType>("");
        res.serializeItemSepAfter        = make_string<StringType>(";\n");

        res.serializeSetTemplate         = make_string<StringType>("MARTY_CPP_ENUM$(PPCLASS)_SERIALIZE_SET($(ENAMNAME), $(SETTYPE))\n");
        res.deserializeSetTemplate       = make_string<StringType>("MARTY_CPP_ENUM$(PPCLASS)_DESERIALIZE_SET($(ENAMNAME), $(SETTYPE))\n");
        
        return res;
    }

    StringType makeClassMacroVal(unsigned options) const
    {
        StringType ccClass;
        if (options&EnumGeneratorOptionFlags::enumFlags)
            ccClass = declClass;
        else if (options&EnumGeneratorOptionFlags::enumClass)
            ccClass = declClass;

        return ccClass;
    }

    StringType makePpClassMacroVal(unsigned options) const
    {
        StringType ppClass;
        if (options&EnumGeneratorOptionFlags::enumFlags)
            ppClass = make_string<StringType>("_FLAGS");
        else if (options&EnumGeneratorOptionFlags::enumClass)
            ppClass = make_string<StringType>("_CLASS");

        return ppClass;
    }

    StringType replaceLeadingSpaceToIndentMacro(const StringType &str) const
    {
        if (str.empty() || str[0]!=(typename StringType::value_type)' ')
            return str;
        StringType res = make_string<StringType>("$(INDENT)");
        res.append(str, 1);
        return res;
    }

    StringType formatCastToUnderlying(const StringType &underlyingTypeName, const StringType &val) const
    {
        if (underlyingTypeName.empty())
            return val;

        auto res = castTemplate;
        // StringType
        res = simple_string_replace( res, make_string<StringType>("$(UNDERLYING)"), underlyingTypeName );
        res = simple_string_replace( res, make_string<StringType>("$(ITEMVAL)"), val );
        return res;
    }

    StringType formatDeclBegin( const StringType &indent, const StringType &enumName, const StringType &underlyingTypeName, unsigned options ) const
    {
        StringType res = replaceLeadingSpaceToIndentMacro(underlyingTypeName.empty() ? declBeginTemplate : declBeginUnderlyingTemplate);

        res = simple_string_replace( res, make_string<StringType>("$(UNDERLYING)"), underlyingTypeName );
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)"), indent );
        res = simple_string_replace( res, make_string<StringType>("$(CLASS)"), makeClassMacroVal(options) );
        res = simple_string_replace( res, make_string<StringType>("$(PPCLASS)"), makePpClassMacroVal(options) );
        res = simple_string_replace( res, make_string<StringType>("$(ENAMNAME)"), enumName );
        return res;
    }

    StringType formatScopeBegin( const StringType &indent, const StringType &declBegin ) const
    {
        StringType res = replaceLeadingSpaceToIndentMacro(scopeBeginTemplate);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)"), indent );
        res = simple_string_replace( res, make_string<StringType>("$(DECLBEGIN)"), declBegin );
        return res;
    }

    StringType formatScopeEnd( const StringType &indent, const StringType &declBegin ) const
    {
        StringType res = replaceLeadingSpaceToIndentMacro(scopeEndTemplate);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)"), indent );
        res = simple_string_replace( res, make_string<StringType>("$(DECLBEGIN)"), declBegin );
        return res;
    }

    StringType formatDeclFlags( const StringType &indent, const StringType &enumName, unsigned options ) const
    {
        StringType res = replaceLeadingSpaceToIndentMacro(declFlagsTemplate);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)")   , indent );
        res = simple_string_replace( res, make_string<StringType>("$(ENAMNAME)"), enumName );
        return res;
    }

    StringType getDeclItemSepBefore( std::size_t nItem ) const
    {
        return nItem ? declItemSepBefore : declItemSepBeforeFirst;
    }

    StringType getSerializeItemSepBefore( std::size_t nItem ) const
    {
        return nItem ? serializeItemSepBefore : serializeItemSepBeforeFirst;
    }

    StringType formatDeclItem( std::size_t nItem, const StringType &indent, const StringType &name, const StringType &val, unsigned options, std::size_t nNameLen = 32 ) const
    {
        auto nameExpanded = expand_copy(name, nNameLen);
        StringType res = replaceLeadingSpaceToIndentMacro(declItemTemplate);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)"), indent );
        res = simple_string_replace( res, make_string<StringType>("$(ITEMNAME)"), nameExpanded );
        res = simple_string_replace( res, make_string<StringType>("$(ITEMVAL)"), val );
        return getDeclItemSepBefore(nItem) + res + declItemSepAfter;
    }

    StringType formatSerializeTemplateImpl( const StringType &tpl, const StringType &indent, const StringType &name, unsigned options ) const
    {
        StringType mapType   = make_string<StringType>( options&EnumGeneratorOptionFlags::useUnorderedMap ? "std::unordered_map" : "std::map" );
        StringType setType   = make_string<StringType>( options&EnumGeneratorOptionFlags::useUnorderedMap ? "std::unordered_set" : "std::set" );
        StringType lowerFlag = make_string<StringType>( options&EnumGeneratorOptionFlags::lowercaseDeserelialize ? "1" : "0" );

        StringType res = replaceLeadingSpaceToIndentMacro(tpl);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)")   , indent );
        res = simple_string_replace( res, make_string<StringType>("$(PPCLASS)")  , makePpClassMacroVal(options) );
        res = simple_string_replace( res, make_string<StringType>("$(MAPTYPE)")  , mapType );
        res = simple_string_replace( res, make_string<StringType>("$(SETTYPE)")  , setType );
        res = simple_string_replace( res, make_string<StringType>("$(UPPERFLAG)"), lowerFlag );
        res = simple_string_replace( res, make_string<StringType>("$(ENAMNAME)") , name );

        return res;
    }

    StringType formatSerializeItemTemplateImpl( const StringType &tpl, std::size_t nItem, const StringType &indent, const StringType &enumName, const StringType &name, const StringType &val, unsigned options, std::size_t nNameLen = 32, std::size_t nValLen = 32 ) const
    {
        StringType mapType   = make_string<StringType>( options&EnumGeneratorOptionFlags::useUnorderedMap ? "std::unordered_map" : "std::map" );
        StringType setType   = make_string<StringType>( options&EnumGeneratorOptionFlags::useUnorderedMap ? "std::unordered_set" : "std::set" );
        StringType lowerFlag = make_string<StringType>( options&EnumGeneratorOptionFlags::lowercaseDeserelialize ? "1" : "0" );

        auto nameExpanded = expand_copy((options&EnumGeneratorOptionFlags::enumClass) ? (enumName + make_string<StringType>("::") + name) : name, nNameLen);
        auto valExpanded  = expand_copy(val, nValLen);

        StringType res = replaceLeadingSpaceToIndentMacro(tpl);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)")   , indent );
        res = simple_string_replace( res, make_string<StringType>("$(PPCLASS)")  , makePpClassMacroVal(options) );
        res = simple_string_replace( res, make_string<StringType>("$(MAPTYPE)")  , mapType );
        res = simple_string_replace( res, make_string<StringType>("$(SETTYPE)")  , setType );
        res = simple_string_replace( res, make_string<StringType>("$(UPPERFLAG)"), lowerFlag );
        res = simple_string_replace( res, make_string<StringType>("$(ITEMNAME)") , nameExpanded );
        res = simple_string_replace( res, make_string<StringType>("$(ITEMVAL)")  , valExpanded );

        return getSerializeItemSepBefore(nItem) + res + serializeItemSepAfter;
    }

    StringType formatSerializeBegin( const StringType &indent, const StringType &name, unsigned options ) const
    {
        return formatSerializeTemplateImpl( serializeBeginTemplate, indent, name, options );
    }

    StringType formatSerializeEnd( const StringType &indent, const StringType &name, unsigned options ) const
    {
        return formatSerializeTemplateImpl( serializeEndTemplate, indent, name, options );
    }

    StringType formatDeserializeBegin( const StringType &indent, const StringType &name, unsigned options ) const
    {
        return formatSerializeTemplateImpl( deserializeBeginTemplate, indent, name, options );
    }

    StringType formatDeserializeEnd( const StringType &indent, const StringType &name, unsigned options ) const
    {
        return formatSerializeTemplateImpl( deserializeEndTemplate, indent, name, options );
    }

    StringType formatSerializeItem( std::size_t nItem, const StringType &indent, const StringType &enumName, const StringType &name, const StringType &val, unsigned options, std::size_t nNameLen = 32, std::size_t nValLen = 32 ) const
    {
        return formatSerializeItemTemplateImpl( serializeItemTemplate, nItem, indent, enumName, name, val, options, nNameLen, nValLen );
    }

    StringType formatDeserializeItem( std::size_t nItem, const StringType &indent, const StringType &enumName, const StringType &name, const StringType &val, unsigned options, std::size_t nNameLen = 32, std::size_t nValLen = 32 ) const
    {
        return formatSerializeItemTemplateImpl( deserializeItemTemplate, nItem, indent, enumName, name, val, options, nNameLen, nValLen );
    }

    StringType formatSerializeSetImpl(const StringType &tpl, const StringType &indent, const StringType &enumName, unsigned options) const
    {
        auto setType = setSerializeSetType;
        if (setType.empty())
            setType = make_string<StringType>("std::set");

        StringType res = replaceLeadingSpaceToIndentMacro(tpl);
        res = simple_string_replace( res, make_string<StringType>("$(INDENT)")   , indent   );
        res = simple_string_replace( res, make_string<StringType>("$(PPCLASS)")  , makePpClassMacroVal(options) );
        res = simple_string_replace( res, make_string<StringType>("$(SETTYPE)")  , setType  );
        res = simple_string_replace( res, make_string<StringType>("$(ENAMNAME)") , enumName );
        return res;
    }

    StringType formatSerializeSet(const StringType &indent, const StringType &enumName, unsigned options) const
    {
        return formatSerializeSetImpl(serializeSetTemplate, indent, enumName, options);
    }

    StringType formatDeserializeSet(const StringType &indent, const StringType &enumName, unsigned options) const
    {
        return formatSerializeSetImpl(deserializeSetTemplate, indent, enumName, options);
    }


}; // EnumGeneratorTemplate

//-----------------------------------------------------------------------------
template<typename StringType> inline
StringType makeEnamValueString(const StringType &name, const StringType &prefix, NameStyle nameStyle)
{
    auto fixStartDigit = prefix.empty();
    auto fixedName     = fixName(name,fixStartDigit);
    auto filteredName  = filterName(fixedName);

    bool noMidPrefix = false;

    if (nameStyle==NameStyle::invalid || nameStyle==NameStyle::all)
    {
        noMidPrefix = true;
    }
    else
    {
        filteredName = formatName(filteredName,nameStyle,fixStartDigit);
    }

    StringType midPrefix;

    if (!filteredName.empty() && !isUpper(filteredName[0]) && !isDigit(filteredName[0]))
        midPrefix = make_string<StringType>("_");

    if (prefix.empty() || prefix.back()==(typename StringType::value_type)'_')
        midPrefix = StringType();

    if (!filteredName.empty() && filteredName.front()==(typename StringType::value_type)'_')
        midPrefix = StringType();

    if (noMidPrefix)
        midPrefix = StringType();

    return prefix + midPrefix + filteredName;
}

//-----------------------------------------------------------------------------
inline
unsigned enum_generate_adjust_gen_options(unsigned genOptions)
{
    if (genOptions&EnumGeneratorOptionFlags::enumFlags)
        genOptions |= EnumGeneratorOptionFlags::enumClass;

    if (genOptions&EnumGeneratorOptionFlags::generateDefSerializeSet)
        genOptions |= EnumGeneratorOptionFlags::generateDefSerialize;

    if (genOptions&EnumGeneratorOptionFlags::generateDefDeserializeSet)
        genOptions |= EnumGeneratorOptionFlags::generateDefDeserialize;

    return genOptions;
}

// genOptions = enum_generate_adjust_gen_options(genOptions);
// if (genOptions&EnumGeneratorOptionFlags::enumFlags)


//-----------------------------------------------------------------------------
//! Генерирует собственно само определение enum
template<typename StreamType, typename StringType> inline
void enum_generate_serialize_enum_def( StreamType &ss
                            , const std::vector< std::pair< StringType,StringType > > &vals
                            , const StringType                         &indent
                            , const StringType                         &indentInc
                            , const StringType                         &enumName
                            , const StringType                         &underlayedTypeName
                            , NameStyle                                valuesNameStyle
                            , const StringType                         &valuesPrefix
                            , unsigned                                 genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            )
{
    genOptions = enum_generate_adjust_gen_options(genOptions);


    auto declBegin = genTpl.formatDeclBegin( indent, enumName, underlayedTypeName, genOptions );
    ss << declBegin;

    ss << genTpl.formatScopeBegin(indent,declBegin);

    std::size_t maxNameLen = vals.empty() 
                           ? (std::size_t)0 
                           : std::max_element(vals.begin(), vals.end(), []( const auto &p1, const auto &p2 ){ return p1.first.size()<p2.first.size(); } )->first.size()
                           ;
    maxNameLen = (maxNameLen+2)>48 ? 48 : (maxNameLen+2);

    StringType lineIndent = indent + indentInc;
    std::size_t i = (std::size_t)-1;

    for( const auto& [name,val] : vals)
    {
        ++i;

        if (val==make_string<StringType>("-1") && !underlayedTypeName.empty())
        {
            ss << genTpl.formatDeclItem( i, lineIndent, name, genTpl.formatCastToUnderlying(underlayedTypeName,val), genOptions, maxNameLen );
        }
        else
        {
            ss << genTpl.formatDeclItem( i, lineIndent, name, val, genOptions, maxNameLen );
        }

    }

    ss << genTpl.formatScopeEnd(indent,declBegin);

    if (genOptions&EnumGeneratorOptionFlags::enumFlags)
    {
        ss << "\n";
        ss << genTpl.formatDeclFlags(indent,enumName,genOptions);
    }

}

//-----------------------------------------------------------------------------
//! Генерирует сериализацию значений enum
template<typename StreamType, typename StringType> inline
void enum_generate_serialize_enum_serialize( StreamType &ss
                            , const std::unordered_map< StringType, StringType > &serializeVals
                            , const StringType                         &indent
                            , const StringType                         &indentInc
                            , const StringType                         &enumName
                            , const StringType                         &underlayedTypeName
                            , NameStyle                                valuesNameStyle
                            , NameStyle                                serializedNameStyle
                            , const StringType                         &valuesPrefix
                            , unsigned                                 genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            )
{
    genOptions = enum_generate_adjust_gen_options(genOptions);


    ss << genTpl.formatSerializeBegin( indent, enumName, genOptions );

    std::size_t maxNameLen = serializeVals.empty() 
                           ? (std::size_t)0 
                           : std::max_element(serializeVals.begin(), serializeVals.end(), []( const auto &p1, const auto &p2 ){ return p1.first.size()<p2.first.size(); } )->first.size()
                           ;

    if (genOptions&EnumGeneratorOptionFlags::enumClass)
        maxNameLen += enumName.size()+2;

    maxNameLen = (maxNameLen+2)>48 ? 48 : (maxNameLen+2);

    std::size_t maxValLen  = serializeVals.empty() 
                           ? (std::size_t)0 
                           : std::max_element(serializeVals.begin(), serializeVals.end(), []( const auto &p1, const auto &p2 ){ return p1.second.size()<p2.second.size(); } )->second.size()
                           ;
    maxValLen = (maxValLen+2)>48 ? 48 : (maxValLen+2);


    StringType lineIndent = indent + indentInc;
    std::size_t i = (std::size_t)-1;

    for( const auto& [name,val] : serializeVals)
    {
        ++i;
        ss << genTpl.formatSerializeItem( i, lineIndent
                                        , enumName, name
                                        , make_string<StringType>("\"") + val + make_string<StringType>("\"")
                                        , genOptions
                                        , maxNameLen, maxValLen
                                        );
    }

    ss << genTpl.formatSerializeEnd( indent, enumName, genOptions );

}

//-----------------------------------------------------------------------------
//! Генерирует десериализацию значений enum
template<typename StreamType, typename StringType> inline
void enum_generate_serialize_enum_deserialize( StreamType &ss
                            , const std::unordered_map< StringType, std::unordered_set<StringType> >  &deserializeVals
                            , const StringType                         &indent
                            , const StringType                         &indentInc
                            , const StringType                         &enumName
                            , const StringType                         &underlayedTypeName
                            , NameStyle                                valuesNameStyle
                            , NameStyle                                serializedNameStyle
                            , const StringType                         &valuesPrefix
                            , unsigned                                 genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            )
{
    genOptions = enum_generate_adjust_gen_options(genOptions);


    ss << genTpl.formatDeserializeBegin( indent, enumName, genOptions );

    auto setItemsMaxLen = []( const std::unordered_set<StringType> &s )
    {
        return s.empty()
             ? (std::size_t)0 
             : std::max_element(s.begin(), s.end(), []( const auto &s1, const auto &s2 ){ return s1.size()<s2.size(); } )->size()
             ;
    };

    std::size_t maxNameLen = deserializeVals.empty() 
                           ? (std::size_t)0 
                           : std::max_element(deserializeVals.begin(), deserializeVals.end(), []( const auto &p1, const auto &p2 ){ return p1.first.size()<p2.first.size(); } )->first.size()
                           ;

    if (genOptions&EnumGeneratorOptionFlags::enumClass)
        maxNameLen += enumName.size()+2;

    maxNameLen = (maxNameLen+2)>48 ? 48 : (maxNameLen+2);

    std::size_t maxValLen  = deserializeVals.empty() 
                           ? (std::size_t)0 
                           : setItemsMaxLen(std::max_element(deserializeVals.begin(), deserializeVals.end(), [&]( const auto &p1, const auto &p2 ){ return setItemsMaxLen(p1.second)<setItemsMaxLen(p2.second); } )->second)
                           ;
    maxValLen = (maxValLen+2)>48 ? 48 : (maxValLen+2);


    StringType lineIndent = indent + indentInc;
    std::size_t i = (std::size_t)-1;

    for( const auto& [name,vals] : deserializeVals)
    {
        ++i;
        for( const auto& val : vals)
        ss << genTpl.formatDeserializeItem( i, lineIndent
                                          , enumName, name
                                          , make_string<StringType>("\"") + val + make_string<StringType>("\"")
                                          , genOptions
                                          , maxNameLen, maxValLen
                                          );
    }

    ss << genTpl.formatDeserializeEnd( indent, enumName, genOptions );

}

    // StringType formatDeserializeBegin( const StringType &indent, const StringType &name, unsigned options ) const
    // StringType formatDeserializeEnd( const StringType &indent, const StringType &name, unsigned options ) const
    // StringType formatSerializeItem( const StringType &tpl, std::size_t nItem, const StringType &indent, const StringType &name, const StringType &val, unsigned options, std::size_t nNameLen = 32 ) const
    // StringType formatDeserializeItem( const StringType &tpl, std::size_t nItem, const StringType &indent, const StringType &name, const StringType &val, unsigned options, std::size_t nNameLen = 32 ) const


//-----------------------------------------------------------------------------
template<typename StringType> inline
StringType enum_generate_number_convert(unsigned val, unsigned genOptions)
{
    genOptions = enum_generate_adjust_gen_options(genOptions);

    //std::basic_stringstream< typename StringType::value_type, typename StringType::traits_type, typename StringType::allocator_type >  oss;
    SimpleStringStream<StringType> oss;
    if (val==(unsigned)-1)
    {
        oss << make_string<StringType>("-1");
    }
    else
    {
        if (genOptions&EnumGeneratorOptionFlags::unsignedVals)
            oss << (unsigned)val;
        else
            oss << (int)val;
    }

    return oss.str();
}

//-----------------------------------------------------------------------------
template<typename StringType> inline
void enum_generate_serialize_prepare( std::vector< std::pair< StringType,StringType > >                 &defVals // for enum def
                                    , std::unordered_map< StringType, std::unordered_set<StringType> >  &deserializeVals // keyEnumName -> set of deserialize variants
                                    , std::unordered_map< StringType, StringType >                      &serializeVals // keyEnumName -> serialize str
                                    , std::vector< std::pair< StringType,StringType > >                 vals
                                    , const StringType                                                  &enumName
                                    , const StringType                                                  &underlayedTypeName
                                    , NameStyle                                                         valuesNameStyle
                                    , NameStyle                                                         serializedNameStyle
                                    , const StringType                                                  &valuesPrefix
                                    , unsigned                                                          genOptions
                                    , const EnumGeneratorTemplate<StringType>                           &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                                    , std::vector<StringType>                                           *pDups = 0
                                    , std::vector<StringType>                                           *pDupVals = 0
                                    )
{
    NameStyleSet deserializeNameStyles;

    genOptions = enum_generate_adjust_gen_options(genOptions);


    if (serializedNameStyle==NameStyle::all)
    {
        deserializeNameStyles = makeAllNameStylesSet( true  /* onlyValidStyles */ );
    }
    else
    {
        deserializeNameStyles.insert(serializedNameStyle);
    }

    //unsigned long long counter = 0;
    // const std::vector< std::pair< StringType,unsigned > > &vals
    // enum value name -> enum value pairs

    // Заблаговременно форматируем все имена enum'а
    // Помещаем в map с ключем по имени исходного члена enum'а
    std::unordered_map<StringType, StringType> formattedEnumNames;
    for( const auto& [name,val] : vals)
    {
        auto formattedName = makeEnamValueString(name,valuesPrefix,valuesNameStyle);
        formattedEnumNames[name] = formattedName;
    }

    // Если значение нельзя сконвертировать в число, значит там - не число.
    // Там возможна ссылка на какое-то из значений enum'а, или, возможно, какое-то выражение 
    // с их использованием
    auto formatEnumValue = [&]( const StringType &s )
    {
        if (s.empty())
            return s;

        std::vector<StringType> vec;
        auto inserter = std::back_inserter(vec);
        splitNamesNotNames<decltype(inserter), typename StringType::value_type, typename StringType::traits_type, typename StringType::allocator_type>(inserter, s);

        StringType res; res.reserve(s.size());

        for( const auto& n: vec)
        {
            // Если у нас число, то конвертация пройдёт успешно, и ничего делать не нужно
            // А если выскочит исключение, то это какой-то идентификатор, и его надо проапдейтить в соответствии с правилами
            
            try
            {
                std::size_t pos = 0;
                std::stoll(n, &pos, 0); // base: auto
                if (pos==n.size())
                {
                    res.append( n );
                }
                else
                {
                    auto iter = formattedEnumNames.find(n);
                    res.append( iter==formattedEnumNames.end() ? n : iter->second );
                }
                //    continue;
            }
            catch(...)
            {
                auto iter = formattedEnumNames.find(n);
                res.append( iter==formattedEnumNames.end() ? n : iter->second );
            }

        }
    
        return res;
    };

    auto generateDeserializeNames = [&]( const StringType &s )
    {
        std::unordered_set<StringType> res;

        try
        {
            std::size_t pos = 0;
            std::stoll(s, &pos, 0); // base: auto, пробуем сконвертить в целое
            if (pos==s.size())
            {
                // конвертация прошла успешно, у нас - имя, которое выглядит, как число
                if (genOptions&EnumGeneratorOptionFlags::integerDeserelialize)
                {
                    // Но также у нас разрешена десериализация из чисел
                    // А имя, которое выглядит как число, может иметь константу, не соответствующую своему имени
                    // Так, для виртуальных клавиш:
                    // vkM - клавиша - 'M', код - 77, соответствует коду символа 'M'
                    // vk8 - клавиша - '8', код - 56, соответствует коду символа '8'
                    // При десериализации чисел '8' будет использована как число 8 и преобразовано
                    // в элемент vkBack = 8
                    return res; // В данном случае числовые имена нельзя рассматривать, как годные строки для (де)сериализации
                }
            }
                
        }
        catch(...)
        {
        }

        for( auto nameStyle : deserializeNameStyles)
        {
            StringType tmp = nameStyle==NameStyle::unknownStyle
                           ? s
                           : formatName(s,nameStyle, false /* fixStartDigit */ )
                           ;
            if (genOptions&EnumGeneratorOptionFlags::lowercaseDeserelialize)
                tmp = toLower(tmp);

            res.insert(tmp);
        }

        return res;

    };


    // У нас есть куча имен enum'а, в определенном порядке, порядок важен для декларации enum'а
    // У нас есть одно из этих имен, являющееся "ключевым" - оно используется сериализации/десериализации
    // Также оно используется, если включен режим EnumGeneratorOptionFlags::singleDef
    // Для каждого значения enum'а у нас будет куча нагенеренных идентификаторов для десериализации

    std::unordered_set<StringType> usedEnumValNames;
    std::vector<StringType> duplicatedEnumValNames;
    std::vector<StringType> duplicatedEnumVals;

    std::unordered_map<StringType,StringType> enumValToKeyName; // enum val -> enum val name

    //StringType lineIndent = indent + indentInc;
    std::size_t i = (std::size_t)-1;

    for( const auto& [name,val] : vals)
    {
        ++i;

        if (usedEnumValNames.find(name)!=usedEnumValNames.end())
        {
            duplicatedEnumValNames.emplace_back(name);
            continue;
        }
        else
        {
            usedEnumValNames.insert(name);
        }

        auto formattedEnumName = makeEnamValueString(name,valuesPrefix,valuesNameStyle);
        auto formattedEnumVal  = formatEnumValue(val);

        auto [enumValToKeyNameIt, firstValOccurence] = enumValToKeyName.try_emplace(formattedEnumVal, formattedEnumName);


        if (firstValOccurence || 0==(genOptions&EnumGeneratorOptionFlags::singleDef))
        {
            defVals.emplace_back(formattedEnumName,formattedEnumVal);
        }

        if (!firstValOccurence)
        {
            duplicatedEnumVals.emplace_back(formattedEnumVal);
        }

        if (firstValOccurence)
        {
            StringType serializedName = serializedNameStyle==NameStyle::unknownStyle 
                                      ? name
                                      : ( serializedNameStyle==NameStyle::all
                                        ? formatName(name,NameStyle::pascalStyle, false /* fixStartDigit */ )
                                        : formatName(name,serializedNameStyle, false /* fixStartDigit */ )
                                        )
                                      ;
            serializeVals[formattedEnumName] = serializedName;
        }
        else
        {
            i = i;
        }

        auto deserializeNames = generateDeserializeNames(name);
        if (genOptions&EnumGeneratorOptionFlags::integerDeserelialize)
        {
            try
            {
                std::size_t pos = 0;
                std::stoll(val, &pos, 0); // base: auto, пробуем сконвертить в целое
                if (pos==val.size())
                    deserializeNames.insert(val);
            }
            catch(...)
            {
            }
        }

        auto deserializeKey = enumValToKeyNameIt->second;

        deserializeVals[deserializeKey].insert(deserializeNames.begin(),deserializeNames.end());

    }

    if (pDups)
       *pDups = duplicatedEnumValNames;

    if (pDupVals)
       *pDupVals = duplicatedEnumVals;

}

//-----------------------------------------------------------------------------
template<typename StreamType, typename StringType> inline
void enum_generate_serialize( StreamType &ss
                            , const std::vector< std::pair< StringType,StringType > > &vals
                            , const StringType                         &indent
                            , const StringType                         &indentInc
                            , const StringType                         &enumName
                            , const StringType                         &underlayedTypeName
                            , NameStyle                                valuesNameStyle
                            , NameStyle                                serializedNameStyle
                            , const StringType                         &valuesPrefix
                            , unsigned                                 genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            , std::vector<StringType>                  *pDups = 0
                            , std::vector<StringType>                  *pDupVals = 0
                            )
{
    genOptions = enum_generate_adjust_gen_options(genOptions);


    if ((genOptions&EnumGeneratorOptionFlags::generateDefAll)==0)
        return;

    std::vector< std::pair< StringType,StringType > > defVals; // for enum def
    std::unordered_map< StringType, std::unordered_set<StringType> >  deserializeVals; // keyEnumName -> set of deserialize variants
    std::unordered_map< StringType, StringType >                      serializeVals; // keyEnumName -> serialize str

    enum_generate_serialize_prepare( defVals, deserializeVals, serializeVals
                                   , vals, enumName, underlayedTypeName
                                   , valuesNameStyle, serializedNameStyle
                                   , valuesPrefix, genOptions, genTpl
                                   , pDups, pDupVals
                                   );


    if (genOptions&EnumGeneratorOptionFlags::generateDefType)
    {
        if ((genOptions&EnumGeneratorOptionFlags::noExtraLinefeed)==0)
            ss << make_string<StringType>("\n");
        enum_generate_serialize_enum_def( ss, defVals, indent, indentInc, enumName, underlayedTypeName, valuesNameStyle, valuesPrefix, genOptions, genTpl );
    }

    if (genOptions&EnumGeneratorOptionFlags::generateDefSerialize)
    {
        if ((genOptions&EnumGeneratorOptionFlags::noExtraLinefeed)==0)
            ss << make_string<StringType>("\n");
        enum_generate_serialize_enum_serialize( ss, serializeVals, indent, indentInc, enumName, underlayedTypeName, valuesNameStyle, serializedNameStyle, valuesPrefix, genOptions, genTpl );
    }

    if (genOptions&EnumGeneratorOptionFlags::generateDefDeserialize)
    {
        if ((genOptions&EnumGeneratorOptionFlags::noExtraLinefeed)==0)
            ss << make_string<StringType>("\n");
        enum_generate_serialize_enum_deserialize( ss, deserializeVals, indent, indentInc, enumName, underlayedTypeName, valuesNameStyle, serializedNameStyle, valuesPrefix, genOptions, genTpl );
    }

    if (genOptions&EnumGeneratorOptionFlags::generateDefSerializeSet)
    {
        if ((genOptions&EnumGeneratorOptionFlags::noExtraLinefeed)==0)
            ss << make_string<StringType>("\n");
        ss << genTpl.formatSerializeSet(indent, enumName, genOptions);
    }

    if (genOptions&EnumGeneratorOptionFlags::generateDefDeserializeSet)
    {
        if ((genOptions&EnumGeneratorOptionFlags::noExtraLinefeed)==0)
            ss << make_string<StringType>("\n");
        ss << genTpl.formatDeserializeSet(indent, enumName, genOptions);
    }

    if ((genOptions&EnumGeneratorOptionFlags::noExtraLinefeed)==0)
        ss << make_string<StringType>("\n");

}


//-----------------------------------------------------------------------------
template<typename StreamType, typename StringType> inline
void enum_generate_serialize( StreamType &ss
                            , const std::vector< std::pair< StringType,unsigned > > &vals
                            , const StringType                         &indent
                            , const StringType                         &indentInc
                            , const StringType                         &enumName
                            , const StringType                         &underlayedTypeName
                            , NameStyle                                valuesNameStyle
                            , NameStyle                                serializedNameStyle
                            , const StringType                         &valuesPrefix
                            , unsigned                                 genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            , std::vector<StringType>                  *pDups = 0
                            , std::vector<StringType>                  *pDupVals = 0
                            )
{
    genOptions = enum_generate_adjust_gen_options(genOptions);


    std::vector< std::pair< StringType,StringType > > strVals;
    strVals.reserve(vals.size());

    for( const auto& [name,val] : vals)
    {
        strVals.emplace_back(name, enum_generate_number_convert<StringType>(val,genOptions));
    }
    
    enum_generate_serialize( ss, strVals
                           , indent, indentInc
                           , enumName, underlayedTypeName
                           , valuesNameStyle, serializedNameStyle
                           , valuesPrefix
                           , genOptions, genTpl, pDups, pDupVals
                           );
}


//-----------------------------------------------------------------------------
template<typename StreamType, typename StringType> inline
void enum_generate_serialize( StreamType &ss
                            , const StringType                         &valsStr
                            , const StringType                         &indent
                            , const StringType                         &indentInc
                            , const StringType                         &enumName
                            , const StringType                         &underlayedTypeName
                            , NameStyle                                valuesNameStyle
                            , NameStyle                                serializedNameStyle
                            , const StringType                         &valuesPrefix
                            , unsigned                                 genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            , std::vector<StringType>                  *pDups = 0
                            , std::vector<StringType>                  *pDupVals = 0
                            )
{
    genOptions = enum_generate_adjust_gen_options(genOptions);


    auto valsStrPrepared = simple_string_replace<StringType>(valsStr, make_string<StringType>("\n"), make_string<StringType>(";") /* , typename StringType::size_type nSplits = -1 */ );

    auto enumItems = simple_string_split(valsStrPrepared, make_string<StringType>(";") /* , typename StringType::size_type nSplits = -1 */ );

    auto isSpaceChar = [](typename StringType::value_type ch)
                         {
                             typedef typename StringType::value_type CharType; 
                             return ch==(CharType)' ' || ch==(CharType)'\t' || ch==(CharType)'\r' || ch==(CharType)'\n';
                         };

    std::vector< std::pair< StringType,StringType> > vals;

    genOptions = enum_generate_adjust_gen_options(genOptions);


    auto calcNextCounterVal = [&](unsigned long long curVal) -> unsigned long long
        {
            if (genOptions&EnumGeneratorOptionFlags::enumFlags)
            {
                if (curVal==0)
                    return 1;
                else if (curVal==(unsigned long long)-1)
                    return 0;
                return curVal<<1;
            }
            else
            {
                return curVal+1;
            }
        };

    unsigned long long  lastValCounter = (genOptions&EnumGeneratorOptionFlags::enumFlags) ? 0 : (unsigned long long)-1;
    StringType          lastVal;

    for( auto &i: enumItems)
    {
        i = simple_trim(i, isSpaceChar);
        if (i.empty() || i[0]==(typename StringType::value_type)'#')
            continue;

        i = simple_string_replace<StringType>(i, make_string<StringType>(":"), make_string<StringType>("="));
        std::vector< StringType > namesAndVal = simple_string_split(i, make_string<StringType>("="), 1 );

        if (namesAndVal.empty())
            continue;

        StringType &namesStr = namesAndVal[0];
        namesStr = simple_string_replace<StringType>(namesStr, make_string<StringType>("/"), make_string<StringType>(","));
        auto names = simple_string_split(simple_trim(namesStr, isSpaceChar), make_string<StringType>(","));

        bool lastValUpdated = false;
        for( auto &name: names)
        {
            name = simple_trim(name, isSpaceChar);
            if (name.empty())
                continue;

            if (!lastValUpdated)
            {
                lastValUpdated = true;
                if (namesAndVal.size()<2)
                {
                    lastValCounter = calcNextCounterVal(lastValCounter);
                    lastVal = enum_generate_number_convert<StringType>(lastValCounter, genOptions);
                }
                else
                {
                    auto strVal = simple_trim(namesAndVal[1], isSpaceChar);
                    if (strVal.empty())
                    {
                        lastValCounter = calcNextCounterVal(lastValCounter);
                        lastVal = enum_generate_number_convert<StringType>(lastValCounter, genOptions);
                    }
                    else
                    {
                        try
                        {
                            std::size_t pos = 0;
                            lastValCounter = (unsigned)std::stoll(strVal, &pos, 0);
                            if (pos==strVal.size())
                                lastVal = enum_generate_number_convert<StringType>(lastValCounter, genOptions);
                            else
                                lastVal = strVal;
                        }
                        catch(...)
                        {
                            lastVal = strVal;
                        }
                    }
                }
            }

            vals.emplace_back(name, lastVal);
        }
    }

    enum_generate_serialize<StreamType,StringType>( ss, vals, indent, indentInc, enumName, underlayedTypeName, valuesNameStyle, serializedNameStyle, valuesPrefix, genOptions, genTpl, pDups, pDupVals );

    //enum_generate_serialized_enum_def( ss, vals, enumName, valuesNameStyle, valuesPrefix, enumClass );
}

//-----------------------------------------------------------------------------
template<typename StreamType, typename StringType> inline
void enum_generate_serialize( StreamType &ss
                            , const StringType &valsStr
                            , const StringType &indent
                            , const StringType &indentInc
                            , const StringType &enumName
                            , const StringType &underlayedTypeName
                            , const StringType &valuesNameStyle
                            , const StringType &serializedNameStyle
                            , const StringType &valuesPrefix
                            , unsigned         genOptions
                            , const EnumGeneratorTemplate<StringType>  &genTpl = EnumGeneratorTemplate<StringType>::defaultCpp()
                            , std::vector<StringType> *pDups = 0
                            )
{
    if (genOptions&EnumGeneratorOptionFlags::enumFlags)
        genOptions |= EnumGeneratorOptionFlags::enumClass;


    enum_generate_serialize( ss, valsStr, indent, indentInc, enumName, underlayedTypeName
                           , fromString<StringType>(valuesNameStyle, NameStyle::defaultStyle)
                           , fromString<StringType>(serializedNameStyle, NameStyle::defaultStyle /* all */ )
                           , valuesPrefix
                           , genOptions
                           , genTpl
                           , pDups
                           );
}

//-----------------------------------------------------------------------------






//-----------------------------------------------------------------------------
} // namespace marty_cpp



