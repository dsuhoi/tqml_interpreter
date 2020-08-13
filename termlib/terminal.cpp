#include <cstring>
#include "terminal.h"


// Defining static variables of the Terminal class
char Terminal::inputBuffer[INPUT_BUFFER_LEN] = "";
char **Terminal::textBuffer = nullptr;

TERM_WINDOW *Terminal::headWindow = nullptr;
TERM_WINDOW *Terminal::mainTextWindow = nullptr;
TERM_WINDOW *Terminal::inputWindow = nullptr;
TERM_WINDOW *Terminal::extraWindow = nullptr;
TERM_WINDOW *Terminal::systemWindow = nullptr;

int Terminal::numPages = 0;
int Terminal::currentPage = 0;
int Terminal::numChr = 0;


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

// End of terminal functions (false - OK, true - ERROR)
bool Terminal::FinalTerminal()
{
	cbreak();
	keypad(inputWindow->GetMain(), false);
	ClearWindow(MAIN_TEXT);
	
	delete headWindow;
	delete mainTextWindow;
	delete extraWindow;
	delete systemWindow;
	delete inputWindow;
	
	endwin();
	
	return false;
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
	if(!(headWindow = new TERM_WINDOW(HEAD_HEIGHT, winWidth/2, 1, posCenterWidth, COLOR_PAIR(YELLOW)))){
		return true;
	}
	// Initialize the main text window
	if(!(mainTextWindow = new TERM_WINDOW(winHeight, winWidth, HEAD_HEIGHT + 1, INDENT_WIDTH/2, COLOR_PAIR(WHITE)))){
		return true;
	}
	// Initialize the input window
	if(!(inputWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth, winHeight + HEAD_HEIGHT + 1, INDENT_WIDTH/2, COLOR_PAIR(GREEN)))){
		return true;
	}
	
	// Enable the key handler in the input window
	keypad(inputWindow->GetMain(), true);
	
	// Initialize the user extra window
	int posDownHeight = WINDOW_HEIGHT + winHeight + HEAD_HEIGHT + 1;
	if(!(extraWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth/2, posDownHeight, INDENT_WIDTH/2, COLOR_PAIR(BLUE)))){
		return true;
	}
	// Initialize the system window
	int posRightWidth = scrWidth/2;
	if(!(systemWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth/2, posDownHeight, posRightWidth, COLOR_PAIR(CYAN)))){
		return true;
	}
	
	// Сlear the array of input characters
	memset(inputBuffer, 0, INPUT_BUFFER_LEN);
	
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
		EraseMainText();
		break;
	case INPUT:
		inputWindow->Clear();
		inputWindow->Print((char*)"Answer: ");
		inputWindow->Update();
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
bool Terminal::PrintWindow(DISPLAY_WINDOWS windowName, char *text)
{
	switch(windowName){
	case HEAD:
		headWindow->Print(text);
		headWindow->Update();
		break;
	case MAIN_TEXT:
		SetInfoAboutMainText(text);
		UpdateMainTextPage();
		break;
	case INPUT:
		inputWindow->Print(text);
		inputWindow->Update();
		break;
	case EXTRA:
		extraWindow->Print(text);
		extraWindow->Update();
		break;
	default:
		return true;
		break;
	};
	// If everything is OK, return the false value
	return false;
}

// Print the system information to the window (false - OK, true - ERROR)
void Terminal::PrintSystemWindow(char *exceptionText)
{
	systemWindow->Clear();
	WINDOW *printWindow = systemWindow->GetMain();
	mvwprintw(printWindow, 0, 1, "Page: %d / %d", currentPage + 1, numPages);
	mvwprintw(printWindow, 1, 1, "All characters: %d", numChr);
	mvwprintw(printWindow, 2, 1, "Exception: %s", exceptionText);
	systemWindow->Update();
}

// Setting information about the input text to the main window (false - OK, true - ERROR)
bool Terminal::SetInfoAboutMainText(char *text)
{
	// Check the pointer to the textBuffer
	if(textBuffer != nullptr){
		return true;
	}
	// Set the value on the first page
	currentPage = 0;
	int fullArea = mainTextWindow->GetArea();
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
	
	// If everything is OK, return the false value
	return false;
}

// Update the main text page
void Terminal::UpdateMainTextPage()
{
	mainTextWindow->Clear();
	mainTextWindow->Print(textBuffer[currentPage]);
	mainTextWindow->Update();
}

// Erase all main text variables
void Terminal::EraseMainText()
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
}

// The main loop to enter keys on the keyboard
void Terminal::InputLoop()
{
	// This is the ENTER key of the keyboard
	const int ENTER = 10;
	// Infinite loop
	while(1){
		// Catch a key from the keyboard
		int currentButton = wgetch(inputWindow->GetMain());
		switch(currentButton){
		/* // Backup keys
		case KEY_DOWN:
			break;
		case KEY_UP:
			break;
		*/
		case KEY_LEFT:
			if(currentPage > 0){
				--currentPage;
			}
			// Update current page
			UpdateMainTextPage();
			PrintSystemWindow();
			break;
		case KEY_RIGHT:
			if(currentPage < numPages - 1){
				++currentPage;
			}
			// Update current page
			UpdateMainTextPage();
			PrintSystemWindow();
			break;
		case ENTER:
			// Сlear the array of input characters
			memset(inputBuffer, 0, INPUT_BUFFER_LEN);
			// Move the cursor to the input window
			wmove(inputWindow->GetMain(), 0,8);
			// Enable the display of the cursor
			curs_set(1);
			// Enable the display of characters
			echo();
			// Get the input text line
			wgetstr(inputWindow->GetMain(), inputBuffer);
			// Disable the display of characters
			noecho();
			// Disable the display of the cursor
			curs_set(0);
			// Clear this window
			ClearWindow(INPUT);
			// Return from the function
			return;
			break;
		default:
			break;
		};
	}
}

// Getting a pointer to the text buffer
char *Terminal::GetTextBuffer(const int _page)
{
	if(_page < 0 || numPages <= _page){
		return nullptr;
	}
	return textBuffer[_page];
}

// Return a pointer to the inputBuffer Array
char *Terminal::GetAnswer()
{
	return inputBuffer;
}
