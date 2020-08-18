#include "interpreter.h"
#include "../termlib/terminal.h"
#include "../filesystem/files.h"
#include "../parserlib/regex_parser.h"


// Constructor
Interpreter::Interpreter()
{
	mainPath = "";
	currentPart = 0;
}

// Destructor
Interpreter::~Interpreter()
{
	mainPath.clear();
}

// Initialize the interpreter components
int Interpreter::Initialize(char *_filePath)
{
	
	Filesystem::GetDir(_filePath, mainPath);
	
	if(Terminal::InitTerminal()){
		return 1;
	}
	
	if(Terminal::InitAllWindows()){
		return 2;
	}
	
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
		//
		
	}
	
	return 0;
}





