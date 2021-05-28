#include "regex_parser.hpp"
#include "text_data.hpp"


// Parsing the file text (false - OK, true - ERROR)
bool Regex_parser::parse_file(std::string file_text, std::map<int, Text_block>& text_parts)
{
    // Check the map for elements
    if (!text_parts.empty())
        text_parts.clear();

    // Parsing result
    std::cmatch result_str;
    // Regex template to search for
    const std::regex regex_template(BLOCK_TEXT_REGEX);
    // Link to the text part
    int link = -1;
    // Parsing...
    while (std::regex_search(file_text.data(), result_str, regex_template))
	{
        link = stoi(result_str.str(1));
        // Create memory for the text part
        text_parts.emplace(link, Text_block(result_str.str(2)));
        // Next iteration of the loop
        file_text = result_str.suffix();
    }
    // If the text parts are not founded, return the true value
    if (link == -1)
        return true;
    // If everything is OK, return the false value
    return false;
}

// Get the vector with text links from the text part (false - OK, true - ERROR)
bool Regex_parser::parse_links(std::string part, std::vector<Text_link>& vect_links)
{
    // Check the vector for elements
    if (!vect_links.empty())
        vect_links.clear();
    //
    // Copy text to the string
    std::string link_text_str(part);
    // Parsing result
    std::cmatch result_str;
    // Regex template to search for
    std::regex regex_template(LINKS_TEXT_REGEX);
    // Preparation...
    if (std::regex_search(part.c_str(), result_str, regex_template))
        link_text_str = result_str.str(1);
    else
        // If the links to the text parts are not founded, return the true value
        return true;
    // Link to the text part
    int link = -1;
    regex_template = LINK_REGEX;
    // Parsing...
    while (std::regex_search(part.c_str(), result_str, regex_template))
	{
        link = stoi(result_str.str(2));
        // Create a vector with text links
        vect_links.push_back(Text_link(link, result_str.str(3).c_str(), result_str.str(1)));
        // Next iteration of the loop
        part = result_str.suffix();
    }
    // If the links to the text parts are not founded, return the true value
    if (link == -1)
        return true;
    // If everything is OK, return the false value
    return false;
}

// Get the pointers to the main, header and extra text (false - OK, true - ERROR)
bool Regex_parser::parse_text(std::string part, std::string& main_text, std::string& header_text, std::string& extra_text)
{
        
    // Parsing result
    std::cmatch result_str;
    // Regex template to search for
    std::regex regex_template("\n|\t");
    // Delete all '\n' and '\t' characters from the main text
    std::string replace_str = std::regex_replace(part, regex_template, "");
    // Replace the carriage strings with the '\n' characters
    regex_template = CARR_CHR_EQUAL;
    replace_str = std::regex_replace(replace_str, regex_template, "\n");
    // Replace the tab lines with the space characters
    regex_template = TAB_CHR_EQUAL;
    part = std::regex_replace(replace_str, regex_template, "    ");
    
    // Find the main text
    regex_template = MAIN_TEXT_REGEX;
    if (std::regex_search(part.c_str(), result_str, regex_template))
        main_text = result_str.str(1);
    else
        return true;
    
    // Find the header text
    regex_template = HEADER_TEXT_REGEX;
    if (std::regex_search(part.c_str(), result_str, regex_template))
        header_text = result_str.str(1);
    
    // Find the extra text
    regex_template = EXTRA_TEXT_REGEX;
    if (std::regex_search(part.c_str(), result_str, regex_template))
        extra_text = result_str.str(1);
    
    // If everything is OK, return the false value
    return false;
}
