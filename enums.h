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


enum class EnumGeneratorOptionFlagsSerializable : std::uint32_t
{
    Invalid                     = (std::uint32_t)(-1),
    Unknown                     = (std::uint32_t)(-1),
    EnumClass                   = marty_cpp::EnumGeneratorOptionFlags::EnumClass,
    Unsigned                    = marty_cpp::EnumGeneratorOptionFlags::UnsignedVals,
    UnsignedVals                = marty_cpp::EnumGeneratorOptionFlags::UnsignedVals,
    Umap                        = marty_cpp::EnumGeneratorOptionFlags::UseUnorderedMap,
    UseUnorderedMap             = marty_cpp::EnumGeneratorOptionFlags::UseUnorderedMap,
    SingleName                  = marty_cpp::EnumGeneratorOptionFlags::SingleDef,
    SingleDef                   = marty_cpp::EnumGeneratorOptionFlags::SingleDef,
    NoExtraLinefeed             = marty_cpp::EnumGeneratorOptionFlags::NoExtraLinefeed,
    Noxlf                       = marty_cpp::EnumGeneratorOptionFlags::NoExtraLinefeed,
    Lowercase                   = marty_cpp::EnumGeneratorOptionFlags::LowercaseDeserialize,
    LowercaseDeserialize        = marty_cpp::EnumGeneratorOptionFlags::LowercaseDeserialize,
    Integers                    = marty_cpp::EnumGeneratorOptionFlags::IntegerDeserialize,
    AllowIntegers               = marty_cpp::EnumGeneratorOptionFlags::IntegerDeserialize,
    IntegerDeserialize          = marty_cpp::EnumGeneratorOptionFlags::IntegerDeserialize,
    Flags                       = marty_cpp::EnumGeneratorOptionFlags::EnumFlags,
    EnumFlags                   = marty_cpp::EnumGeneratorOptionFlags::EnumFlags,
    NoComments                  = marty_cpp::EnumGeneratorOptionFlags::DisableComments,
    DisableComments             = marty_cpp::EnumGeneratorOptionFlags::DisableComments,
    Serialize                   = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerialize,
    GenSerialize                = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerialize,
    GenerateDefSerialize        = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerialize,
    Deserialize                 = marty_cpp::EnumGeneratorOptionFlags::GenerateDefDeserialize,
    GenDeserialize              = marty_cpp::EnumGeneratorOptionFlags::GenerateDefDeserialize,
    GenerateDefDeserialize      = marty_cpp::EnumGeneratorOptionFlags::GenerateDefDeserialize,
    TypeDecl                    = marty_cpp::EnumGeneratorOptionFlags::GenerateDefType,
    TypeDeclaration             = marty_cpp::EnumGeneratorOptionFlags::GenerateDefType,
    GenTypeDecl                 = marty_cpp::EnumGeneratorOptionFlags::GenerateDefType,
    GenerateDefType             = marty_cpp::EnumGeneratorOptionFlags::GenerateDefType,
    SerializeSet                = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeSet,
    GenSerializeSet             = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeSet,
    GenerateDefSerializeSet     = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeSet,
    DeserializeSet              = marty_cpp::EnumGeneratorOptionFlags::GenerateDefDeserializeSet,
    GenDeserializeSet           = marty_cpp::EnumGeneratorOptionFlags::GenerateDefDeserializeSet,
    GenerateDefDeserializeSet   = marty_cpp::EnumGeneratorOptionFlags::GenerateDefDeserializeSet,
    SerializeBoth               = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeBoth,
    GenSerializeBoth            = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeBoth,
    GenerateDefSerializeBoth    = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeBoth,
    All                         = marty_cpp::EnumGeneratorOptionFlags::GenerateDefAll,
    AllDefs                     = marty_cpp::EnumGeneratorOptionFlags::GenerateDefAll,
    GenAllDefs                  = marty_cpp::EnumGeneratorOptionFlags::GenerateDefAll,
    GenerateDefAll              = marty_cpp::EnumGeneratorOptionFlags::GenerateDefAll,
    Extra                       = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeExtra,
    GenerateDefSerializeExtra   = marty_cpp::EnumGeneratorOptionFlags::GenerateDefSerializeExtra,
    FmtAuto                     = marty_cpp::EnumGeneratorOptionFlags::OutputAuto,
    FormatAuto                  = marty_cpp::EnumGeneratorOptionFlags::OutputAuto,
    OutputAuto                  = marty_cpp::EnumGeneratorOptionFlags::OutputAuto,
    FmtOct                      = marty_cpp::EnumGeneratorOptionFlags::OutputOct,
    FormatOct                   = marty_cpp::EnumGeneratorOptionFlags::OutputOct,
    OutputOct                   = marty_cpp::EnumGeneratorOptionFlags::OutputOct,
    FmtDec                      = marty_cpp::EnumGeneratorOptionFlags::OutputDec,
    FormatDec                   = marty_cpp::EnumGeneratorOptionFlags::OutputDec,
    OutputDec                   = marty_cpp::EnumGeneratorOptionFlags::OutputDec,
    FmtHex                      = marty_cpp::EnumGeneratorOptionFlags::OutputHex,
    FormatHex                   = marty_cpp::EnumGeneratorOptionFlags::OutputHex,
    OutputHex                   = marty_cpp::EnumGeneratorOptionFlags::OutputHex,
    Sys                         = marty_cpp::EnumGeneratorOptionFlags::generateSysIncludesFirst,
    System                      = marty_cpp::EnumGeneratorOptionFlags::generateSysIncludesFirst,
    SysFirst                    = marty_cpp::EnumGeneratorOptionFlags::generateSysIncludesFirst,
    SystemFirst                 = marty_cpp::EnumGeneratorOptionFlags::generateSysIncludesFirst,
    NoPrologEpilog              = marty_cpp::EnumGeneratorOptionFlags::DisablePrologEpilog,
    NoHeaderFooter              = marty_cpp::EnumGeneratorOptionFlags::DisablePrologEpilog,
    DisablePrologEpilog         = marty_cpp::EnumGeneratorOptionFlags::DisablePrologEpilog

}; // enum class EnumGeneratorOptionFlagsSerializable : std::uint32_t

