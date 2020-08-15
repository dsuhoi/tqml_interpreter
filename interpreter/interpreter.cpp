#include <cstring>
#include "interpreter.h"


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
