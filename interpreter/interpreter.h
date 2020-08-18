#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <map>
#include <string>
#include "../parserlib/text_data.h"


// TQML interpreter class
class Interpreter {
private:
	// Map to the text parts and its link
	std::map<int, TextBlock*> textParts;
	int currentPart;
	std::string mainPath;
public:
	// Constructor
	Interpreter();
	// Destructor
	~Interpreter();
	// Initialize the interpreter components
	int Initialize(char *_filePath);
	int Process();
};



#endif
