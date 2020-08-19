#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <ncurses.h>
#include "term_windows.h"

// background and cursor colors
enum BACKGROUND_COLORS {
	WHITE = 1,
	GREEN,
	YELLOW,
	BLUE,
	CYAN
};

// Names of the main windows
enum DISPLAY_WINDOWS {
	HEAD = 0,
	MAIN_TEXT,
	INPUT,
	EXTRA
//	SYSTEM
};


// For the name of the open file
const int INPUT_BUFFER_LEN = 256;

// Indent size
const int INDENT_WIDTH = 10;
const int INDENT_HEIGHT = 15;

// Height of the title window
const int HEAD_HEIGHT = 3;

// Height of the input, extra and system windows
const int WINDOW_HEIGHT = 5;

// Limit of the screen size
const int MIN_SCREEN_WIDTH = 1;
const int MIN_SCREEN_HEIGHT = 1;


// Class of terminal I/O function
class Terminal {
private:
	// Array of input characters
	static char inputBuffer[INPUT_BUFFER_LEN];
	
	// Window for displaying the title text
	static TERM_WINDOW *headWindow;
	// Window for displaying the text of the story
	static MAIN_TEXT_WINDOW *mainTextWindow;
	// Window for displaying the input user data
	static TERM_WINDOW *inputWindow;
	// Window for displaying the user extra information
	static TERM_WINDOW *extraWindow;
	// Window for displaying the system information
	static TERM_WINDOW *systemWindow;

	// Private constructor
	Terminal(){}
	// Analog refresh() function for the windows
	static void UpdateWindow(DISPLAY_WINDOWS windowName);
	// Initialization of the color scheme
	static void InitAllColors();
	// Clear a text in the window (false - OK, true - ERROR)
	static bool ClearWindow(DISPLAY_WINDOWS windowName);
	// Scanning input text from the input window
	static void ScanInputWindow();
public:
	// Initialization of terminal functions (false - OK, true - ERROR)
	static bool InitTerminal();
	// Initialization of all windows (false - OK, true - ERROR)
	static bool InitAllWindows();
	// End of terminal functions (false - OK, true - ERROR)
	static bool FinalTerminal();
	// Print a text to the window (false - OK, true - ERROR)
	static bool PrintWindow(DISPLAY_WINDOWS windowName, char *text);
	// Print the system information to the window (false - OK, true - ERROR)
	static void PrintSystemWindow(char *exceptionText = nullptr);
	// The main loop to enter keys on the keyboard (false - OK, true - ERROR)
	static bool InputLoop();
	// Return a pointer to the inputBuffer Array
	static char *GetAnswer();
};


#endif
