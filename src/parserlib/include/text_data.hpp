#ifndef __TEXT_DATA_H__
#define __TEXT_DATA_H__

#include <vector>

// Text link to the next text part
class Text_link
{
public:
    // Empty constructor
    Text_link();
    // Main constructor
    Text_link(int _link, const char *_answer, const char *_file);
    // Destructor
    ~Text_link();
    // Return the pointer to the file name (char array)
    char *get_file_name();
    // Return the pointer to the answer (char array)
    char *get_answer();
    // Return the link to the next text part
    int get_link_num();
private:
    // Pointer to the file name string
    char *file_name;
    // Pointer to the answer string
    char *text_answer;
    // Link to the next text part
    int link_number;
};

// Text block class
class Text_block
{
public:
    // Constructor
    Text_block(const char *full_text);
    // Destructor
    ~Text_block();
    // Return a pointer to the main text from the block
    char *get_main_text();
    // Return a pointer to the header text from the block
    char *get_header_text();
    // Return a pointer to the extra text from the block
    char *get_extra_text();
    // Return a pointer to the text link object
    Text_link *get_link(char *answer);
private:
    // Vector with text links
    std::vector<Text_link*> vect_links;
    // Extra text in the text block
    char *extra_text;
    // Header text in the text block
    char *header_text;
    // Main text in the text block
    char *main_text;
};

#endif
