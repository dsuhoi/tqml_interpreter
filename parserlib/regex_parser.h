#ifndef __REGEX_PARSER_H__
#define __REGEX_PARSER_H__

#include <map>
#include "text_data.h"

// Class for parsing text data
class RegexParser {
private:
	// Regular expression for parsing file text
	static const char BLOCK_TEXT_REGEX[];
	static const char MAIN_TEXT_REGEX[];
	static const char HEADER_TEXT_REGEX[];
	static const char EXTRA_TEXT_REGEX[];
	static const char LINKS_TEXT_REGEX[];
	static const char LINK_REGEX[];
	static const char CARR_CHR_EQUAL[];
	// Private constructor
	RegexParser() {}
public:
	// Parsing the file text (Return an array with text parts) (false - OK, true - ERROR)
	static bool ParseFile(char *fileText, std::map<int, TextBlock*> &textParts);
	// Return the pointer to the text links from the text part
	static bool ParseLinks(const char *part, std::vector<TextLink*> &vectLinks);
	// Return the pointer to the main text
	static bool ParseText(const char *part, char **mainText, char **headerText, char **extraText);
};

#endif
