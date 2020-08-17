#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <map>
#include "../parserlib/text_data.h"


// TQML interpreter class
class Interpreter {
private:
	// Map to the text parts and its link
	std::map<int, TextBlock*> textParts;

public:
	// Constructor
	Interpreter();
	// Destructor
	~Interpreter();
	// Initialize the interpreter components
	void Initialize(char *filePath);
	
};



#endif
