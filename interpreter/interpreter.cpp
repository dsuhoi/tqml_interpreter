#include "../termlib/terminal.h"
#include "../filesystem/files.h"
#include "../parserlib/regex_parser.h"
#include "interpreter.h"


// Initialize the interpreter components
int Initialize(char *_filePath, std::map<int, TextBlock*> &textParts, std::string &mainPath)
{
	// Get the path to the folder with the question
	Filesystem::GetDir(_filePath, mainPath);
	// Initialization of terminal functions
	if(Terminal::InitTerminal()){
		return 2;
	}
	// Initialization of all windows
	if(Terminal::InitAllWindows()){
		return 3;
	}
	// Buffer for a file text
	char *readText = nullptr;
	// Read the text file
	if(Filesystem::ReadFile(_filePath, &readText)){
		return 4;
	}
	// Parsing the file text
	if(RegexParser::ParseFile(readText, textParts)){
		return 5;
	}
	// Delete the buffer for a file text
	delete [] readText;
	
	return 0;
}

// Main loop of the interpreter
int Process(std::map<int, TextBlock*> &textParts, const std::string &mainPath)
{
	int currentPart = 0;
	// Main loop
	while(1){
		// Pointers to text blocks and their text links
		TextBlock *currentTextBlock = textParts[currentPart];
		
		Terminal::PrintWindow(HEAD, currentTextBlock->GetHeaderText());
		Terminal::PrintWindow(EXTRA, currentTextBlock->GetExtraText());
		Terminal::PrintWindow(MAIN_TEXT, currentTextBlock->GetMainText());
		Terminal::PrintSystemWindow();
		
		TextLink *currentTextLink = nullptr;
		char *answer = nullptr;
		// Input loop
		do{
			if(Terminal::InputLoop()){
				return 0;
			}
			answer = Terminal::GetAnswer();
		}while((currentTextLink = currentTextBlock->GetLink(answer)) == nullptr);
		// Save the link
		currentPart = currentTextLink->GetLinkNum();
		
		if(currentTextLink->GetFileName() != nullptr){
			// Main path string
			std::string newPathStr = mainPath + currentTextLink->GetFileName();
			// Buffer for a file text
			char *readText = nullptr;
			// Read the file and parsing the its text
			if(Filesystem::ReadFile(const_cast<char*>(newPathStr.c_str()), &readText)){
				return 4;
			}
			if(RegexParser::ParseFile(readText, textParts)){
				return 5;
			}
			// Delete the buffer for a file text
			delete [] readText;
		}
		
	}
	
	return 0;
}

// End of the program
void EndProgram(std::map<int, TextBlock*> &textParts)
{
	// Check the map for elements
	if(!textParts.empty()){
		for(auto iter = textParts.begin(); iter != textParts.end(); iter++){
			// Delete text parts
			delete iter->second;
		}
		// Erase all elements
		textParts.clear();
	}
	
	Terminal::FinalTerminal();
}
