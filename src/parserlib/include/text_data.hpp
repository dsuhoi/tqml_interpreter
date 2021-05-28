#ifndef __TEXT_DATA_H__
#define __TEXT_DATA_H__

#include <vector>
#include <string>
#include <optional>


// Text link to the next text part
class Text_link
{
public:
    // Empty constructor
    Text_link() = default;
    // Main constructor
    Text_link(int link, std::string_view answer, std::string_view file) : 
        _link_number(link), _text_answer(answer), _file_name(file) {}
    // Destructor
    ~Text_link() = default;
    // Return the pointer to the file name (char array)
    std::string get_file_name() const { return _file_name; }
    // Return the pointer to the answer (char array)
    std::string get_answer() const { return _text_answer; }
    // Return the link to the next text part
    int get_link_num() const { return _link_number; }
private:
    // Pointer to the file name string
    std::string _file_name;
    // Pointer to the answer string
    std::string _text_answer;
    // Link to the next text part
    int _link_number = 0;
};


// Text block class
class Text_block
{
public:
    // Constructor
    Text_block(std::string const& full_text)
    {
        Regex_parser::parse_links(full_text, _vect_links);
        Regex_parser::parse_text(full_text, _main_text, _header_text, _extra_text);
    }
    // Destructor
    ~Text_block() = default;
    // Return a pointer to the main text from the block
    std::string get_main_text() const { return _main_text; }
    // Return a pointer to the header text from the block
    std::string get_header_text() const { return _header_text; }
    // Return a pointer to the extra text from the block
    std::string get_extra_text() const { return _extra_text; }
    // Return a pointer to the text link object
    std::optional<Text_link> get_link(std::string_view answer)
    {
        auto iter = std::find_if(_vect_links.begin(), _vect_links.end(), 
            [answer](auto txt_link) { return txt_link.get_answer() == answer; });
        if (iter != _vect_links.end())
            return { *iter };
        else
            return std::nullopt;
    }
private:
    // Vector with text links
    std::vector<Text_link> _vect_links;
    // Extra text in the text block
    std::string _extra_text;
    // Header text in the text block
    std::string _header_text;
    // Main text in the text block
    std::string _main_text;
};

#endif
