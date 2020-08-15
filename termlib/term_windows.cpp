#include <cstring>
#include "term_windows.h"


// Basic constructor
TERM_WINDOW::TERM_WINDOW(int height, int width, int pos_y, int pos_x)
{
	// Create the background window
	background = newwin(height, width, pos_y, pos_x);
	// Create the main subwindow
	main = derwin(background, height - 2, width - 2, 1, 1);
	// Create the box frame around the main subwindow
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

// Destructor
TERM_WINDOW::~TERM_WINDOW()
{
	delete main;
	delete background;
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

// Clear the text in the main subwindow (wclear)
void TERM_WINDOW::Clear()
{
	wclear(main);
	Update();
}

// Print the text in the main subwindow (wprintw)
void TERM_WINDOW::Print(char *text)
{
	wprintw(main, text);
}

// Return the main subwindow area
int TERM_WINDOW::GetArea()
{
	// Get the main subwindow size
	int winWidth, winHeight;
	getmaxyx(main, winHeight, winWidth);
	return winWidth * winHeight;
}

// Return a pointer to the main subwindow
WINDOW *TERM_WINDOW::GetMain()
{
	return main;
}



// Basic constructor
MAIN_TEXT_WINDOW::MAIN_TEXT_WINDOW(int height, int width, int pos_y, int pos_x) : 
TERM_WINDOW(height, width, pos_y, pos_x)
{
	numPages = 0;
	currentPage = 0;
	numChr = 0;
	textBuffer = nullptr;
}

// Constructor with color
MAIN_TEXT_WINDOW::MAIN_TEXT_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors) :
TERM_WINDOW(height, width, pos_y, pos_x, colors)
{
	numPages = 0;
	currentPage = 0;
	numChr = 0;
	textBuffer = nullptr;
}

// Destructor
MAIN_TEXT_WINDOW::~MAIN_TEXT_WINDOW()
{
	TERM_WINDOW::~TERM_WINDOW();
	Clear();
}

// This function is an analog refresh() for two windows (main and background)
void MAIN_TEXT_WINDOW::Update()
{
	TERM_WINDOW::Update();
}

// Update the main text page
void MAIN_TEXT_WINDOW::UpdatePage()
{
	TERM_WINDOW::Clear();
	TERM_WINDOW::Print(textBuffer[currentPage]);
	TERM_WINDOW::Update();
}
