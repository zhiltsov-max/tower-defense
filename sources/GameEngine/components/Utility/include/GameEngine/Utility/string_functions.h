#ifndef GAME_ENGINE_STRING_FUNCTIONS_H
#define GAME_ENGINE_STRING_FUNCTIONS_H

#include <cmath>
#include <cstring>
#include <locale>
#include <string>
#include <vector>

#include "GameEngine/Infrastructure/string.h"

// TODO: update the implementation to accept Unicode

namespace GE {

namespace String {

// Split
template< class CharT >
std::vector< basic_string<CharT> >
split(const CharT* str, const CharT separator);

template< class CharT >
std::vector< basic_string<CharT> >
split(const CharT* str, const CharT* separator);

template< class CharT >
std::vector< basic_string<CharT> >
split(const CharT* str, const basic_string<CharT>& separator);


template< class CharT >
std::vector< basic_string<CharT> >
split(const basic_string<CharT>& str, const CharT separator);

template< class CharT >
std::vector< basic_string<CharT> >
split(const basic_string<CharT>& str, const CharT* separator);

template< class CharT >
std::vector< basic_string<CharT> >
split(const basic_string<CharT>& str, const basic_string<CharT>& separator);


template< class CharT >
std::vector< basic_string<CharT> >
splitByLength(const CharT* str, size_t partSize);

template< class CharT >
std::vector< basic_string<CharT> >
splitByLength(const basic_string<CharT>& str, size_t partSize);


// Join
template< class CharT >
basic_string<CharT>
join(const std::vector< basic_string<CharT> >& parts, CharT glue);

template< class CharT >
basic_string<CharT>
join(
    const std::vector< basic_string<CharT> >& parts,
    const basic_string<CharT>& glue = basic_string<CharT>()
);


// Starts with
template< class CharT >
bool startsWith(const CharT* str, const CharT* prefix);

template< class CharT >
bool startsWith(const CharT* str, const basic_string<CharT>& prefix);

template< class CharT >
bool startsWith(const basic_string<CharT>& str, const CharT* prefix);

template< class CharT >
bool startsWith(const basic_string<CharT>& str, const basic_string<CharT>& prefix);

// Ends with
template< class CharT >
bool endsWith(const basic_string<CharT>& str, const basic_string<CharT>& ending);

// Right
template< class CharT >
basic_string<CharT> right(const basic_string<CharT>& str, size_t firstPos);

// Left
template< class CharT >
basic_string<CharT> left(const basic_string<CharT>& str, size_t lastPos);

// To lower
template< class CharT >
basic_string<CharT> toLower(
    const basic_string<CharT>& str,
    const std::locale& locale = std::locale()
);

template< class CharT >
basic_string<CharT> toLower(
    const CharT* str,
    const std::locale& locale = std::locale()
);

// To Upper
template< class CharT >
basic_string<CharT> toUpper(
    const basic_string<CharT>& str,
    const std::locale& locale = std::locale()
);

template< class CharT >
basic_string<CharT> toUpper(
    const CharT* str,
    const std::locale& locale = std::locale()
);

} // namespace String


// ### Implementation ###

template< class CharT >
struct STRING_END;

template<> struct STRING_END<char> {
    static constexpr char value = '\0';
};
template<> struct STRING_END<wchar_t> {
    static constexpr wchar_t value = L'\0';
};

template< class CharT >
std::vector< basic_string<CharT> >
String::split(const CharT* str, const CharT separator) {
    std::vector<basic_string<CharT>> res;

    CharT const* start = str;
    CharT const* c = str;

    for(; (*c) != STRING_END<CharT>::value; ++c) {
        if (*c == separator) {
            res.emplace_back(start, c - start);
            start = c + 1;
        }
    }

    res.emplace_back(start, c - start);

    return res;
}

template< class CharT >
std::vector< basic_string<CharT> >
String::split(const CharT* str, const CharT* separator) {
    std::vector<basic_string<CharT>> res;

    CharT const* start = str;
    CharT const* sep = separator;
    CharT const* c = str;

    for(; (*c) != STRING_END<CharT>::value; ++c) {
        if (*c == *sep) {
            ++sep;
            if (*sep == STRING_END<CharT>::value) {
                res.emplace_back(start, (c - start) - (sep - separator) + 1);
                start = c + 1;
                sep = separator;
            }
        }
    }

    res.emplace_back(start, c - start);
    return res;

}

template< class CharT >
std::vector<basic_string<CharT>>
String::split(const CharT* str, const basic_string<CharT>& separator) {
    return String::split(str, separator.c_str());
}


template< class CharT >
std::vector<basic_string<CharT>>
String::split(const basic_string<CharT>& str, const CharT separator) {
    return String::split(str.c_str(), separator);
}

template< class CharT >
std::vector<basic_string<CharT>>
String::split(const basic_string<CharT>& str, const CharT* separator) {
    return String::split(str.c_str(), separator);
}

template< class CharT >
std::vector<basic_string<CharT>>
String::split(const basic_string<CharT>& str,
    const basic_string<CharT>& separator
) {
    return String::split(str.c_str(), separator.c_str());
}


template< class CharT >
std::vector< basic_string<CharT> >
String::splitByLength(const CharT* str_raw, size_t partSize) {
    return String::split(basic_string<CharT>(str_raw), partSize);
}

template< class CharT >
std::vector< basic_string<CharT> >
String::splitByLength(const basic_string<CharT>& str, size_t partSize) {
    size_t count = (size_t) std::ceil(double(str.size()) / partSize);
    std::vector<basic_string<CharT>> res;
    res.reserve(count);

    size_t pos = 0;
    for (size_t part = 0; part < count; ++part) {
        size_t newPos = std::min(str.size(), pos + partSize);
        res.emplace_back(str.substr(pos, newPos - pos));
        pos = newPos;
    }

    return res;
}


template< class CharT >
basic_string<CharT>
String::join(const std::vector< basic_string<CharT> >& parts, CharT glue) {
    return String::join(parts, basic_string<CharT>{glue});
}

template< class CharT >
basic_string<CharT>
String::join(const std::vector< basic_string<CharT> >& parts,
    const basic_string<CharT>& glue
) {
    basic_string<CharT> res;
    for(auto it = parts.cbegin(); it != parts.cend();) {
        res += *it;
        if ((*it).empty() == false) {
            ++it;
            if (it != parts.cend()) {
                res += glue;
            }
        } else {
            ++it;
        }
    }
    return res;
}


template< class CharT >
bool String::startsWith(const CharT* str, const CharT* begin) {
    while ( (*str != STRING_END<CharT>::value) &&
        (*begin != STRING_END<CharT>::value) &&
        (*str == *begin) )
    {
        ++str;
        ++begin;
    }
    return (*begin == STRING_END<CharT>::value);
}

template< class CharT >
bool String::startsWith(const CharT* str, const basic_string<CharT>& begin) {
    return String::startsWith(str, begin.c_str());
}


template< class CharT >
bool String::startsWith(const basic_string<CharT>& str, const CharT* begin) {
    return String::startsWith(str.c_str(), begin);
}

template< class CharT >
bool String::startsWith(const basic_string<CharT>& str,
    const basic_string<CharT>& begin
) {
    return String::startsWith(str.c_str(), begin.c_str());
}


template< class CharT >
bool String::endsWith(const basic_string<CharT>& str,
    const basic_string<CharT>& end
) {
    if (str.size() < end.size()) {
        return false;
    }
    return end.compare(str.substr(str.size() - end.size(), end.size())) == 0;
}


template< class CharT >
basic_string<CharT> String::right(const basic_string<CharT>& str,
    size_t firstPos
) {
    return str.substr(std::min(firstPos, str.size()));
}

template< class CharT >
basic_string<CharT> String::left(const basic_string<CharT>& str,
    size_t lastPos
) {
    return str.substr(0, std::min(lastPos, str.size()));
}


template< class CharT >
basic_string<CharT>String::toLower(const basic_string<CharT>& str,
    const std::locale& locale
) {
    basic_string<CharT> res;
    res.reserve(str.size());

    const CharT* c = str.c_str();
    while (*c != STRING_END<CharT>::value) {
        auto symbol = std::tolower(*c, locale);
        if (symbol != STRING_END<CharT>::value) {
            res.push_back(symbol);
        }
        ++c;
    }

    return res;
}

template< class CharT >
basic_string<CharT> String::toLower(const CharT* str,
    const std::locale& locale
) {
    basic_string<CharT> res;

    while (*str != STRING_END<CharT>::value) {
        auto symbol = std::tolower(*str, locale);
        if (symbol != STRING_END<CharT>::value) {
            res.push_back(symbol);
        }
        ++str;
    }

    return res;
}

template< class CharT >
basic_string<CharT> String::toUpper(const basic_string<CharT>& str,
    const std::locale& locale
) {
    basic_string<CharT> res;
    res.reserve(str.size());

    const CharT* c = str.c_str();
    while (*c != STRING_END<CharT>::value) {
        auto symbol = std::toupper(*c, locale);
        if (symbol != STRING_END<CharT>::value) {
            res.emplace_back(symbol);
        }
        ++c;
    }

    return res;
}

template< class CharT >
basic_string<CharT> String::toUpper(const CharT* str,
    const std::locale& locale
) {
    basic_string<CharT> res;

    while (*str != STRING_END<CharT>::value) {
        auto symbol = std::toupper(*str, locale);
        if (symbol != STRING_END<CharT>::value) {
            res.emplace_back(symbol);
        }
        ++str;
    }

    return res;
}

} // namespace GE

#endif // GAME_ENGINE_STRING_FUNCTIONS_H
