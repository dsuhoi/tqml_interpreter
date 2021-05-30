#ifndef __TERMINAL_H__
#define __TERMINAL_H__

#include <memory>
#include <ncurses.h>
#include <string>
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
constexpr int INPUT_BUFFER_LEN = 256;

// Indent size
constexpr int INDENT_WIDTH = 10;
constexpr int INDENT_HEIGHT = 15;

// Height of the title window
constexpr int HEAD_HEIGHT = 3;

// Height and width of the help window
constexpr int HELP_HEIGHT = 9;
constexpr int HELP_WIDTH = 45;

// Height of the input, extra and system windows
constexpr int WINDOW_HEIGHT = 5;

// Limit of the screen size
constexpr int MIN_SCREEN_WIDTH = 1;
constexpr int MIN_SCREEN_HEIGHT = 1;


// Class of terminal I/O function
class Terminal
{
public:
    // Private constructor
    Terminal() = delete;
    // Initialization of terminal functions (false - OK, true - ERROR)
    static bool init_terminal();
    // Initialization of all windows (false - OK, true - ERROR)
    static bool init_all_windows();
    // End of terminal functions (false - OK, true - ERROR)
    static bool final_terminal();
    // Print a text to the window (false - OK, true - ERROR)
    static bool print_window(DISPLAY_WINDOWS window_name, std::string const& text);
    // Print the system information to the window (false - OK, true - ERROR)
    static void print_system_window(std::string const& exception_text = "");
    // Printing help window
    static void print_help_window();
    // The main loop to enter keys on the keyboard (false - OK, true - ERROR)
    static bool input_loop();
    // Return a pointer to the inputBuffer Array
    static std::string get_answer() { return input_buffer; }
private:
    // Array of input characters
    static inline char input_buffer[INPUT_BUFFER_LEN];
    
    // Window for displaying the title text
    static inline std::unique_ptr<TERM_WINDOW> head_window;
    // Window for displaying the text of the story
    static inline std::unique_ptr<MAIN_TEXT_WINDOW> main_text_window;
    // Window for displaying the input user data
    static inline std::unique_ptr<TERM_WINDOW> input_window;
    // Window for displaying the user extra information
    static inline std::unique_ptr<TERM_WINDOW> extra_window;
    // Window for displaying the system information
    static inline std::unique_ptr<TERM_WINDOW> system_window;
    // Window for displaying the help information
    static inline std::unique_ptr<TERM_WINDOW> help_window;
    
    
    // Analog refresh() function for the windows
    static void update_window(DISPLAY_WINDOWS window_name);
    // Initialization of the color scheme
    static void init_all_colors();
    // Clear a text in the window (false - OK, true - ERROR)
    static bool clear_window(DISPLAY_WINDOWS window_name);
    // Scanning input text from the input window
    static void scan_input_window();
};


#endif
