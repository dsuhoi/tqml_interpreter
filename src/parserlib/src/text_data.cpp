#include <cstring>
#include <string>
#include "text_data.hpp"
#include "regex_parser.hpp"

// Empty constructor
Text_link::Text_link()
{
    file_name = nullptr;
    text_answer = nullptr;
    link_number = 0;
}

// Main constructor
Text_link::Text_link(int _link, const char *_answer, const char *_file)
{   
    link_number = _link;
    
    text_answer = new char [strlen(_answer) + 1];
    strcpy(text_answer, _answer);
    
    if (_file[0] != 0)
	{
        file_name = new char [strlen(_file) + 1];
        strcpy(file_name, _file);
    }
    else
    {
        // If the string is empty, set the nullptr
        file_name = nullptr;
    }
}

// Destructor
Text_link::~Text_link()
{
    // Delete data from memory
    if (text_answer != nullptr)
        delete [] text_answer;

    if (file_name != nullptr)
        delete [] file_name;
}

// Return the pointer to the file name (char array)
char *Text_link::get_file_name()
{
    return file_name;
}

// Return the pointer to the answer (char array)
char *Text_link::get_answer()
{
    return text_answer;
}

// Return the link to the next text part
int Text_link::get_link_num()
{
    return link_number;
}



// Constructor
Text_block::Text_block(const char *full_text)
{
    main_text = nullptr;
    header_text = nullptr;
    extra_text = nullptr;
    
    Regex_parser::parse_links(full_text, vect_links);
    Regex_parser::parse_text(full_text, &main_text, &header_text, &extra_text);
}

// Destructor
Text_block::~Text_block()
{
    // Check the vector for elements
    if (!vect_links.empty())
    {
        // Delete the text links
        for (auto it = vect_links.begin(); it != vect_links.end(); ++it)
            delete *it;
        // Erase all elements
        vect_links.clear();
    }
    // Delete the memory for text data
    if (main_text != nullptr)
        delete [] main_text;
    
    if (header_text != nullptr)
        delete [] header_text;
    
    if (extra_text != nullptr)
        delete [] extra_text;
}

// Return a pointer to the main text from the block
char *Text_block::get_main_text()
{
    return main_text;
}

// Return a pointer to the header text from the block
char *Text_block::get_header_text()
{
    return header_text;
}

// Return a pointer to the extra text from the block
char *Text_block::get_extra_text()
{
    return extra_text;
}

// Return a pointer to the text link object
Text_link *Text_block::get_link(char *answer)
{
    // Select the text link
    for (auto it = vect_links.cbegin(); it != vect_links.cend(); ++it)
        if (!(strcmp((*it)->get_answer(), answer)))
            return *it;
    // If the answer isn't founded, return the nullptr
    return nullptr;
}
