/*! \file
    \brief Генерация enum и сериализации для различных перечислений
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
                           , EnumGeneratorOptionFlags::enumClass
                           | EnumGeneratorOptionFlags::generateDefAll // generateDefType | generateDefSerialize | generateDefDeserialize
                           //| EnumGeneratorOptionFlags::generateDefSerializeExtra
                           | EnumGeneratorOptionFlags::lowercaseDeserialize
                           //| EnumGeneratorOptionFlags::enumFlags
                           //| EnumGeneratorOptionFlags::outputHex
                           );


    enum_generate_serialize( std::cout
                           , std::string( "invalid,unknown=-1;"
                                          "enumClass                                                  = marty_cpp::EnumGeneratorOptionFlags::enumClass;"
                                          "unsignedVals                                               = marty_cpp::EnumGeneratorOptionFlags::unsignedVals;"
                                          "umap,useUnorderedMap                                       = marty_cpp::EnumGeneratorOptionFlags::useUnorderedMap;"
                                          "singleName,singleDef                                       = marty_cpp::EnumGeneratorOptionFlags::singleDef;"
                                          "noExtraLinefeed,noxlf                                      = marty_cpp::EnumGeneratorOptionFlags::noExtraLinefeed;"
                                          "lowercase,lowercaseDeserialize                             = marty_cpp::EnumGeneratorOptionFlags::lowercaseDeserialize;"
                                          "integers,allowIntegers,integerDeserialize                  = marty_cpp::EnumGeneratorOptionFlags::integerDeserialize;"
                                          "flags,enumFlags                                            = marty_cpp::EnumGeneratorOptionFlags::enumFlags;"
                                          "noComments,disableComments                                 = marty_cpp::EnumGeneratorOptionFlags::disableComments;"
                                          "serialize,genSerialize,generateDefSerialize                = marty_cpp::EnumGeneratorOptionFlags::generateDefSerialize;"
                                          "deserialize,genDeserialize,generateDefDeserialize          = marty_cpp::EnumGeneratorOptionFlags::generateDefDeserialize;"
                                          "typeDecl,typeDeclaration,genTypeDecl,generateDefType       = marty_cpp::EnumGeneratorOptionFlags::generateDefType;"
                                          "serializeSet,genSerializeSet,generateDefSerializeSet       = marty_cpp::EnumGeneratorOptionFlags::generateDefSerializeSet;"
                                          "deserializeSet,genDeserializeSet,generateDefDeserializeSet = marty_cpp::EnumGeneratorOptionFlags::generateDefDeserializeSet;"
                                          "serializeBoth,genSerializeBoth,generateDefSerializeBoth    = marty_cpp::EnumGeneratorOptionFlags::generateDefSerializeBoth;"
                                          "all,allDefs,genAllDefs,generateDefAll                      = marty_cpp::EnumGeneratorOptionFlags::generateDefAll;"
                                          "extra,generateDefSerializeExtra                            = marty_cpp::EnumGeneratorOptionFlags::generateDefSerializeExtra;"
                                          "fmtAuto,formatAuto,outputAuto                              = marty_cpp::EnumGeneratorOptionFlags::outputAuto;"
                                          "fmtOct,formatOct,outputOct                                 = marty_cpp::EnumGeneratorOptionFlags::outputOct;"
                                          "fmtDec,formatDec,outputDec                                 = marty_cpp::EnumGeneratorOptionFlags::outputDec;"
                                          "fmtHex,formatHex,outputHex                                 = marty_cpp::EnumGeneratorOptionFlags::outputHex;"
                                          "sys,system,sysFirst,systemFirst                            = marty_cpp::EnumGeneratorOptionFlags::generateSysIncludesFirst;"
                                          //"noPe,noPrologEpilog,noHeaderFooter,disablePrologEpilog     = marty_cpp::EnumGeneratorOptionFlags::disablePrologEpilog;"
                                          //"=marty_cpp::EnumGeneratorOptionFlags::;"
                                        )
                           , std::string(), std::string("    ")
                           , std::string("EnumGeneratorOptionFlagsSerializable"), std::string("std::uint32_t") // std::string() // std::string("std::uint8_t")
                           , NameStyle::camelStyle // pascalStyle
                           , NameStyle::all        // serializedNameStyle all - mix of all styles while deserializing, serialization uses same style as C/C++ constants
                           , std::string("") // name prefix
                           , EnumGeneratorOptionFlags::enumClass
                           | EnumGeneratorOptionFlags::generateDefAll // generateDefType | generateDefSerialize | generateDefDeserialize
                           | EnumGeneratorOptionFlags::generateDefSerializeExtra // for set
                           | EnumGeneratorOptionFlags::lowercaseDeserialize
                           | EnumGeneratorOptionFlags::enumFlags
                           //| EnumGeneratorOptionFlags::outputHex
                           );


    return 0;
}


