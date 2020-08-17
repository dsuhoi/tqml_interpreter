#include <cstring>
#include <string>
#include "text_data.h"
#include "regex_parser.h"

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
int TextLink::GetLinkNum()
{
	return linkNumber;
}



// Constructor
TextBlock::TextBlock(const char *fullText)
{
	mainText = nullptr;
	headerText = nullptr;
	extraText = nullptr;
	
	RegexParser::ParseLinks(fullText, vectLinks);
	RegexParser::ParseText(fullText, &mainText, &headerText, &extraText);
}

// Destructor
TextBlock::~TextBlock()
{
	// Check the vector for elements
	if(!vectLinks.empty()){
		// Delete the text links
		for(auto it = vectLinks.begin(); it != vectLinks.end(); it++){
			delete *it;
		}
	}
	// Delete the memory for text data
	if(mainText != nullptr){
		delete [] mainText;
	}
	
	if(headerText != nullptr){
		delete [] headerText;
	}
	
	if(extraText != nullptr){
		delete [] extraText;
	}
}

// Return a pointer to the main text from the block
char *TextBlock::GetMainText()
{
	return mainText;
}

// Return a pointer to the header text from the block
char *TextBlock::GetHeaderText()
{
	return headerText;
}

// Return a pointer to the extra text from the block
char *TextBlock::GetExtraText()
{
	return extraText;
}

// Return a pointer to the text link object
TextLink *TextBlock::GetLink(char *Answer)
{
	// Select the text link
	for(auto it = vectLinks.cbegin(); it != vectLinks.cend(); it++){
		if(!(strcmp((*it)->GetAnswer(), Answer))){
			return *it;
		}
	}
	// If the answer isn't founded, return the nullptr
	return nullptr;
}
