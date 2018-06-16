#ifndef GAME_ENGINE_MYON_PARSER_H
#define GAME_ENGINE_MYON_PARSER_H

#include <istream>
#include <vector>

#include "GameEngine/Infrastructure/string.h"
#include "GameEngine/Utility/named_data.h"


namespace GE {

class TMyonParser {
public:
    TMyonParser(std::istream& source, const TString& needle = "");

	/*
     * Returns false if no error occured, otherwise returns true.
     * If an error occured, it can be acquired by calling 'error' function.
	 */
	bool parse(); // TODO: change interface

    const TString& getError() const;

    const TNamedData<TString>& getParsedData() const;

	void setIgnoredSymbols(const std::vector<TString>& value = default_ignored());

private:
    static constexpr char sectionStart = '{';
    static constexpr char sectionEnd = '}';
    static constexpr char separator = ';';
    static constexpr char valueSign = ':';
    static constexpr char keySeparator = ':';
    static constexpr std::initializer_list<TString> default_ignored() {
        return {' ', '\t', '\r', '\n'};
    }

    std::istream& source;

	TString needle;
	TString error;

    TNamedData<TString> parsedData;
	TString ignored;


	bool seekDataStart();
    TString join(const std::vector<TString>& parts);
};

/*
 * Parses source and returns resulting TNamedData
 */
TNamedData<TString> ParseData(std::istream& source);

} // namespace GE

#endif //GAME_ENGINE_MYON_PARSER_H
