#ifndef __REGEX_PARSER_H__
#define __REGEX_PARSER_H__

#include <map>
#include <string>
#include <regex>

class Text_link;
class Text_block;

// Class for parsing text data
class Regex_parser
{
public:
    // Private constructor
    Regex_parser() = delete;
    // Parsing the file text (false - OK, true - ERROR)
    static bool parse_file(std::string file_text, std::map<int, Text_block>& text_parts);
    // Get the vector with text links from the text part (false - OK, true - ERROR)
    static bool parse_links(std::string part, std::vector<Text_link>& vect_links);
    // Get the pointers to the main, header and extra text (false - OK, true - ERROR)
    static bool parse_text(std::string part, std::string& main_text, std::string& header_text, std::string& extra_text);
private:
    // Regular expression for parsing file text
    static inline const char BLOCK_TEXT_REGEX[] = "<text\\[([0-9]{1,3})\\]>([\\S\\s]*?)</text>";
    static inline const char MAIN_TEXT_REGEX[] = "<main>([\\S\\s]*?)</main>";
    static inline const char HEADER_TEXT_REGEX[] = "<header>(.*?)</header>";
    static inline const char EXTRA_TEXT_REGEX[] = "<info>([\\S\\s]*?)</info>";
    static inline const char LINKS_TEXT_REGEX[] = "<links>([\\S\\s]*)</links>";
    static inline const char LINK_REGEX[] = "<&\\((\\S*)\\)\\[([0-9]{1,3})\\]\\s*\\=\\s*\"(.*?)\"\\s*>";
    static inline const char CARR_CHR_EQUAL[] = "<n>";
    static inline const char TAB_CHR_EQUAL[] = "<t>";
};

#endif
