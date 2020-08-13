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


