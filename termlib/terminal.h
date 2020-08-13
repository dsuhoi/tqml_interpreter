#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <ncurses.h>

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
// For the array of input characters
const int FILE_NAME_LEN = 32;

// Indent size
const int INDENT_WIDTH = 10;
const int INDENT_HEIGHT = 15;

// Height of the title window
const int HEAD_HEIGHT = 3;

// Height of the input, extra and system windows
const int WINDOW_HEIGHT = 5;

// Limit of the screen size
const int MIN_SCREEN_WIDTH = 80;
const int MIN_SCREEN_HEIGHT = 80;

// Class the main windows
class TERM_WINDOW {
private:
	WINDOW *main;		// This is the main sub window
	WINDOW *background;	// and its background window
public:
	// Basic constructor
	TERM_WINDOW(int height, int width, int pos_y, int pos_x);
	// Constructor with color
	TERM_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors);
	// Function for adding a color scheme
	void SetColors(chtype colors);
	// This function is an analog refresh() for two windows (main and background)
	void Update();
	// Clear the text in the main sub window (wclear)
	void Clear();
	// Print the text in the main sub window (wprintw)
	void Print(char *text);
	// Return a pointer to the main sub window
	WINDOW *GetMain();
};

class Terminal {
private:
	// Array of input characters
	static char inputBuffer[INPUT_BUFFER_LEN];
	// Window for displaying the title text
	static TERM_WINDOW *headWindow;
	// Window for displaying the text of the story
	static TERM_WINDOW *mainTextWindow;
	// Window for displaying the input user data
	static TERM_WINDOW *inputWindow;
	// Window for displaying the user extra information
	static TERM_WINDOW *extraWindow;
	// Window for displaying the system information
	static TERM_WINDOW *systemWindow;
	
	static int numPages;		// Number of pages in the text
	static int currentPage;		// Current page number
	static int numChr;			// Number of characters in the text
	static char fileName[FILE_NAME_LEN];	// Name of the open file
	// Private constructor
	Terminal(){}
	// Analog refresh() function for the windows
	static void UpdateWindow(DISPLAY_WINDOWS windowName);
	// Initialization of the color scheme
	static void InitAllColors();
public:
	// Initialization of terminal functions (false - OK, true - ERROR)
	static bool InitTerminal();
	// Initialization of all windows (false - OK, true - ERROR)
	static bool InitAllWindows();
	// Clear a text in the window
	static bool ClearWindow(DISPLAY_WINDOWS windowName);
	// Print a text to the window
	static bool SetWindow(DISPLAY_WINDOWS windowName, char *text);
	// Return a pointer to the inputBuffer Array
	static char *GetAnswer();
	
};

#endif
