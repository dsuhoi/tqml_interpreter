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

// Print the text in the main text window
void MAIN_TEXT_WINDOW::Print(char *text)
{
	// Check the pointer to the textBuffer
	if(textBuffer != nullptr){
		return;
	}
	// Set the value on the first page
	currentPage = 0;
	int fullArea = GetArea();
	numChr = strlen(text);
	// If one page...
	if(numChr <= fullArea){
		numPages = 1;
	}
	else{
		// ...else processing number of pages
		numPages = numChr / fullArea;
		if(numChr % fullArea != 0){
			++numPages;
		}
	}
	
	// Pointer to the main text
	char *copyText = text;
	// Create the text buffer
	textBuffer = new char*[numPages];
	textBuffer[0] = new char[(fullArea + 1) * numPages];
	for(int i = 0; i < numPages; i++){
		textBuffer[i] = textBuffer[0] + (fullArea + 1) * i;
		// Copy text to the textBuffer page
		strncpy(textBuffer[i], copyText, fullArea);
		copyText = &copyText[fullArea];
	}
	
	// Print the main text page
	TERM_WINDOW::Print(textBuffer[currentPage]);
}

// Erase all main text variables
void MAIN_TEXT_WINDOW::Clear()
{
	// Delete the text buffer
	if(textBuffer != nullptr){
		delete [] textBuffer[0];
		delete [] textBuffer;
		textBuffer = nullptr;
	}
	// Set zero in all main text variables
	currentPage = 0;
	numPages = 0;
	numChr = 0;
	
	TERM_WINDOW::Clear();
}

// Set/Get current page
int &MAIN_TEXT_WINDOW::SetCurrentPage()
{
	return currentPage;
}
// Return the number of pages
int MAIN_TEXT_WINDOW::GetNumPages()
{
	return numPages;
}

// Return the number of characters
int MAIN_TEXT_WINDOW::GetNumChr()
{
	return numChr;
}
