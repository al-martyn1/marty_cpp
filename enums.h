#pragma once

#include "marty_cpp.h"
#include "marty_enum.h"
#include "marty_flags.h"

namespace marty_cpp{

enum  ELinefeedType
{
    invalid   = -1,
    unknown   = -1,
    detect    = 0,
    lf        = 1,
    cr        = 2,
    lfcr      = 3,
    crlf      = 4

}; // enum  ELinefeedType

MARTY_CPP_ENUM_SERIALIZE_BEGIN( ELinefeedType, std::map, 1 )
    MARTY_CPP_ENUM_SERIALIZE_ITEM( cr       , "Cr"      );
    MARTY_CPP_ENUM_SERIALIZE_ITEM( invalid  , "Invalid" );
    MARTY_CPP_ENUM_SERIALIZE_ITEM( lfcr     , "Lfcr"    );
    MARTY_CPP_ENUM_SERIALIZE_ITEM( detect   , "Detect"  );
    MARTY_CPP_ENUM_SERIALIZE_ITEM( lf       , "Lf"      );
    MARTY_CPP_ENUM_SERIALIZE_ITEM( crlf     , "Crlf"    );
MARTY_CPP_ENUM_SERIALIZE_END( ELinefeedType, std::map, 1 )

MARTY_CPP_ENUM_DESERIALIZE_BEGIN( ELinefeedType, std::map, 1 )
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( cr       , "cr"      );
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( invalid  , "invalid" );
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( invalid  , "unknown" );
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( lfcr     , "lfcr"    );
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( detect   , "detect"  );
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( lf       , "lf"      );
    MARTY_CPP_ENUM_DESERIALIZE_ITEM( crlf     , "crlf"    );
MARTY_CPP_ENUM_DESERIALIZE_END( ELinefeedType, std::map, 1 )

} // marty_cpp
