#include <string>
#include "interpreter.h"


// Regular expression for parsing file text
const char RegexParser::FILE_TEXT_REGEX[] = "<text\\[([0-9]{1,3})\\]>([\\S\\s]*?)</text>";
const char RegexParser::LINKS_TEXT_REGEX[] = "<links>([\\S\\s]*)</links>";
const char RegexParser::LINK_REGEX[] = "<&\\((\\S*)\\)\\[([0-9]{1,3})\\]\\s*\\=\\s*\"(.*?)\"\\s*>";


// Empty constructor
TextLink::TextLink()
{
	fileName = nullptr;
	textAnswer = nullptr;
	linkNumber = 0;
}

// Main constructor
TextLink::TextLink(int _link, const char *_answer, const char *_file)
{	
	linkNumber = _link;
	
	textAnswer = new char [strlen(_answer) + 1];
	strcpy(textAnswer, _answer);
	
	if(_file[0] != 0){
		fileName = new char [strlen(_file) + 1];
		strcpy(fileName, _file);
	}
	else{
		// If the string is empty, set the nullptr
		fileName = nullptr;
	}
}

// Destructor
TextLink::~TextLink()
{
	// Delete data from memory
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
bool RegexParser::ParseFile(char *fileText, std::map<int, char*> &textParts)
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
	int link = -1;
	// Parsing...
	while(std::regex_search(fileTextStr.c_str(), resultStr, regexTemplate)){
		link = atoi(resultStr.str(1).c_str());
		// Create memory for the text part
		int strLen = resultStr.str(2).length() + 1;
		textParts[link] = new char [strLen];
		strcpy(textParts[link], resultStr.str(2).c_str());
		// Next iteration of the loop
		fileTextStr = resultStr.suffix().str();
	}
	// If the text parts are not founded, return the true value
	if(link == -1){
		return true;
	}
	// If everything is OK, return the false value
	return false;
}

// Return the pointer to the text links from the text part
bool RegexParser::ParseLinks(char *part, std::vector<TextLink*> &vectLinks)
{
	// Check the vector for elements
	if(!vectLinks.empty()){
		// Delete the text links
		for(auto it = vectLinks.begin(); it != vectLinks.end(); it++){
			delete *it;
		}
		vectLinks.clear();
	}
	// Copy text to the string
	std::string LinkTextStr(part);
	// Parsing result
	std::cmatch resultStr;
	// Regex template to search for
	const std::regex regexTemplateForLinks(LINKS_TEXT_REGEX);
	const std::regex regexTemplate(LINK_REGEX);
	// Preparation...
	if(std::regex_search(LinkTextStr.c_str(), resultStr, regexTemplateForLinks)){
		LinkTextStr = resultStr.str(1);
	}
	else{
		// If the links to the text parts are not founded, return the true value
		return true;
	}
	// Link to the text part
	int link = -1;
	// Parsing...
	while(std::regex_search(LinkTextStr.c_str(), resultStr, regexTemplate)){
		link = atoi(resultStr.str(2).c_str());
		// Create a vector with text links
		TextLink *textLink = new TextLink(link, resultStr.str(3).c_str(), resultStr.str(1).c_str());
		vectLinks.push_back(textLink);
		// Next iteration of the loop
		LinkTextStr = resultStr.suffix().str();
	}
	// If the links to the text parts are not founded, return the true value
	if(link == -1){
		return true;
	}
	// If everything is OK, return the false value
	return false;
}



