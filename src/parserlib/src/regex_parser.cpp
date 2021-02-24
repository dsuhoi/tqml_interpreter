#include <string>
#include <regex>
#include "../includes/regex_parser.h"


// Regular expression for parsing file text
const char RegexParser::BLOCK_TEXT_REGEX[] = "<text\\[([0-9]{1,3})\\]>([\\S\\s]*?)</text>";
const char RegexParser::MAIN_TEXT_REGEX[] = "<main>([\\S\\s]*?)</main>";
const char RegexParser::HEADER_TEXT_REGEX[] = "<header>(.*?)</header>";
const char RegexParser::EXTRA_TEXT_REGEX[] = "<info>([\\S\\s]*?)</info>";
const char RegexParser::LINKS_TEXT_REGEX[] = "<links>([\\S\\s]*)</links>";
const char RegexParser::LINK_REGEX[] = "<&\\((\\S*)\\)\\[([0-9]{1,3})\\]\\s*\\=\\s*\"(.*?)\"\\s*>";
const char RegexParser::CARR_CHR_EQUAL[] = "<n>";
const char RegexParser::TAB_CHR_EQUAL[] = "<t>";

// Parsing the file text (false - OK, true - ERROR)
bool RegexParser::parseFile(char *fileText, std::map<int, TextBlock*> &textParts)
{
    // Check the map for elements
    if (!textParts.empty()) {
        // Delete text parts
        for (auto iter = textParts.begin(); iter != textParts.end(); ++iter)
            delete iter->second;
        // Erase all elements
        textParts.clear();
    }
    // Copy text to the string
    std::string fileTextStr(fileText);
    // Parsing result
    std::cmatch resultStr;
    // Regex template to search for
    const std::regex regexTemplate(BLOCK_TEXT_REGEX);
    // Link to the text part
    int link = -1;
    // Parsing...
    while (std::regex_search(fileTextStr.c_str(), resultStr, regexTemplate)) {
        link = atoi(resultStr.str(1).c_str());
        // Create memory for the text part
        textParts[link] = new TextBlock(resultStr.str(2).c_str());
        // Next iteration of the loop
        fileTextStr = resultStr.suffix().str();
    }
    // If the text parts are not founded, return the true value
    if (link == -1)
        return true;
    // If everything is OK, return the false value
    return false;
}

// Get the vector with text links from the text part (false - OK, true - ERROR)
bool RegexParser::parseLinks(const char *part, std::vector<TextLink*> &vectLinks)
{
    // Check the vector for elements
    if (!vectLinks.empty()) {
        // Delete the text links
        for (auto it = vectLinks.begin(); it != vectLinks.end(); ++it)
            delete *it;
        vectLinks.clear();
    }
    // Copy text to the string
    std::string linkTextStr(part);
    // Parsing result
    std::cmatch resultStr;
    // Regex template to search for
    std::regex regexTemplate(LINKS_TEXT_REGEX);
    // Preparation...
    if (std::regex_search(linkTextStr.c_str(), resultStr, regexTemplate))
        linkTextStr = resultStr.str(1);
    else
        // If the links to the text parts are not founded, return the true value
        return true;
    // Link to the text part
    int link = -1;
    regexTemplate = LINK_REGEX;
    // Parsing...
    while (std::regex_search(linkTextStr.c_str(), resultStr, regexTemplate)) {
        link = atoi(resultStr.str(2).c_str());
        // Create a vector with text links
        TextLink *textLink = new TextLink(link, resultStr.str(3).c_str(), resultStr.str(1).c_str());
        vectLinks.push_back(textLink);
        // Next iteration of the loop
        linkTextStr = resultStr.suffix().str();
    }
    // If the links to the text parts are not founded, return the true value
    if (link == -1)
        return true;
    // If everything is OK, return the false value
    return false;
}

// Get the pointers to the main, header and extra text (false - OK, true - ERROR)
bool RegexParser::parseText(const char *part, char **mainText, char **headerText, char **extraText)
{
    // Check the pointer to the main text
    if ((*mainText) != nullptr) {
        delete [] (*mainText);
        (*mainText) = nullptr;
    }
    // Check the pointer to the header text
    if ((*headerText) != nullptr) {
        delete [] (*headerText);
        (*headerText) = nullptr;
    }
    // Check the pointer to the extra text
    if ((*extraText) != nullptr) {
        delete [] (*extraText);
        (*extraText) = nullptr;
    }
    
    // Copy text to the string
    std::string textStr(part);
    // Parsing result
    std::cmatch resultStr;
    // Regex template to search for
    std::regex regexTemplate("\n|\t");
    // Delete all '\n' and '\t' characters from the main text
    std::string replaceStr = std::regex_replace(textStr, regexTemplate, "");
    // Replace the carriage strings with the '\n' characters
    regexTemplate = CARR_CHR_EQUAL;
    replaceStr = std::regex_replace(replaceStr, regexTemplate, "\n");
    // Replace the tab lines with the space characters
    regexTemplate = TAB_CHR_EQUAL;
    textStr = std::regex_replace(replaceStr, regexTemplate, "    ");
    
    // Find the main text
    regexTemplate = MAIN_TEXT_REGEX;
    if (std::regex_search(textStr.c_str(), resultStr, regexTemplate)) {
        // Create the main text
        int strLen = resultStr.str(1).length();
        (*mainText) = new char[strLen + 1];
        strcpy((*mainText), resultStr.str(1).c_str());
    } else {
        // If the text main is not founded, return the true value
        return true;
    }
    
    // Find the header text
    regexTemplate = HEADER_TEXT_REGEX;
    if (std::regex_search(textStr.c_str(), resultStr, regexTemplate)) {
        // Create the header text
        int strLen = resultStr.str(1).length();
        (*headerText) = new char[strLen + 1];
        strcpy((*headerText), resultStr.str(1).c_str());
    }
    
    // Find the extra text
    regexTemplate = EXTRA_TEXT_REGEX;
    if (std::regex_search(textStr.c_str(), resultStr, regexTemplate)) {
        // Create the extra text
        int strLen = resultStr.str(1).length();
        (*extraText) = new char[strLen + 1];
        strcpy((*extraText), resultStr.str(1).c_str());
    }
    
    // If everything is OK, return the false value
    return false;
}
