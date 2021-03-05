#include <string>
#include <regex>
#include "regex_parser.hpp"


// Regular expression for parsing file text
const char Regex_parser::BLOCK_TEXT_REGEX[] = "<text\\[([0-9]{1,3})\\]>([\\S\\s]*?)</text>";
const char Regex_parser::MAIN_TEXT_REGEX[] = "<main>([\\S\\s]*?)</main>";
const char Regex_parser::HEADER_TEXT_REGEX[] = "<header>(.*?)</header>";
const char Regex_parser::EXTRA_TEXT_REGEX[] = "<info>([\\S\\s]*?)</info>";
const char Regex_parser::LINKS_TEXT_REGEX[] = "<links>([\\S\\s]*)</links>";
const char Regex_parser::LINK_REGEX[] = "<&\\((\\S*)\\)\\[([0-9]{1,3})\\]\\s*\\=\\s*\"(.*?)\"\\s*>";
const char Regex_parser::CARR_CHR_EQUAL[] = "<n>";
const char Regex_parser::TAB_CHR_EQUAL[] = "<t>";

// Parsing the file text (false - OK, true - ERROR)
bool Regex_parser::parse_file(char *file_text, std::map<int, Text_block*> &text_parts)
{
    // Check the map for elements
    if (!text_parts.empty())
	{
        // Delete text parts
        for (auto iter = text_parts.begin(); iter != text_parts.end(); ++iter)
            delete iter->second;
        // Erase all elements
        text_parts.clear();
    }
    // Copy text to the string
    std::string file_textStr(file_text);
    // Parsing result
    std::cmatch result_str;
    // Regex template to search for
    const std::regex regex_template(BLOCK_TEXT_REGEX);
    // Link to the text part
    int link = -1;
    // Parsing...
    while (std::regex_search(file_textStr.c_str(), result_str, regex_template))
	{
        link = atoi(result_str.str(1).c_str());
        // Create memory for the text part
        text_parts[link] = new Text_block(result_str.str(2).c_str());
        // Next iteration of the loop
        file_textStr = result_str.suffix().str();
    }
    // If the text parts are not founded, return the true value
    if (link == -1)
        return true;
    // If everything is OK, return the false value
    return false;
}

// Get the vector with text links from the text part (false - OK, true - ERROR)
bool Regex_parser::parse_links(const char *part, std::vector<Text_link*> &vect_links)
{
    // Check the vector for elements
    if (!vect_links.empty())
	{
        // Delete the text links
        for (auto it = vect_links.begin(); it != vect_links.end(); ++it)
            delete *it;
        vect_links.clear();
    }
    // Copy text to the string
    std::string link_text_str(part);
    // Parsing result
    std::cmatch result_str;
    // Regex template to search for
    std::regex regex_template(LINKS_TEXT_REGEX);
    // Preparation...
    if (std::regex_search(link_text_str.c_str(), result_str, regex_template))
        link_text_str = result_str.str(1);
    else
        // If the links to the text parts are not founded, return the true value
        return true;
    // Link to the text part
    int link = -1;
    regex_template = LINK_REGEX;
    // Parsing...
    while (std::regex_search(link_text_str.c_str(), result_str, regex_template))
	{
        link = atoi(result_str.str(2).c_str());
        // Create a vector with text links
        Text_link *textLink = new Text_link(link, result_str.str(3).c_str(), result_str.str(1).c_str());
        vect_links.push_back(textLink);
        // Next iteration of the loop
        link_text_str = result_str.suffix().str();
    }
    // If the links to the text parts are not founded, return the true value
    if (link == -1)
        return true;
    // If everything is OK, return the false value
    return false;
}

// Get the pointers to the main, header and extra text (false - OK, true - ERROR)
bool Regex_parser::parse_text(const char *part, char **main_text, char **header_text, char **extra_text)
{
    // Check the pointer to the main text
    if ((*main_text) != nullptr)
	{
        delete [] (*main_text);
        (*main_text) = nullptr;
    }
    // Check the pointer to the header text
    if ((*header_text) != nullptr)
	{
        delete [] (*header_text);
        (*header_text) = nullptr;
    }
    // Check the pointer to the extra text
    if ((*extra_text) != nullptr)
	{
        delete [] (*extra_text);
        (*extra_text) = nullptr;
    }
    
    // Copy text to the string
    std::string textStr(part);
    // Parsing result
    std::cmatch result_str;
    // Regex template to search for
    std::regex regex_template("\n|\t");
    // Delete all '\n' and '\t' characters from the main text
    std::string replace_str = std::regex_replace(textStr, regex_template, "");
    // Replace the carriage strings with the '\n' characters
    regex_template = CARR_CHR_EQUAL;
    replace_str = std::regex_replace(replace_str, regex_template, "\n");
    // Replace the tab lines with the space characters
    regex_template = TAB_CHR_EQUAL;
    textStr = std::regex_replace(replace_str, regex_template, "    ");
    
    // Find the main text
    regex_template = MAIN_TEXT_REGEX;
    if (std::regex_search(textStr.c_str(), result_str, regex_template))
	{
        // Create the main text
        int strLen = result_str.str(1).length();
        (*main_text) = new char[strLen + 1];
        strcpy((*main_text), result_str.str(1).c_str());
    }
    else
    {
        // If the text main is not founded, return the true value
        return true;
    }
    
    // Find the header text
    regex_template = HEADER_TEXT_REGEX;
    if (std::regex_search(textStr.c_str(), result_str, regex_template))
	{
        // Create the header text
        int strLen = result_str.str(1).length();
        (*header_text) = new char[strLen + 1];
        strcpy((*header_text), result_str.str(1).c_str());
    }
    
    // Find the extra text
    regex_template = EXTRA_TEXT_REGEX;
    if (std::regex_search(textStr.c_str(), result_str, regex_template))
	{
        // Create the extra text
        int strLen = result_str.str(1).length();
        (*extra_text) = new char[strLen + 1];
        strcpy((*extra_text), result_str.str(1).c_str());
    }
    
    // If everything is OK, return the false value
    return false;
}
