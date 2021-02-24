#include "../../termlib/include/terminal.h"
#include "../../filesystem/include/files.h"
#include "../../parserlib/include/regex_parser.h"
#include "../include/interpreter.h"


// Initialize the interpreter components
int initialize(char *_filePath, std::map<int, TextBlock*> &textParts, std::string &mainPath)
{
    // Get the path to the folder with the question
    Filesystem::getDir(_filePath, mainPath);
    // Initialization of terminal functions
    if (Terminal::initTerminal())
        return 2;
    // Initialization of all windows
    if (Terminal::initAllWindows())
        return 3;
    // Buffer for a file text
    char *readText = nullptr;
    // Read the text file
    if (Filesystem::readFile(_filePath, &readText))
        return 4;
    // Parsing the file text
    if (RegexParser::parseFile(readText, textParts))
        return 5;
    // Delete the buffer for a file text
    delete [] readText;
    
    return 0;
}

// Main loop of the interpreter
int process(std::map<int, TextBlock*> &textParts, const std::string &mainPath)
{
    int currentPart = 0;
    // Print the help information
    Terminal::printHelpWindow();
    // Main loop
    while (1) {
        // Pointers to text blocks and their text links
        TextBlock *currentTextBlock = textParts[currentPart];
        // Print the windows
        Terminal::printWindow(HEAD, currentTextBlock->getHeaderText());
        Terminal::printWindow(EXTRA, currentTextBlock->getExtraText());
        Terminal::printWindow(MAIN_TEXT, currentTextBlock->getMainText());
        Terminal::printSystemWindow();

        TextLink *currentTextLink = nullptr;
        char *answer = nullptr;
        // Input loop
        do {
            if (Terminal::inputLoop())
                return 0;
            answer = Terminal::getAnswer();
            
            if ((currentTextLink = currentTextBlock->getLink(answer)) == nullptr)
                Terminal::printSystemWindow((char*)"Invalid input!!!");
        } while (currentTextLink == nullptr);
        
        // Save the link
        currentPart = currentTextLink->getLinkNum();
        
        if (currentTextLink->getFileName() != nullptr) {
            // Main path string
            std::string newPathStr = mainPath + currentTextLink->getFileName();
            // Buffer for a file text
            char *readText = nullptr;
            // Read the file and parsing the its text
            if (Filesystem::readFile(const_cast<char*>(newPathStr.c_str()), &readText))
                return 4;
            if (RegexParser::parseFile(readText, textParts))
                return 5;
            // Delete the buffer for a file text
            delete [] readText;
        }
    }
    
    return 0;
}

// End of the program
void endProgram(std::map<int, TextBlock*> &textParts)
{
    // Check the map for elements
    if (!textParts.empty()) {
        for (auto iter = textParts.begin(); iter != textParts.end(); iter++)
            // Delete text parts
            delete iter->second;
        // Erase all elements
        textParts.clear();
    }
    
    Terminal::finalTerminal();
}
