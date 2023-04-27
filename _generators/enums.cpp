/*! \file
    \brief Генерация enum и сериализации для отрисовки иконок
*/

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "../marty_cpp.h"
#include "../marty_ss.h"
#include "../marty_ns.h"
#include "../marty_enum.h"
#include "../marty_flags.h"



int main()
{

    std::cout
        << "#pragma once\n"
        << "\n"
        << "#include \"marty_cpp.h\"\n"
        << "#include \"marty_enum.h\"\n"
        << "#include \"marty_flags.h\"\n"
        << "\n";


    using namespace marty_cpp;


    auto ns = makeNamespaceOutputWriteGuard( std::cout, std::string("marty_cpp") );

    enum_generate_serialize( std::cout
                           , std::string( "invalid,unknown=-1; detect=0; lf; cr; lfcr; crlf;"
                                        )
                           , std::string(), std::string("    ")
                           , std::string("ELinefeedType"), std::string() // std::string("std::uint8_t")
                           , NameStyle::camelStyle // pascalStyle
                           , NameStyle::all        // serializedNameStyle all - mix of all styles while deserializing, serialization uses same style as C/C++ constants
                           , std::string("") // name prefix
                           , EnumGeneratorOptionFlags::generateDefAll // generateDefType | generateDefSerialize | generateDefDeserialize
                           //| EnumGeneratorOptionFlags::generateDefSerializeExtra
                           | EnumGeneratorOptionFlags::lowercaseDeserelialize
                           //| EnumGeneratorOptionFlags::enumFlags
                           //| EnumGeneratorOptionFlags::outputHex
                           );
    return 0;
}






