#include "terminal.h"

// Basic constructor
TERM_WINDOW::TERM_WINDOW(int height, int width, int pos_y, int pos_x)
{
	// Create the background window
	background = newwin(height, width, pos_y, pos_x);
	// Create the main sub window
	main = derwin(background, height - 2, width - 2, 1, 1);
	// Create the box frame around the main sub window
	box(background, 0, 0);
	// refresh background and main
	Update();
}

// Constructor with color
TERM_WINDOW::TERM_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors)
{
	background = newwin(height, width, pos_y, pos_x);
	main = derwin(background, height - 2, width - 2, 1, 1);
	box(background, 0, 0);
	// Install the color scheme for the window
	SetColors(colors);
	Update();
}

// Function for adding a color scheme
void TERM_WINDOW::SetColors(chtype colors)
{
	wbkgd(main, colors);
	wbkgd(background, colors);
}

// This function is an analog refresh() for two windows (main and background)
void TERM_WINDOW::Update()
{
	wrefresh(background);
	wrefresh(main);
}

// Clear the text in the main sub window (wclear)
void TERM_WINDOW::Clear()
{
	wclear(main);
	Update();
}

// Return a pointer to the main sub window
WINDOW *TERM_WINDOW::GetMain()
{
	return main;
}



// Initialization of terminal functions (false - OK, true - ERROR)
bool Terminal::InitTerminal()
{
	// Initialize the stdscreen
	initscr();
	// Start color processing
	start_color();
	// Initialize the basic color schemes
	InitAllColors();
	// Disable the display of characters
	noecho();
	// Disable the delay while the getch() is running
	nodelay(stdscr,true);
	// Enable the key handler
	keypad(stdscr,true);
	// Disable the display of the cursor
	curs_set(0);
	// If everything is OK, return the false value
	return false;
}

// Initialization of the color scheme
void Terminal::InitAllColors()
{
	init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);
	init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
	
}

// Initialization of all windows (false - OK, true - ERROR)
bool Terminal::InitAllWindows()
{
	// Get the screen size
	int scrWidth, scrHeight;
	getmaxyx(stdscr, scrHeight, scrWidth);
	// Check the screen size
	if(scrWidth < MIN_SCREEN_WIDTH || scrHeight < MIN_SCREEN_HEIGHT){
		return true;
	}
	// The size of the windows
	int winWidth = scrWidth - INDENT_WIDTH;
	int winHeight = scrHeight - INDENT_HEIGHT;
	
	// Initialize the title window
	int posCenterWidth = (scrWidth + INDENT_WIDTH)/4;
	if(!(headWindow = new TERM_WINDOW(HEAD_HEIGHT, winWidth, 1, posCenterWidth, COLOR_PAIR(YELLOW)))){
		return true;
	}
	// Initialize the main text window
	const int POS_LEFT_WIDTH = INDENT_HEIGHT/2;
	if(!(mainTextWindow = new TERM_WINDOW(winHeight, winWidth, HEAD_HEIGHT + 1, POS_LEFT_WIDTH, COLOR_PAIR(WHITE)))){
		return true;
	}
	// Initialize the input window
	if(!(inputWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth, winHeight + HEAD_HEIGHT + 1, POS_LEFT_WIDTH, COLOR_PAIR(GREEN)))){
		return true;
	}
	// Initialize the user extra window
	int posDownHeight = WINDOW_HEIGHT + winHeight + HEAD_HEIGHT + 1;
	if(!(extraWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth/2, posDownHeight, POS_LEFT_WIDTH, COLOR_PAIR(BLUE)))){
		return true;
	}
	// Initialize the system window
	int posRightWidth = scrWidth/2;
	if(!(systemWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth/2, posDownHeight, posRightWidth, COLOR_PAIR(CYAN)))){
		return true;
	}
	// If everything is OK, return the false value
	return false;
}

// Clear a text in the window (false - OK, true - ERROR)
bool Terminal::ClearWindow(DISPLAY_WINDOWS windowName)
{
	switch(windowName){
	case HEAD:
		headWindow->Clear();
		break;
	case MAIN_TEXT:
		mainTextWindow->Clear();
		break;
	case INPUT:
		inputWindow->Clear();
		break;
	case EXTRA:
		extraWindow->Clear();
		break;
	default:
		return true;
		break;
	};
	// If everything is OK, return the false value
	return false;
}

// Print a text to the window (false - OK, true - ERROR)
bool Terminal::SetWindow(DISPLAY_WINDOWS windowName, char *text)
{
	switch(windowName){
	case HEAD:
		wprintw(headWindow->GetMain(), text);
		break;
	case MAIN_TEXT:
		wprintw(mainTextWindow->GetMain(), text);
		break;
	case INPUT:
		wprintw(inputWindow->GetMain(), text);
		break;
	case EXTRA:
		wprintw(extraWindow->GetMain(), text);
		break;
	default:
		return true;
		break;
	};
	// If everything is OK, return the false value
	return false;
}

// Return a pointer to the inputBuffer Array
char *Terminal::GetAnswer()
{
	wscanw(inputWindow->GetMain(), "%s", inputBuffer);
	return inputBuffer;
}
