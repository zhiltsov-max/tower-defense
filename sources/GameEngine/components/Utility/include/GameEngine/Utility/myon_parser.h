#ifndef GAME_ENGINE_MYON_PARSER_H
#define GAME_ENGINE_MYON_PARSER_H

#include <istream>
#include <vector>

#include "GameEngine/Utility/string.h"
#include "GameEngine/Utility/named_data.h"


namespace GE {

class TMyonParser {
public:
    TMyonParser(std::istream& source, const TTextString& needle = "");

	/*
     * Returns false if no error occured, otherwise returns true.
     * If an error occured, it can be acquired by calling 'error' function.
	 */
	bool parse(); // TODO: change interface

    const TTextString& getError() const;

    const TNamedData<TTextString>& getParsedData() const;

	void setIgnoredSymbols(const TTextString& value = default_ignored());

private:
    static constexpr char sectionStart = '{';
    static constexpr char sectionEnd = '}';
    static constexpr char separator = ';';
    static constexpr char valueSign = ':';
    static constexpr char keySeparator = ':';
    static constexpr const char* default_ignored() { return " \t\r\n"; }

    std::istream& source;

	TTextString needle;
	TTextString error;

    TNamedData<TTextString> parsedData;
	TTextString ignored;


	bool seekDataStart();
    TString join(const std::vector<TString>& parts);
};

/*
 * Parses source and returns resulting TNamedData
 */
TNamedData<TTextString> ParseData(std::istream& source);

} // namespace GE

#endif //GAME_ENGINE_MYON_PARSER_H
