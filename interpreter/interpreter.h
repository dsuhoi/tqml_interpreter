#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <string>
#include <map>
#include "../parserlib/text_data.h"

// TQML interpreter functions

// Initialize the interpreter components
int Initialize(char *_filePath, std::map<int, TextBlock*> &textParts, std::string &mainPath);
// Main loop of the interpreter
int Process(std::map<int, TextBlock*> &textParts, const std::string &mainPath);
// End of the program
void EndProgram(std::map<int, TextBlock*> &textParts);

#endif
