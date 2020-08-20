#include <cstring>
#include "terminal.h"


// Defining static variables of the Terminal class
char Terminal::inputBuffer[INPUT_BUFFER_LEN] = "";
// Terminal windows
TERM_WINDOW *Terminal::headWindow = nullptr;
MAIN_TEXT_WINDOW *Terminal::mainTextWindow = nullptr;
TERM_WINDOW *Terminal::inputWindow = nullptr;
TERM_WINDOW *Terminal::extraWindow = nullptr;
TERM_WINDOW *Terminal::systemWindow = nullptr;
TERM_WINDOW *Terminal::helpWindow = nullptr;

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
	// Delete the text buffer from the main text window
	ClearWindow(MAIN_TEXT);
	
	// Disable the keyboard handler
	cbreak();
	keypad(inputWindow->GetMain(), false);
	
	// Enable the display of cursor and characters
	curs_set(1);
	echo();
	
	// Delete all windows
	if(headWindow != nullptr){
		delete headWindow;
	}
	if(mainTextWindow != nullptr){
		delete mainTextWindow;
	}
	if(extraWindow != nullptr){
		delete extraWindow;
	}
	if(systemWindow != nullptr){
		delete systemWindow;
	}
	if(inputWindow != nullptr){
		delete inputWindow;
	}
	if(helpWindow != nullptr){
		delete helpWindow;
	}
	
	// End of the terminal
	endwin();
	
	// If everything is OK, return the false value
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
	if(!(mainTextWindow = new MAIN_TEXT_WINDOW(winHeight, winWidth, HEAD_HEIGHT + 1, INDENT_WIDTH/2, COLOR_PAIR(WHITE)))){
		return true;
	}
	// Initialize the input window
	if(!(inputWindow = new TERM_WINDOW(WINDOW_HEIGHT, winWidth, winHeight + HEAD_HEIGHT + 1, INDENT_WIDTH/2, COLOR_PAIR(GREEN)))){
		return true;
	}
	
	// Enable the key handler in the input window
	keypad(inputWindow->GetMain(), true);
	inputWindow->Print((char*)"Answer: ");
	inputWindow->Update();
	
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
	
	
	if(!(helpWindow = new TERM_WINDOW(HELP_HEIGHT, HELP_WIDTH, (scrHeight - HELP_HEIGHT)/2, (scrWidth - HELP_WIDTH)/2, COLOR_PAIR(BLUE)))){
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
	if(text == nullptr){
		return true;
	}
	
	ClearWindow(windowName);
	
	int headWidth, headHeight;
	switch(windowName){
	case HEAD:
		headWindow->GetWidthAndHeight(headWidth, headHeight);
		headWindow->Print((headWidth - strlen(text))/2, headHeight - 1, text);
		headWindow->Update();
		break;
	case MAIN_TEXT:
		mainTextWindow->Print(text);
		mainTextWindow->Update();
		PrintSystemWindow();
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
	int currentTextPage = mainTextWindow->SetCurrentPage() + 1;
	int numTextPages = mainTextWindow->GetNumPages();
	int numChrInText = mainTextWindow->GetNumChr();
	mvwprintw(printWindow, 0, 1, "Page: %d / %d", currentTextPage, numTextPages);
	mvwprintw(printWindow, 1, 1, "All characters: %d", numChrInText);
	mvwprintw(printWindow, 2, 1, "Exception: %s", exceptionText);
	systemWindow->Update();
}

// Printing help window
void Terminal::PrintHelpWindow()
{
	// Clear the help window
	helpWindow->Clear();
	// Print the help window
	helpWindow->Print((char*)
	"\t\t  HELP\n"
	"LEFT or RIGHT - navigate between pages\n"
	"ENTER - entering the answer\n"
	"ESC - program exit\n"
	"  Interpreter created by DSuhoi (2020):\n"
	"https://github.com/DSuhoi/tqml_interpreter\n"
	"      <Press any key to continue...>");
	// Update the window
	helpWindow->Update();
	// Pause
	getchar();
	// Clear the help window
	helpWindow->Clear();
}


// Scanning input text from the input window
void Terminal::ScanInputWindow()
{
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
}


// The main loop to enter keys on the keyboard
bool Terminal::InputLoop()
{
	// This is the ENTER key of the keyboard
	const int ENTER = 10;
	// ESC key of the keyboard
	const int ESC = 27;
	
	int currentTextPage = mainTextWindow->SetCurrentPage();
	int numTextPages = mainTextWindow->GetNumPages();
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
			if(currentTextPage > 0){
				mainTextWindow->SetCurrentPage() = --currentTextPage;
			}
			// Update current text page and systemm info
			mainTextWindow->UpdatePage();
			PrintSystemWindow();
			break;
		case KEY_RIGHT:
			if(currentTextPage < numTextPages - 1){
				mainTextWindow->SetCurrentPage() = ++currentTextPage;
			}
			// Update current text page and system info
			mainTextWindow->UpdatePage();
			PrintSystemWindow();
			break;
		case ESC:
			// End of the program
			return true;
			break;
		case ENTER:
			// Scan the input text
			ScanInputWindow();
			// If everything is OK, return the false value
			return false;
			break;
		default:
			break;
		};
	}
}

// Return a pointer to the inputBuffer Array
char *Terminal::GetAnswer()
{
	return inputBuffer;
}
