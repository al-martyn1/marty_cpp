#pragma once

#include "marty_cpp.h"

#include <unordered_map>
#include <exception>
#include <stdexcept>

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace marty_cpp {



//----------------------------------------------------------------------------
enum class SourceLineType
{
    genericLine,  // 0
    emptyLine  ,  // 1
    includeLine,  // 2
    sortOn     ,  // 3
    sortOff       // 4

};

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
namespace sort_includes_utils {

//------------------------------
// В случае совпадения возвращает длину искомой строки, или 0, если не совпало (частичное совпадение также вернёт 0)
template <typename IteratorType> inline
std::size_t startsWith(IteratorType b, IteratorType e, const char *pCmpWith)
{
    std::size_t idx = 0;
    while(pCmpWith[idx]!=0 && b!=e && pCmpWith[idx]==*b)
    {
        ++b;
        ++idx;
    }

    if (pCmpWith[idx]==0) // дошли до конца искомой строки
    {
        return idx;
    }

    return 0;
}

//------------------------------
template <typename IteratorType, typename VectorIteratorType> inline
std::size_t startsWithOneOf(IteratorType b, IteratorType e, VectorIteratorType bValsCmpWith, VectorIteratorType eValsCmpWith)
{
    for(; bValsCmpWith!=eValsCmpWith; ++bValsCmpWith)
    {
        std::size_t len = startsWith(b, e, bValsCmpWith->c_str());
        if (len)
            return len;
    }

    return 0;
}

//------------------------------
template <typename IteratorType> inline
IteratorType eatSpaces(IteratorType b, IteratorType e)
{
    while(b!=e && (*b==' ' || *b=='\t')) ++b;
    return b;
}

//------------------------------
inline
std::string normalizeIncludeName(std::string name)
{
    for(std::string::iterator it=name.begin(); it!=name.end(); ++it)
    {
        if (*it=='\\')
            *it = '/';
    }
    return name;
}

//------------------------------
inline
std::string getIncludeNamePath(const std::string &name)
{
     auto sepPos = name.find_last_of('/' /* , name.size() */ );
     if (sepPos==name.npos)
         return std::string();
     return std::string(name,0,sepPos);
}

//------------------------------
} // namespace sort_includes_utils

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------
template <typename IteratorType> inline
SourceLineType parseSourceLineForIncludes(IteratorType b, IteratorType e, std::string *pFoundName = 0)
{
    b = sort_includes_utils::eatSpaces(b, e);
    if (b==e)
        return SourceLineType::emptyLine;

    static std::vector<std::string> nosortMarkers = { "//#-sort", "/*#-sort", "//#nosort", "/*#nosort"};
    static std::vector<std::string>   sortMarkers = { "//#+sort", "/*#+sort", "//#sort"  , "/*#sort"  };

    std::size_t 
    prefixLen = sort_includes_utils::startsWithOneOf(b, e, sortMarkers.begin(), sortMarkers.end());
    // sort_includes_utils::startsWith(b, e, "/*#sort");
    // if (!prefixLen)
    //    prefixLen = sort_includes_utils::startsWith(b, e, "//#sort");
    if (prefixLen)
        return SourceLineType::sortOn;

    prefixLen = sort_includes_utils::startsWithOneOf(b, e, nosortMarkers.begin(), nosortMarkers.end());
    // prefixLen = sort_includes_utils::startsWith(b, e, "/*#nosort");
    // if (!prefixLen)
    //    prefixLen = sort_includes_utils::startsWith(b, e, "//#nosort");
    if (prefixLen)
        return SourceLineType::sortOff;

    if (*b!='#')
        return SourceLineType::genericLine;

    ++b;
    if (b==e)
        return SourceLineType::genericLine;

    // Поддержка пробелов между # и include
    b = sort_includes_utils::eatSpaces(b, e);
    if (b==e)
        return SourceLineType::genericLine;

    prefixLen = sort_includes_utils::startsWith(b, e, "include");
    if (!prefixLen)
        return SourceLineType::genericLine;

    b += prefixLen;
    if (b==e)
        return SourceLineType::genericLine;

    b = sort_includes_utils::eatSpaces(b, e);
    if (b==e)
        return SourceLineType::genericLine;

    if (*b!='\"' && *b!='<')
        return SourceLineType::genericLine;

    if (pFoundName)
    {
        std::string tmpName = std::string(b, e);
        *pFoundName = simple_rtrim(tmpName, [](char ch) {return ch==' ' || ch=='\t' || ch=='\r' || ch=='\n';} );
    }
    
    return SourceLineType::includeLine;

}

//----------------------------------------------------------------------------
inline
SourceLineType parseSourceLineForIncludes(const std::string &str, std::string *pFoundName = 0)
{
    return parseSourceLineForIncludes(str.begin(), str.end(), pFoundName);
}

//----------------------------------------------------------------------------
inline
std::vector<SourceLineType> parseSourceLinesForIncludes(const std::vector<std::string> &lines, std::unordered_map<std::size_t, std::string> *pNamesByLine = 0)
{
    auto addNameByLine = [&](std::size_t n, const std::string &name)
    {
        if (!pNamesByLine)
            return;

        (*pNamesByLine)[n] = name;
    };

    std::vector<SourceLineType> resSlt; resSlt.reserve(lines.size());

    for(std::size_t n=0; n!=lines.size(); ++n)
    {
        std::string name;
        SourceLineType slt = parseSourceLineForIncludes(lines[n], &name);
        if (slt==SourceLineType::includeLine)
            addNameByLine(n,name);
        resSlt.emplace_back(slt);
    }

    return resSlt;
}

//----------------------------------------------------------------------------




//----------------------------------------------------------------------------
struct SortIncludeBlockInfo
{
    std::size_t      idxBegin;
    std::size_t      idxEnd  ;
    bool             bSort   ;
};

//----------------------------------------------------------------------------
inline
std::vector<unsigned char> findSortIncludeMarkers(const std::vector<SourceLineType> &vecSlt)
{
    std::vector<unsigned char> sortFlags; sortFlags.reserve(vecSlt.size());

    auto backTraceEmptyLines = [&](std::size_t n)
    {
        //std::size_t i = n;
        while(n!=0)
        {
            --n;

            if (sortFlags[n]==0)
                break;

            if (vecSlt[n]==SourceLineType::emptyLine)
            {
                sortFlags[n] = 0;
                continue;
            }

            break;
        }
    };


    int sortLevel = 1; // default is sort

    bool prevInclude = false;

    for(std::size_t n=0; n!=vecSlt.size(); ++n)
    {
        switch(vecSlt[n])
        {
            case SourceLineType::sortOn:
                ++sortLevel;
                sortFlags.emplace_back(0); // do not sort current line with sort mode ctrl
                backTraceEmptyLines(n);
                prevInclude = false;
                break;

            case SourceLineType::sortOff:
                --sortLevel;
                sortFlags.emplace_back(0); // do not sort current line with sort mode ctrl
                backTraceEmptyLines(n);
                prevInclude = false;
                break;

            case SourceLineType::genericLine:
                sortFlags.emplace_back(0); // do not sort generic lines
                backTraceEmptyLines(n);
                prevInclude = false;
                break;

            case SourceLineType::emptyLine:
                if (prevInclude)
                {
                    sortFlags.emplace_back(sortLevel>0 ? 1 : 0);
                }
                else
                {
                    sortFlags.emplace_back(0);
                }
                break;

            case SourceLineType::includeLine:
                sortFlags.emplace_back(sortLevel>0 ? 1 : 0);
                prevInclude = true;
                break;

            default:
                throw std::runtime_error("marty_cpp::findSortIncludeBlocks: default hits");

        } // switch

    } // for

    return sortFlags;

}

//----------------------------------------------------------------------------
struct SortIncludeOptions
{
    std::size_t sysIncludesFirst  = false;
    std::size_t sepGroupLines     = 1;
    std::size_t sepBlockLines     = 1; // 2;
};

//----------------------------------------------------------------------------
inline
std::vector<std::string> sortIncludes( const std::vector<std::string>    &lines
                                     , const std::vector<unsigned char>  &sortMarkers
                                     , const std::vector<SourceLineType> &vecSlt
                                     , const std::unordered_map<std::size_t, std::string> &namesByLine
                                     , const SortIncludeOptions          &sortOptions = SortIncludeOptions()
                                     )
{
    if (lines.size()!=sortMarkers.size() || lines.size()!=vecSlt.size())
    {
        throw std::runtime_error("marty_cpp::sortIncludes: size mismatch");
    }

    std::vector<std::string> resLines; resLines.reserve(lines.size());

    auto skipNonSort = [&](std::size_t n)
    {
        while(n!=sortMarkers.size() && sortMarkers[n]==0)
        {
            resLines.emplace_back(lines[n]);
            ++n;
        }
        return n;
    };

    auto formatIncludes = [&](const std::map<std::string, std::size_t> &includesMap)
    {
        bool firstGroup = true;
        std::string curGroup;

        std::map<std::string, std::size_t>::const_iterator it = includesMap.begin();
        for(; it!=includesMap.end(); ++it)
        {
            if (it->second>=lines.size())
                continue;

            std::string grpName = sort_includes_utils::getIncludeNamePath(it->first);
            if (curGroup!=grpName)
            {
                curGroup = grpName;
                if (!firstGroup)
                {
                    resLines.insert(resLines.end(), sortOptions.sepGroupLines, std::string());
                }
                firstGroup = false;
            }

            resLines.emplace_back(lines[it->second]);
        }
    };


    for( std::size_t n=skipNonSort(0)
       ; n!=sortMarkers.size()
       ; n=skipNonSort(n)
       )
    {
        std::map<std::string, std::size_t>    sysIncludesMap;
        std::map<std::string, std::size_t>    userIncludesMap;
        std::set<std::string>                 processedIncludes;

        for(; n!=sortMarkers.size() && sortMarkers[n]!=0; ++n )
        {
            if (vecSlt[n]!=SourceLineType::includeLine)
                continue;

            std::unordered_map<std::size_t, std::string>::const_iterator nblIt = namesByLine.find(n);
            if (nblIt==namesByLine.end())
                continue;

            std::string fileName = nblIt->second;

            bool sysInclude = unquote(fileName, '<', '>');
            if (!sysInclude)
                unquote(fileName, '\"', '\"');

            if (fileName.empty())
                continue;

            fileName = sort_includes_utils::normalizeIncludeName(fileName);

            if (processedIncludes.find(fileName)!=processedIncludes.end())
                continue;
           
            processedIncludes.insert(fileName);

            if (sysInclude)
                sysIncludesMap[fileName]  = n;
            else
                userIncludesMap[fileName] = n;

        } // for

        if (sysIncludesMap.empty() && userIncludesMap.empty())
            continue;

        if (sortOptions.sysIncludesFirst)
        {
            formatIncludes(sysIncludesMap);
            if (!sysIncludesMap.empty() && !userIncludesMap.empty())
                resLines.insert(resLines.end(), sortOptions.sepBlockLines, std::string());
            formatIncludes(userIncludesMap);
        }
        else
        {
            formatIncludes(userIncludesMap);
            if (!sysIncludesMap.empty() && !userIncludesMap.empty())
                resLines.insert(resLines.end(), sortOptions.sepBlockLines, std::string());
            formatIncludes(sysIncludesMap);
        }
    
    } // for

    return resLines;
}

//----------------------------------------------------------------------------
inline
std::vector<std::string> sortIncludes( const std::vector<std::string>    &lines
                                     , const SortIncludeOptions          &sortOptions = SortIncludeOptions()
                                     )
{
    std::unordered_map<std::size_t, std::string> incNames;
    std::vector<SourceLineType> vecSlt  = parseSourceLinesForIncludes(lines, &incNames);
    std::vector<unsigned char>  markers = findSortIncludeMarkers(vecSlt);
    return sortIncludes(lines, markers, vecSlt, incNames, sortOptions);
}

//----------------------------------------------------------------------------



//----------------------------------------------------------------------------

} // namespace marty_cpp
