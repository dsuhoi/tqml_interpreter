#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__


#include <vector>
#include <regex>

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

class RegexParser {
private:
	static const char TEXT_TEMPLATE[];
	static char **textParts;
public:
	// Parsing the file text (Return an array with text parts)
	static char **ParseFile(char *fileText);
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

const char RegexParser::TEXT_TEMPLATE[] = "<text\\[([0-9]{1,2})\\]>([\\S\\s]*?)</text>";

#endif
