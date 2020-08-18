#include "interpreter.h"
#include "../termlib/terminal.h"
#include "../filesystem/files.h"
#include "../parserlib/regex_parser.h"


// Constructor
Interpreter::Interpreter()
{
	
}

// Destructor
Interpreter::~Interpreter()
{
		
}

// Initialize the interpreter components
int Interpreter::Initialize(char *_filePath)
{
	if(Terminal::InitTerminal()){
		return 1;
	}
	
	if(Terminal::InitAllWindows()){
		return 2;
	}
	
	size_t strLen = strlen(_filePath);
	filePath = new char[strLen];
	strcpy(filePath, _filePath);
	
	char *readText = nullptr;
	
	if(Filesystem::ReadFile(_filePath, &readText)){
		return 3;
	}
	
	if(RegexParser::ParseFile(readText, textParts)){
		return 4;
	}
	
	return 0;
}


int Interpreter::Process()
{
	while(1){
		Terminal::PrintWindow();
		
	}
	
	return 0;
}





