/*! \file
    \brief Helpers for flags
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
#include <type_traits>

#include <cwctype>
#include <cctype>

#include "marty_enum.h"

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------

// https://stackoverflow.com/questions/1448396/how-to-use-enums-as-flags-in-c

#define MARTY_CPP_MAKE_ENUM_FLAGS(TEnum)                                                       \
    inline constexpr bool operator==(TEnum a, std::underlying_type<TEnum>::type b) {           \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TUnder>(a) == b;                                                    \
    }                                                                                          \
    inline constexpr bool operator==(std::underlying_type<TEnum>::type a, TEnum b) {           \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return a == static_cast<TUnder>(b);                                                    \
    }                                                                                          \
    inline constexpr bool operator!=(TEnum a, std::underlying_type<TEnum>::type b) {           \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TUnder>(a) != b;                                                    \
    }                                                                                          \
    inline constexpr bool operator!=(std::underlying_type<TEnum>::type a, TEnum b) {           \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return a != static_cast<TUnder>(b);                                                    \
    }                                                                                          \
    inline constexpr TEnum operator<<(TEnum a, unsigned b) {                                   \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TEnum>(static_cast<TUnder>(a) << b);                                \
    }                                                                                          \
    inline constexpr TEnum operator>>(TEnum a, unsigned b) {                                   \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TEnum>(static_cast<TUnder>(a) >> b);                                \
    }                                                                                          \
    inline constexpr TEnum operator~(TEnum a) {                                                \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TEnum>(~static_cast<TUnder>(a));                                    \
    }                                                                                          \
    inline constexpr TEnum operator|(TEnum a, TEnum b) {                                       \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TEnum>(static_cast<TUnder>(a) | static_cast<TUnder>(b));            \
    }                                                                                          \
    inline constexpr TEnum operator&(TEnum a, TEnum b) {                                       \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TEnum>(static_cast<TUnder>(a) & static_cast<TUnder>(b));            \
    }                                                                                          \
    inline constexpr TEnum operator^(TEnum a, TEnum b) {                                       \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        return static_cast<TEnum>(static_cast<TUnder>(a) ^ static_cast<TUnder>(b));            \
    }                                                                                          \
    inline constexpr TEnum& operator<<=(TEnum& a, unsigned b) {                                \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        a = static_cast<TEnum>(static_cast<TUnder>(a) << b );                                  \
        return a;                                                                              \
    }                                                                                          \
    inline constexpr TEnum& operator>>=(TEnum& a, unsigned b) {                                \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        a = static_cast<TEnum>(static_cast<TUnder>(a) >> b );                                  \
        return a;                                                                              \
    }                                                                                          \
    inline constexpr TEnum& operator|=(TEnum& a, TEnum b) {                                    \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        a = static_cast<TEnum>(static_cast<TUnder>(a) | static_cast<TUnder>(b));               \
        return a;                                                                              \
    }                                                                                          \
    inline constexpr TEnum& operator&=(TEnum& a, TEnum b) {                                    \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        a = static_cast<TEnum>(static_cast<TUnder>(a) & static_cast<TUnder>(b));               \
        return a;                                                                              \
    }                                                                                          \
    inline constexpr TEnum& operator^=(TEnum& a, TEnum b) {                                    \
        using TUnder = typename std::underlying_type<TEnum>::type;                             \
        a = static_cast<TEnum>(static_cast<TUnder>(a) ^ static_cast<TUnder>(b));               \
        return a;                                                                              \
    }


//----------------------------------------------------------------------------
#define MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( enumTypeName, mapType, doUpper )\
        MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( enumTypeName, mapType, doUpper )

#define MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( val, valStr )\
        MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( val, valStr )

#define MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( enumTypeName, mapType, doUpper )\
        MARTY_CPP_ENUM_CLASS_SERIALIZE_END( enumTypeName, mapType, doUpper )

//------------------------------
#define MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( enumTypeName, mapType, doUpper )\
        MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( enumTypeName, mapType, doUpper )

#define MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( val, valStr )\
        MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( val, valStr )

#define MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( enumTypeName, mapType, doUpper )\
        MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( enumTypeName, mapType, doUpper )

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
#define MARTY_CPP_ENUM_FLAGS_SERIALIZE_SET(enumTypeName, setType)            \
                                                                             \
inline                                                                       \
std::string enum_serialize_flags_##enumTypeName( enumTypeName enumVal, const char *seps = "|+,")                 \
{                                                                                                                \
    return marty_cpp::serializeEnumFlagsImpl(enumVal, enum_serialize_##enumTypeName, seps);                      \
}                                                                                                                \
                                                                                                                 \
inline                                                                                                           \
std::string enum_serialize_flags_##enumTypeName( enumTypeName enumVal, const std::string &seps)                  \
{                                                                                                                \
    return marty_cpp::serializeEnumFlagsImpl(enumVal, enum_serialize_##enumTypeName, seps);                      \
}                                                                                                                \
                                                                                                                 \
inline                                                                                                           \
std::string enum_serialize_flags( enumTypeName enumVal, const char *seps = "|+,")                                \
{                                                                                                                \
    return marty_cpp::serializeEnumFlagsImpl(enumVal, enum_serialize_##enumTypeName, seps);                      \
}                                                                                                                \
                                                                                                                 \
inline                                                                                                           \
std::string enum_serialize_flags( enumTypeName enumVal, const std::string &seps)                                 \
{                                                                                                                \
    return marty_cpp::serializeEnumFlagsImpl(enumVal, enum_serialize_##enumTypeName, seps);                      \
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
#define MARTY_CPP_ENUM_FLAGS_DESERIALIZE_SET(enumTypeName, setType)



//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace marty_cpp
{




//-----------------------------------------------------------------------------
template< typename EnumType
        , typename EnumTypeSerializer
        > inline
std::string serializeEnumFlagsImpl( EnumType enumVal
                                , EnumTypeSerializer serializer
                                , const char *seps // используем только первый элемент
                                )
{
    const char sepChar = (seps && seps[0]) ? '|' : seps[0];

    std::string res;

    typedef typename std::underlying_type<EnumType>::type  EnumUnderlyingType;

    using EnumUnderlyingUnsignedType = typename std::make_unsigned<EnumUnderlyingType>::type;

    // Calc max bit
    EnumUnderlyingUnsignedType curBit = ~(((EnumUnderlyingUnsignedType)-1)>>1);

    for(; curBit; curBit>>=1)
    {
        auto testVal = enumVal&((EnumType)curBit);
        if (testVal==0)
            continue;

        auto enumValStr = serializer(testVal);

        if (!res.empty())
            res.append(1,sepChar);

        res.append(enumValStr);

    }

    return res;
}

//-----------------------------------------------------------------------------
template< typename EnumType
        , typename EnumTypeSerializer
        > inline
std::string serializeEnumFlagsImpl( EnumType enumVal
                                , EnumTypeSerializer serializer
                                , const std::string &seps // используем только первый элемент
                                )
{
    return serializeEnumFlagsImpl(enumVal, serializer, seps.c_str());
}

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------
template< typename EnumType
        , typename EnumTypeDeserializer
        > inline
void deserializeEnumFlagsImpl( EnumType enumVal
                           , const std::string &str
                           , EnumTypeDeserializer deserializer
                           , const char *seps
                           )
{
}

//-----------------------------------------------------------------------------
template< typename EnumType
        , typename EnumTypeDeserializer
        > inline
void deserializeEnumFlagsImpl( EnumType enumVal
                           , const std::string &str
                           , EnumTypeDeserializer deserializer
                           , const std::string &seps
                           )
{
    return deserializeEnumFlagsImpl(enumVal, str, deserializer, seps.c_str());
}




//-----------------------------------------------------------------------------
} // namespace marty_cpp





//-----------------------------------------------------------------------------

