#include <string>
#include "interpreter.h"


// Regular expression for parsing file text
const char RegexParser::FILE_TEXT_REGEX[] = "<text\\[([0-9]{1,3})\\]>([\\S\\s]*?)</text>";
// Map to the text parts and its link
std::map<int, char*> RegexParser::textParts;


// Empty constructor
TextLink::TextLink()
{
	fileName = nullptr;
	textAnswer = nullptr;
	linkNumber = 0;
}

// Main constructor
TextLink::TextLink(int _link, char *_answer, char *_file)
{	
	linkNumber = _link;
	
	textAnswer = new char [strlen(_answer) + 1];
	strcpy(textAnswer, _answer);
	
	fileName = new char [strlen(_file) + 1];
	strcpy(fileName, _file);	
}

// Destructor
TextLink::~TextLink()
{
	if(textAnswer != nullptr){
		delete [] textAnswer;
	}
	if(fileName != nullptr){
		delete [] fileName;
	}
}

// Return the pointer to the file name (char array)
char *TextLink::GetFileName()
{
	return fileName;
}

// Return the pointer to the answer (char array)
char *TextLink::GetAnswer()
{
	return textAnswer;
}

// Return the link to the next text part
int TextLink::GetLink()
{
	return linkNumber;
}


// Parsing the file text (Return an array with text parts) (false - OK, true - ERROR)
bool RegexParser::ParseFile(char *fileText)
{
	// Check the map for elements
	if(!textParts.empty()){
		for(auto iter = textParts.begin(); iter != textParts.end(); iter++){
			// Delete text parts
			delete [] iter->second;
		}
		// Erase all elements
		textParts.clear();
	}
	// Copy text to the string
	std::string fileTextStr(fileText);
	// Parsing result
	std::cmatch resultStr;
	// Regex template to search for
	const std::regex regexTemplate(FILE_TEXT_REGEX);
	// Link to the text part
	int link = 0;
	while(std::regex_search(fileTextStr.c_str(), resultStr, regexTemplate)){
		for(size_t part = 0; part < resultStr.size(); part++){
			if(part % 3 == 1){
				link = atoi(resultStr.str(part).c_str());
				
			}
			else if(part % 3 == 2){
				// Create memory for the text part
				int strLen = resultStr.str(part).length();
				textParts[link] = new char [strLen];
				strcpy(textParts[link], resultStr.str(part).c_str());
			}
			
		}
		// Next iteration of the loop
		fileTextStr = resultStr.suffix().str();
	}
	
	return false;
}


