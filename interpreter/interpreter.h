#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <map>
#include <regex>


// Text link to the next text part
class TextLink {
private:
	// Pointer to the file name string
	char *fileName;
	// Pointer to the answer string
	char *textAnswer;
	// Link to the next text part
	int linkNumber;
public:
	// Empty constructor
	TextLink();
	// Main constructor
	TextLink(int _link, char *_answer, char *_file = nullptr);
	// Destructor
	~TextLink();
	// Return the pointer to the file name (char array)
	char *GetFileName();
	// Return the pointer to the answer (char array)
	char *GetAnswer();
	// Return the link to the next text part
	int GetLink();
};

// Class for parsing text data
class RegexParser {
private:
	// Regular expression for parsing file text
	static const char FILE_TEXT_REGEX[];
	// Map to the text parts and its link
	static std::map<int, char*> textParts;
	
	// Private constructor
	RegexParser() {}
public:
	// Parsing the file text (Return an array with text parts) (false - OK, true - ERROR)
	static bool ParseFile(char *fileText);
	// Return the pointer to the text links from the text part
	static TextLink *ParseLinks(char *part);
};


// TQML interpreter class
class Interpreter {
private:
	std::vector<std::string> vect;

public:
	// Constructor and Destructor
	Interpreter();
	~Interpreter();
	
	
};



#endif
