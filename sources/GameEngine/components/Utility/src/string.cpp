#include "string.h"



wstring String::toWide(const char* str) {
    wstring res;
    res.reserve(20); //magic size of preallocation
    while (*str != STRING_END<char>::value) {
        res.push_back(std::btowc(*str));
        ++str;
    }
    return res;
}

wstring String::toWide(const string& str) {
    return String::toWide(str.c_str());
}


wstring String::toWide(const wchar_t* str) {
    return wstring{str};
}

wstring String::toWide(const wstring& str) {
    return str;
}
