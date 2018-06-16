#include <fstream>
#include <ios>
#include <istream>
#include <streambuf>
#include <vector>

#include "GameEngine/Utility/debug.h"
#include "GameEngine/Utility/myon_parser.h"
#include "GameEngine/Utility/named_data.h"
#include "GameEngine/Utility/string.h"


namespace GE {

//TODO: update the implementation to support Unicode

TMyON_DataReader::TMyON_DataReader(
    std::istream& source,
    const TString& needle
) :
    source(source),
    needle(needle),
    parsedData(),
    ignored(default_ignored())
{}

bool TMyON_DataReader::parse() {
    if (seekDataStart() == false) {
        error = "Failed to find '" + needle + "'";
		return true;
	}

    parsedData.emplace("__name__", needle);

	std::vector<TString> keyStack;
	TString currentKey;
	TString currentValue;
    bool isInsideValue = false;
    int parenthesesSum = 0;

    while (source.good()) {
        char currentChr = source.get();
		if (error.empty() == false) { break; }

        if (ignored.find(currentChr) != ignored.npos) {
			continue;
		}

        switch (currentChr) {
		case sectionStart:
			{
                ++parenthesesSum;

				//add parsed categories too
                TString key = join(keyStack);
				if (keyStack.empty() == false) {
					key += keySeparator;
				}
				key += currentKey;
                parsedData.emplace(std::move(key), "");

				if (currentKey.empty() == false) {
                    keyStack.emplace_back(std::move(currentKey));
				}
                currentKey.clear();
                currentValue.clear();
                isInsideValue = false;
				break;
			}

		case sectionEnd:
			{
                --parenthesesSum;
                if (parenthesesSum < 0) {
                    error = "Wrong closing parenthesis at pos " +
                        std::to_string(source.tellg()) + ".";
                    break;
                }
                if ((parenthesesSum == 0) && (source.peek() != separator)) {
                    error = "Missing separator after closing parenthesis at pos " +
                        std::to_string(source.tellg()) + ".";
                    break;
                }

                if (isInsideValue) {
                    error = "Missing separator after value at pos " +
                        std::to_string(source.tellg()) + ".";
                    break;
                }

                if (keyStack.size() == 0) {
                    break;
                }

				keyStack.pop_back();
				break;
			}

		case separator:
            {
                if (currentKey.empty() && currentValue.empty()) { /* block end or ;;;; */
                    continue;
                }

                if (currentKey.empty() == true) {
                    error = "Empty key at pos " + std::to_string(source.tellg()) + ".";
					break;
				} else if (currentValue.empty() == true) {
                    error = "Empty value at pos " + std::to_string(source.tellg()) + ".";
					break;
				}

                TString key = join(keyStack);
				if (keyStack.empty() == false) {
                    key += keySeparator;
				}
				key += currentKey;
                parsedData.emplace(std::move(key), currentValue);
                currentKey.clear();
                currentValue.clear();
                isInsideValue = false;
				break;
			}

		case valueSign:
			{
				if (currentKey.empty() == true) {
                    error = "Empty key for value at pos " + std::to_string(source.tellg()) + ".";
					break;
				}

                currentValue.clear();
                isInsideValue = true;
				break;
			}

        default:
            {
                if (isInsideValue) {
                    currentValue += currentChr;
                } else {
                    currentKey += currentChr;
                }
				break;
			}
		}
	}

    if (parenthesesSum != 0) {
        if (error.empty() == true) {
            error = "Unexpected file end: closing parenthesis was not found.";
        }
    }

    return error.empty() == false;
}

const TString& TMyON_DataReader::getError() const {
	return error;
}

const TNamedData<TString>& TMyON_DataReader::getParsedData() const {
	return parsedData;
}

void TMyON_DataReader::setIgnoredSymbols(const TString& value) {
	ignored = value;
}

bool TMyON_DataReader::seekDataStart() {
    source.seekg(0);
	if (needle.empty() == true) {
		return true;
	}

    char* buffer = new char[needle.size() + 1];
    std::unique_ptr<char> bufferObj(buffer);

    while (source.good()) {
        std::streampos start = source.tellg();
        source.get(buffer, needle.size() + 1);

        if (strncmp(buffer, needle.c_str(), needle.size()) == 0) {
            source.seekg(start);
			return true;
		}
	}

	error = "substring started with '" + needle + "' was not found.";
	return false;

    UNUSED(bufferObj);
}


TString TMyON_DataReader::join(const std::vector<TString>& parts) {
    return String::join(parts, keySeparator);
}


TNamedData<TString> ParseData(std::istream& source) {
    TMyON_DataReader parser(source);
    ASSERT(parser.parse() == false,
        "Failed to parse source. Message is: " + parser.getError())
    return parser.getParsedData();
}

} // namespace GE