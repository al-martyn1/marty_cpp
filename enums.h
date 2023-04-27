#pragma once

#include "marty_cpp.h"
#include "marty_enum.h"
#include "marty_flags.h"

namespace marty_cpp{

enum class ELinefeedType
{
    invalid   = -1,
    unknown   = -1,
    detect    = 0,
    lf        = 1,
    cr        = 2,
    lfcr      = 3,
    crlf      = 4

}; // enum class ELinefeedType

MARTY_CPP_ENUM_CLASS_SERIALIZE_BEGIN( ELinefeedType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELinefeedType::cr       , "Cr"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELinefeedType::invalid  , "Invalid" );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELinefeedType::lfcr     , "Lfcr"    );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELinefeedType::detect   , "Detect"  );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELinefeedType::lf       , "Lf"      );
    MARTY_CPP_ENUM_CLASS_SERIALIZE_ITEM( ELinefeedType::crlf     , "Crlf"    );
MARTY_CPP_ENUM_CLASS_SERIALIZE_END( ELinefeedType, std::map, 1 )

MARTY_CPP_ENUM_CLASS_DESERIALIZE_BEGIN( ELinefeedType, std::map, 1 )
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::cr       , "cr"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::invalid  , "invalid" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::invalid  , "unknown" );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::lfcr     , "lfcr"    );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::detect   , "detect"  );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::lf       , "lf"      );
    MARTY_CPP_ENUM_CLASS_DESERIALIZE_ITEM( ELinefeedType::crlf     , "crlf"    );
MARTY_CPP_ENUM_CLASS_DESERIALIZE_END( ELinefeedType, std::map, 1 )

} // marty_cpp
