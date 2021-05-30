#include <iostream>
#include <string>
#include <map>
#include "interpreter.hpp"


// Main function
int main(int argc, char **argv)
{
    // Check the string parametr
    if (argc < 2)
    {
        std::cout << "No text file specified.\n";
        return 1;
    }
    
    // Map to the text parts and its link
    std::map<int, Text_block> text_parts;
    // Path to the folder with the question
    std::string main_path;
    try
    {
        // Initialize the interpreter components
        initialize(argv[1], text_parts, main_path);
        // Main loop of the interpreter
        process(text_parts, main_path);
    }
    catch(int result)
    {
        end_program(text_parts);
        std::cout << "Exception code: " << result << std::endl;
        return result;
    }
    // End of the program
    end_program(text_parts);
    return 0;
}
