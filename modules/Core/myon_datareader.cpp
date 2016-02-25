#include "myon_datareader.h"

#include <fstream>
#include <streambuf>
#include "defs.h"


TMyON_DataReader::TMyON_DataReader(
    std::istream& source,
    const string& needle
) :
    source(source),
    needle(needle),
    parsedData(),
    ignored(default_ignored())
{}
	
TMyON_DataReader::~TMyON_DataReader() {}


bool TMyON_DataReader::parse() {
    if (seekDataStart() == false) {
        error = "Failed to find '" + needle + "'";
		return true;
	}

    parsedData.emplace("__name__", needle);

	std::vector<string> keyStack;		
	string currentKey;
	string currentValue;
    bool insideValue = false;
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
                string key = std::move(join(keyStack));
				if (keyStack.empty() == false) {
					key += keySeparator;
				}
				key += currentKey;
                parsedData.emplace(key, "");
					
				if (currentKey.empty() == false) {
                    keyStack.emplace_back(currentKey);
				}
                currentKey.clear();
                currentValue.clear();
                insideValue = false;
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

                if (insideValue) {
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
				
                string key = std::move(join(keyStack));
				if (keyStack.empty() == false) {
					key += keySeparator;
				}
				key += currentKey;
                parsedData.emplace(key, currentValue);
                currentKey.clear();
                currentValue.clear();
                insideValue = false;
				break;
			}
					
		case valueSign:
			{
				if (currentKey.empty() == true) {
                    error = "Empty key for value at pos " + std::to_string(source.tellg()) + ".";
					break;
				}

                currentValue.clear();
                insideValue = true;
				break;
			}
					
        default:
            {
                if (insideValue) {
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
	
const string& TMyON_DataReader::getError() const {
	return error;
}
	
const TNamedData<string>& TMyON_DataReader::getParsedData() const {
	return parsedData;
}
	
void TMyON_DataReader::setIgnoredSymbols(const string& value) {
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
    UNUSED(bufferObj)
}


string TMyON_DataReader::join(const std::vector<string>& parts) {
    return String::join(parts, keySeparator);
}


TNamedData<string> ParseData(std::istream& source) {
    TMyON_DataReader parser(source);
    ASSERT(parser.parse() == false,
        "Failed to parse source. Message is: " + parser.getError())
    return parser.getParsedData();
}
