/*! \file
    \brief Тестирование генератора enum'ов marty_cpp::enum_generate_*
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <queue>
#include <deque>
#include <vector>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <random>
#include <cstdlib>
#include <exception>
#include <stdexcept>

#include "../../marty_cpp/marty_cpp.h"
#include "../../marty_cpp/marty_enum.h"
#include "../../marty_cpp/marty_ns.h"

#include "enum_gen_cpp_templates_txt.c"


int main( int argc, char* argv[] )
{
    auto tplParseRes = marty_cpp::EnumGeneratorTemplate<std::string>::parseTemplateOptionsText
        ( std::string(&enum_gen_cpp_templates_txt[0], enum_gen_cpp_templates_txt_size)
        , std::cerr
        , false /* ignoreUnknownParams */
        , false /* logGccFormat */
        , enum_gen_cpp_templates_txt_filename /* fileName */
        );

    if (std::get<0>(tplParseRes)==false)
    {
        std::cerr << "Exiting\n";
    }

    auto genTpl = std::get<1>(tplParseRes);

    marty_cpp::enum_generate_prolog(std::cout, genTpl);
    marty_cpp::enum_generate_includes(std::cout, marty_cpp::EnumGeneratorOptionFlags::generateDefAll | marty_cpp::EnumGeneratorOptionFlags::generateDefSerializeExtra, genTpl);


    using namespace marty_cpp;


    auto ns = makeNamespaceOutputWriteGuard( std::cout, std::string("") );


    enum_generate_serialize( std::cout
                           , std::string( "Invalid,Unknown=-1 // Unknown; Txt=0; Src=0x01; Other=0x02; 42=42 //42;"
                                        )
                           , std::string(), std::string("    ")
                           , std::string("ETextTrainingMode"), std::string("std::uint8_t")
                           , NameStyle::pascalStyle
                           , NameStyle::all
                           , std::string("") // name prefix
                           , EnumGeneratorOptionFlags::generateDefAll
                           | EnumGeneratorOptionFlags::generateDefSerializeExtra
                           | EnumGeneratorOptionFlags::lowercaseDeserialize
                           | EnumGeneratorOptionFlags::enumClass
                           | EnumGeneratorOptionFlags::unsignedVals
                           | EnumGeneratorOptionFlags::integerDeserialize
                           | EnumGeneratorOptionFlags::outputHex
                           // | EnumGeneratorOptionFlags::disableComments
                           );

    return 0;
}



