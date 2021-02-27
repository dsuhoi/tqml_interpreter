#ifndef __REGEX_PARSER_H__
#define __REGEX_PARSER_H__

#include <map>
#include "text_data.h"

// Class for parsing text data
class Regex_parser
{
private:
    // Regular expression for parsing file text
    static const char BLOCK_TEXT_REGEX[];
    static const char MAIN_TEXT_REGEX[];
    static const char HEADER_TEXT_REGEX[];
    static const char EXTRA_TEXT_REGEX[];
    static const char LINKS_TEXT_REGEX[];
    static const char LINK_REGEX[];
    static const char CARR_CHR_EQUAL[];
    static const char TAB_CHR_EQUAL[];
    // Private constructor
    Regex_parser() = delete;
public:
    // Parsing the file text (false - OK, true - ERROR)
    static bool parse_file(char *file_text, std::map<int, Text_block*> &text_parts);
    // Get the vector with text links from the text part (false - OK, true - ERROR)
    static bool parse_links(const char *part, std::vector<Text_link*> &vect_links);
    // Get the pointers to the main, header and extra text (false - OK, true - ERROR)
    static bool parse_text(const char *part, char **main_text, char **header_text, char **extra_text);
};

#endif
