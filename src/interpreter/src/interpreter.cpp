#include "terminal.hpp"
#include "files.hpp"
#include "regex_parser.hpp"
#include "interpreter.hpp"
#include <optional>


// Initialize the interpreter components
int initialize(std::string_view _file_path, std::map<int, Text_block>& text_parts, std::string& main_path)
{
    // Get the path to the folder with the question
    main_path = Filesystem::get_dir(_file_path);
    // Initialization of terminal functions
    if (Terminal::init_terminal())
        throw 2;
    // Initialization of all windows
    if (Terminal::init_all_windows())
        throw 3;
    // Buffer for a file text
    std::string read_text;
    // Read the text file
    if (Filesystem::read_file(_file_path, read_text))
        throw 4;
    // Parsing the file text
    if (Regex_parser::parse_file(read_text, text_parts))
        throw 5;
    // Delete the buffer for a file text
    
    return 0;
}

// Main loop of the interpreter
int process(std::map<int, Text_block>& text_parts, std::string const& main_path)
{
    int current_part = 0;
    // Print the help information
    Terminal::print_help_window();
    // Main loop
    while (1)
	{
        // Pointers to text blocks and their text links
        Text_block& current_text_block = text_parts[current_part];
        // Print the windows
        Terminal::print_window(HEAD, current_text_block.get_header_text().data());
        Terminal::print_window(EXTRA, current_text_block.get_extra_text().data());
        Terminal::print_window(MAIN_TEXT, current_text_block.get_main_text().data());
        Terminal::print_system_window();

        std::optional<Text_link> current_text_link;
        std::string answer;
        // Input loop
        do
        {
            if (Terminal::input_loop())
                return 0;
            answer = Terminal::get_answer();
            
            if ((current_text_link = current_text_block.get_link(answer)) == std::nullopt)
                Terminal::print_system_window((char*)"Invalid input!!!");
        } while (current_text_link == std::nullopt);
        
        // Save the link
        current_part = current_text_link.value().get_link_num();
        
        if (!current_text_link.value().get_file_name().empty())
	    {
            // Main path string
            std::string new_path_str = main_path + current_text_link.value().get_file_name();
            // Buffer for a file text
            std::string read_text;
            // Read the file and parsing the its text
            if (Filesystem::read_file(new_path_str, read_text))
                throw 4;
            if (Regex_parser::parse_file(read_text, text_parts))
                throw 5;
        }
    }
    
    return 0;
}

// End of the program
void end_program(std::map<int, Text_block>& text_parts)
{
    Terminal::final_terminal();
}
