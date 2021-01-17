#include <cstring>
#include <string>
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
	update();
}

// Constructor with color
TERM_WINDOW::TERM_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors)
{
	background = newwin(height, width, pos_y, pos_x);
	main = derwin(background, height - 2, width - 2, 1, 1);
	box(background, 0, 0);
	// Install the color scheme for the window
	setColors(colors);
	update();
}

// Destructor
TERM_WINDOW::~TERM_WINDOW()
{
	delwin(main);
	delwin(background);
}

// Function for adding a color scheme
void TERM_WINDOW::setColors(chtype colors)
{
	wbkgd(main, colors);
	wbkgd(background, colors);
}

// This function is an analog refresh() for two windows (main and background)
void TERM_WINDOW::update()
{
	wrefresh(background);
	wrefresh(main);
}

// Clear the text in the main subwindow (wclear)
void TERM_WINDOW::clear()
{
	wclear(main);
	update();
}

// Print the text in the main subwindow (wprintw)
void TERM_WINDOW::print(char *text)
{
	wprintw(main, text);
}

// Print the text in the main subwindow (mvwprintw)
void TERM_WINDOW::print(int x, int y, char *text)
{
	mvwprintw(main, y, x, text);
}
	
// Get the main subwindow width and height
void TERM_WINDOW::getWidthAndHeight(int &width, int &height)
{
	getmaxyx(main, height, width);
}

// Return a pointer to the main subwindow
WINDOW *TERM_WINDOW::getMain()
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
	clear();
	TERM_WINDOW::~TERM_WINDOW();
}

// This function is an analog refresh() for two windows (main and background)
void MAIN_TEXT_WINDOW::update()
{
	TERM_WINDOW::update();
}

// Update the main text page
void MAIN_TEXT_WINDOW::updatePage()
{
	TERM_WINDOW::clear();
	TERM_WINDOW::print(textBuffer[currentPage]);
	TERM_WINDOW::update();
}

// Print the text in the main text window
void MAIN_TEXT_WINDOW::print(char *text)
{
	// Check the pointer to the input text
	if(text == nullptr || text[0] == 0)
		return;
	
	// Check the pointer to the textBuffer
	if(textBuffer != nullptr)
		clear();
	
	// Set the value on the first page
	currentPage = 0;
	numChr = strlen(text);
	// Get the window width and height
	int width, height;
	getWidthAndHeight(width, height);
	// Found the visual characters in the text ('\n', etc.)
	int visualChr = 0;
	for(int i = 0; i < numChr; i++)
		if(text[i] == '\n')
			visualChr += width - (i + visualChr) % width - 1;

	visualChr += numChr;
	// Get the window area
	int fullArea = width * height;
	// Processing number of pages
	numPages = visualChr / fullArea;
	if(visualChr % fullArea != 0)
		++numPages;
	
	// Pointer to the main text
	char *copyText = text;
	// Create the text buffer
	textBuffer = new char*[numPages];
	textBuffer[0] = new char[(fullArea + 1) * numPages];
	for(int i = 0; i < numPages; i++) {
		// Set the pointer to the text part
		textBuffer[i] = textBuffer[0] + (fullArea + 1) * i;
		// Get the visual characters number
		int pageText = 0, index;
		for(index = 0; index < static_cast<int>(strlen(copyText)) && (pageText + index) < fullArea; index++)
			if(copyText[index] == '\n')
				pageText += width - (index + pageText) % width - 1;
		// Copy text to the textBuffer page
		strncpy(textBuffer[i], copyText, index);
		textBuffer[i][index] = 0;
		copyText = &copyText[index];
	}
	// Print the main text page
	TERM_WINDOW::print(textBuffer[currentPage]);
}

// Erase all main text variables
void MAIN_TEXT_WINDOW::clear()
{
	// Delete the text buffer
	if(textBuffer != nullptr) {
		delete [] textBuffer[0];
		delete [] textBuffer;
		textBuffer = nullptr;
	}
	// Set zero in all main text variables
	currentPage = 0;
	numPages = 0;
	numChr = 0;
	
	TERM_WINDOW::clear();
}

// Set/Get current page
int &MAIN_TEXT_WINDOW::setCurrentPage()
{
	return currentPage;
}
// Return the number of pages
int MAIN_TEXT_WINDOW::getNumPages()
{
	return numPages;
}

// Return the number of characters
int MAIN_TEXT_WINDOW::getNumChr()
{
	return numChr;
}