MARTY_CPP_MAKE_ENUM_FLAGS(EnumGeneratorOptionFlagsSerializable)

MARTY_CPP_ENUM_FLAGS_SERIALIZE_BEGIN( EnumGeneratorOptionFlagsSerializable, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::EnumClass , "EnumClass"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Invalid   , "Invalid"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Unsigned  , "Unsigned"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Lowercase , "Lowercase"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Umap      , "Umap"            );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "Integers"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoExtraLinefeed, "NoExtraLinefeed" );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "FmtOct"          );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "SingleName"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Flags     , "Flags"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "NoComments"      );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "Serialize"       );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "Deserialize"     );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "TypeDecl"        );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "SerializeSet"    );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "DeserializeSet"  );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "SerializeBoth"   );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "All"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Extra     , "Extra"           );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "FmtAuto"         );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "FmtDec"          );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "FmtHex"          );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "Sys"             );
    MARTY_CPP_ENUM_FLAGS_SERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "NoPrologEpilog"  );
MARTY_CPP_ENUM_FLAGS_SERIALIZE_END( EnumGeneratorOptionFlagsSerializable, std::map, 1 )

MARTY_CPP_ENUM_FLAGS_DESERIALIZE_BEGIN( EnumGeneratorOptionFlagsSerializable, std::map, 1 )
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::EnumClass , "enum-class"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::EnumClass , "enum_class"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::EnumClass , "enumclass"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Invalid   , "invalid"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Invalid   , "unknown"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Unsigned  , "unsigned"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Unsigned  , "unsigned-vals"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Unsigned  , "unsigned_vals"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Unsigned  , "unsignedvals"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Lowercase , "lowercase_deserialize"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Lowercase , "lowercase"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Lowercase , "lowercase-deserialize"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Lowercase , "lowercasedeserialize"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Umap      , "use-unordered-map"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Umap      , "use_unordered_map"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Umap      , "useunorderedmap"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Umap      , "umap"                         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "allow-integers"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "integers"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "allow_integers"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "integer_deserialize"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "allowintegers"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "integer-deserialize"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Integers  , "integerdeserialize"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoExtraLinefeed, "no-extra-linefeed"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoExtraLinefeed, "no_extra_linefeed"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoExtraLinefeed, "noextralinefeed"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoExtraLinefeed, "noxlf"                        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "format_oct"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "fmt-oct"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "format-oct"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "fmt_oct"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "fmtoct"                       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "formatoct"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "output-oct"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "output_oct"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtOct    , "outputoct"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "single-name"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "single_def"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "single_name"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "singlename"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "single-def"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SingleName, "singledef"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Flags     , "enum_flags"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Flags     , "flags"                        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Flags     , "enum-flags"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Flags     , "enumflags"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "no-comments"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "no_comments"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "disable-comments"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "nocomments"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "disable_comments"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoComments, "disablecomments"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "genserialize"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "serialize"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "gen-serialize"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "gen_serialize"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "generate-def-serialize"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "generate_def_serialize"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Serialize , "generatedefserialize"         );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "gendeserialize"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "deserialize"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "gen-deserialize"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "gen_deserialize"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "generate-def-deserialize"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "generate_def_deserialize"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Deserialize, "generatedefdeserialize"       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "type-declaration"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "type-decl"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "type_declaration"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "type_decl"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "typedecl"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "gen-type-decl"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "typedeclaration"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "gen_type_decl"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "gentypedecl"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "generate_def_type"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "generate-def-type"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::TypeDecl  , "generatedeftype"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "serialize-set"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "serialize_set"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "gen-serialize-set"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "gen_serialize_set"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "genserializeset"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "serializeset"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "generate-def-serialize-set"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "generate_def_serialize_set"   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeSet, "generatedefserializeset"      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "deserialize-set"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "deserialize_set"              );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "gendeserializeset"            );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "deserializeset"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "gen_deserialize_set"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "gen-deserialize-set"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "generate-def-deserialize-set" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "generate_def_deserialize_set" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::DeserializeSet, "generatedefdeserializeset"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "serialize-both"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "serialize_both"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "gen-serialize-both"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "gen_serialize_both"           );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "genserializeboth"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "serializeboth"                );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "generate-def-serialize-both"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "generate_def_serialize_both"  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::SerializeBoth, "generatedefserializeboth"     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "all"                          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "all-defs"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "all_defs"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "genalldefs"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "alldefs"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "gen-all-defs"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "generate_def_all"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "gen_all_defs"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "generate-def-all"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::All       , "generatedefall"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Extra     , "generatedefserializeextra"    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Extra     , "extra"                        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Extra     , "generate-def-serialize-extra" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Extra     , "generate_def_serialize_extra" );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "format_auto"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "fmt-auto"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "format-auto"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "fmt_auto"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "fmtauto"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "formatauto"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "output-auto"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "output_auto"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtAuto   , "outputauto"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "format_dec"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "fmt-dec"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "format-dec"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "fmt_dec"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "fmtdec"                       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "formatdec"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "output-dec"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "output_dec"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtDec    , "outputdec"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "format_hex"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "fmt-hex"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "format-hex"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "fmt_hex"                      );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "fmthex"                       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "formathex"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "output-hex"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "output_hex"                   );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::FmtHex    , "outputhex"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "sys"                          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "sysfirst"                     );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "system"                       );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "system_first"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "sys-first"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "system-first"                 );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "sys_first"                    );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::Sys       , "systemfirst"                  );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "no-prolog-epilog"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "noprologepilog"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "no_prolog_epilog"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "no-header-footer"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "no_header_footer"             );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "noheaderfooter"               );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "disableprologepilog"          );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "disable_prolog_epilog"        );
    MARTY_CPP_ENUM_FLAGS_DESERIALIZE_ITEM( EnumGeneratorOptionFlagsSerializable::NoPrologEpilog, "disable-prolog-epilog"        );
MARTY_CPP_ENUM_FLAGS_DESERIALIZE_END( EnumGeneratorOptionFlagsSerializable, std::map, 1 )

} // marty_cpp
