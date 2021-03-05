#include "terminal.hpp"
#include "files.hpp"
#include "regex_parser.hpp"
#include "interpreter.hpp"


// Initialize the interpreter components
int initialize(char *_file_path, std::map<int, Text_block*> &text_parts, std::string &main_path)
{
    // Get the path to the folder with the question
    Filesystem::get_dir(_file_path, main_path);
    // Initialization of terminal functions
    if (Terminal::init_terminal())
        return 2;
    // Initialization of all windows
    if (Terminal::init_all_windows())
        return 3;
    // Buffer for a file text
    char *read_text = nullptr;
    // Read the text file
    if (Filesystem::read_file(_file_path, &read_text))
        return 4;
    // Parsing the file text
    if (Regex_parser::parse_file(read_text, text_parts))
        return 5;
    // Delete the buffer for a file text
    delete [] read_text;
    
    return 0;
}

// Main loop of the interpreter
int process(std::map<int, Text_block*> &text_parts, const std::string &main_path)
{
    int current_part = 0;
    // Print the help information
    Terminal::print_help_window();
    // Main loop
    while (1)
	{
        // Pointers to text blocks and their text links
        Text_block *current_text_block = text_parts[current_part];
        // Print the windows
        Terminal::print_window(HEAD, current_text_block->get_header_text());
        Terminal::print_window(EXTRA, current_text_block->get_extra_text());
        Terminal::print_window(MAIN_TEXT, current_text_block->get_main_text());
        Terminal::print_system_window();

        Text_link *current_text_link = nullptr;
        char *answer = nullptr;
        // Input loop
        do {
            if (Terminal::input_loop())
                return 0;
            answer = Terminal::get_answer();
            
            if ((current_text_link = current_text_block->get_link(answer)) == nullptr)
                Terminal::print_system_window((char*)"Invalid input!!!");
        } while (current_text_link == nullptr);
        
        // Save the link
        current_part = current_text_link->get_link_num();
        
        if (current_text_link->get_file_name() != nullptr)
	    {
            // Main path string
            std::string new_path_str = main_path + current_text_link->get_file_name();
            // Buffer for a file text
            char *read_text = nullptr;
            // Read the file and parsing the its text
            if (Filesystem::read_file(const_cast<char*>(new_path_str.c_str()), &read_text))
                return 4;
            if (Regex_parser::parse_file(read_text, text_parts))
                return 5;
            // Delete the buffer for a file text
            delete [] read_text;
        }
    }
    
    return 0;
}

// End of the program
void end_program(std::map<int, Text_block*> &text_parts)
{
    // Check the map for elements
    if (!text_parts.empty())
	{
        for (auto iter = text_parts.begin(); iter != text_parts.end(); ++iter)
            // Delete text parts
            delete iter->second;
        // Erase all elements
        text_parts.clear();
    }
    
    Terminal::final_terminal();
}
