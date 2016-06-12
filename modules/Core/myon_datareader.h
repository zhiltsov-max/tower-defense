#ifndef MYON_DATAREADER_H
#define MYON_DATAREADER_H

#include <istream>
#include <vector>

#include "string.h"
#include "nameddata.h"


class TMyON_DataReader
{
public:
    TMyON_DataReader(std::istream& source, const string& needle = "");
    TMyON_DataReader(const TMyON_DataReader& other) = delete;
    TMyON_DataReader& operator=(const TMyON_DataReader& other) = delete;
    TMyON_DataReader& operator=(TMyON_DataReader&& prot) = delete;
    TMyON_DataReader(TMyON_DataReader&& prot) = delete;
	~TMyON_DataReader();

	/*
    Returns false if no error occured, otherwise returns true.
    If an error occured, it can be acquired by calling 'error' function.
	*/
	bool parse();
	
    const string& getError() const;

    const TNamedData<string>& getParsedData() const;

	void setIgnoredSymbols(const string& value = default_ignored());
private:
    static constexpr char sectionStart = '{';
    static constexpr char sectionEnd = '}';
    static constexpr char separator = ';';
    static constexpr char valueSign = ':';
    static constexpr char keySeparator = ':';
    static constexpr const char* default_ignored() { return " \t\r\n"; }
	
    std::istream& source;

	string needle;
	string error;

    TNamedData<string> parsedData;
	string ignored;
	

	bool seekDataStart();
    string join(const std::vector<string>& parts);
};

/*
Parses source and returns resulting TNamedData
*/
TNamedData<string> ParseData(std::istream& source);


#endif //MYON_DATAREADER_H
