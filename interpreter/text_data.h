#ifndef __TEXT_DATA_H__
#define __TEXT_DATA_H__

#include <vector>

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
	TextLink(int _link, const char *_answer, const char *_file);
	// Destructor
	~TextLink();
	// Return the pointer to the file name (char array)
	char *GetFileName();
	// Return the pointer to the answer (char array)
	char *GetAnswer();
	// Return the link to the next text part
	int GetLinkNum();
};

// Text block class
class TextBlock {
private:
	// Vector with text links
	std::vector<TextLink*> vectLinks;
	// Main text in the text block
	char *mainText;
public:
	// Constructor
	TextBlock(const char *fullText);
	// Destructor
	~TextBlock();
	// Return a pointer to the main text from the block
	char *GetMainText();
	// Return a pointer to the text link object
	TextLink *GetLink(char *Answer);
};

#endif
