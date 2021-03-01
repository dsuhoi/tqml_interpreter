#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <ncurses.h>
#include "term_windows.hpp"

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
//  SYSTEM
};


// For the name of the open file
const int INPUT_BUFFER_LEN = 256;

// Indent size
const int INDENT_WIDTH = 10;
const int INDENT_HEIGHT = 15;

// Height of the title window
const int HEAD_HEIGHT = 3;

// Height and width of the help window
const int HELP_HEIGHT = 9;
const int HELP_WIDTH = 45;

// Height of the input, extra and system windows
const int WINDOW_HEIGHT = 5;

// Limit of the screen size
const int MIN_SCREEN_WIDTH = 1;
const int MIN_SCREEN_HEIGHT = 1;


// Class of terminal I/O function
class Terminal
{
private:
    // Array of input characters
    static char input_buffer[INPUT_BUFFER_LEN];
    
    // Window for displaying the title text
    static TERM_WINDOW *head_window;
    // Window for displaying the text of the story
    static MAIN_TEXT_WINDOW *main_text_window;
    // Window for displaying the input user data
    static TERM_WINDOW *input_window;
    // Window for displaying the user extra information
    static TERM_WINDOW *extra_window;
    // Window for displaying the system information
    static TERM_WINDOW *system_window;
    // Window for displaying the help information
    static TERM_WINDOW *help_window;
    
    // Private constructor
    Terminal() = delete;
    // Analog refresh() function for the windows
    static void update_window(DISPLAY_WINDOWS window_name);
    // Initialization of the color scheme
    static void init_all_colors();
    // Clear a text in the window (false - OK, true - ERROR)
    static bool clear_window(DISPLAY_WINDOWS window_name);
    // Scanning input text from the input window
    static void scan_input_window();
public:
    // Initialization of terminal functions (false - OK, true - ERROR)
    static bool init_terminal();
    // Initialization of all windows (false - OK, true - ERROR)
    static bool init_all_windows();
    // End of terminal functions (false - OK, true - ERROR)
    static bool final_terminal();
    // Print a text to the window (false - OK, true - ERROR)
    static bool print_window(DISPLAY_WINDOWS window_name, char *text);
    // Print the system information to the window (false - OK, true - ERROR)
    static void print_system_window(char *exception_text = nullptr);
    // Printing help window
    static void print_help_window();
    // The main loop to enter keys on the keyboard (false - OK, true - ERROR)
    static bool input_loop();
    // Return a pointer to the inputBuffer Array
    static char *get_answer();
};


#endif
