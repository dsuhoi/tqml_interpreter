#include <iostream>
#include <string>
#include <map>
#include "interpreter.hpp"


// Main function
int main(int argc, char **argv)
{
    // Check the string parametr
    if (argc < 2) {
        std::cout << "No text file specified.\n";
        return 1;
    }
    
    // Map to the text parts and its link
    std::map<int, Text_block*> text_parts;
    // Path to the folder with the question
    std::string main_path;
    int result = 0;
    
    // Initialize the interpreter components
    if ((result = initialize(argv[1], text_parts, main_path)) != 0)
        return result;
        
    // Main loop of the interpreter
    if ((result = process(text_parts, main_path)) != 0) {
        end_program(text_parts);
        return result;
    }
    
    // End of the program
    end_program(text_parts);
    
    return 0;
}
