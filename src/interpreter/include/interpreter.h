#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>
#include <map>
#include "text_data.h"


// TQML interpreter functions

// Initialize the interpreter components
int initialize(char *_filePath, std::map<int, TextBlock*> &textParts, std::string &mainPath);
// Main loop of the interpreter
int process(std::map<int, TextBlock*> &textParts, const std::string &mainPath);
// End of the program
void endProgram(std::map<int, TextBlock*> &textParts);

#endif
