#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>
#include <map>
#include "text_data.hpp"


// TQML interpreter functions
// Initialize the interpreter components
int initialize(std::string_view _file_path, std::map<int, Text_block>& text_parts, std::string& main_path);
// Main loop of the interpreter
int process(std::map<int, Text_block>& text_parts, std::string const& main_path);
// End of the program
void end_program(std::map<int, Text_block>& text_parts);

#endif
