#include <cstring>
#include "terminal.hpp"


// Initialization of terminal functions (false - OK, true - ERROR)
bool Terminal::init_terminal()
{
    // Initialize the stdscreen
    initscr();
    // Start color processing
    start_color();
    // Initialize the basic color schemes
    init_all_colors();
    // Disable the display of characters
    noecho();
    // Disable the display of the cursor
    curs_set(0);
    // If everything is OK, return the false value
    return false;
}

// Initialization of the color scheme
void Terminal::init_all_colors()
{
    init_pair(WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
}

// End of terminal functions (false - OK, true - ERROR)
bool Terminal::final_terminal()
{
    // Delete the text buffer from the main text window
    clear_window(MAIN_TEXT);
    
    // Disable the keyboard handler
    cbreak();
    keypad(input_window->get_main(), false);
    
    // Enable the display of cursor and characters
    curs_set(1);
    echo();

    // End of the terminal
    endwin();
    // If everything is OK, return the false value
    return false;
}

// Initialization of all windows (false - OK, true - ERROR)
bool Terminal::init_all_windows()
{
    // Get the screen size
    int scr_width, scr_height;
    getmaxyx(stdscr, scr_height, scr_width);
    // Check the screen size
    if (scr_width < MIN_SCREEN_WIDTH || scr_height < MIN_SCREEN_HEIGHT)
        return true;
    // The size of the windows
    int win_width = scr_width - INDENT_WIDTH;
    int win_height = scr_height - INDENT_HEIGHT;
    
    // Initialize the title window
    int pos_center_width = (scr_width + INDENT_WIDTH)/4;
    head_window.reset(new TERM_WINDOW(HEAD_HEIGHT, win_width/2, 1, pos_center_width, COLOR_PAIR(YELLOW)));
    // Initialize the main text window
    main_text_window.reset(new MAIN_TEXT_WINDOW(win_height, win_width, HEAD_HEIGHT + 1, INDENT_WIDTH/2, COLOR_PAIR(WHITE)));
    // Initialize the input window
    input_window.reset(new TERM_WINDOW(WINDOW_HEIGHT, win_width, win_height + HEAD_HEIGHT + 1, INDENT_WIDTH/2, COLOR_PAIR(GREEN)));
    
    // Enable the key handler in the input window
    keypad(input_window->get_main(), true);
    input_window->print((char*)"Answer: ");
    input_window->update();
    
    // Initialize the user extra window
    int pos_down_height = WINDOW_HEIGHT + win_height + HEAD_HEIGHT + 1;
    extra_window.reset(new TERM_WINDOW(WINDOW_HEIGHT, win_width/2, pos_down_height, INDENT_WIDTH/2, COLOR_PAIR(BLUE)));
    // Initialize the system window
    int posRightWidth = scr_width/2;
    system_window.reset(new TERM_WINDOW(WINDOW_HEIGHT, win_width/2, pos_down_height, posRightWidth, COLOR_PAIR(CYAN)));
    
    help_window.reset(new TERM_WINDOW(HELP_HEIGHT, HELP_WIDTH, (scr_height - HELP_HEIGHT)/2, (scr_width - HELP_WIDTH)/2, COLOR_PAIR(BLUE)));
    
    // If everything is OK, return the false value
    return false;
}

// Clear a text in the window (false - OK, true - ERROR)
bool Terminal::clear_window(DISPLAY_WINDOWS window_name)
{
    switch (window_name)
	{
    case HEAD:
        head_window->clear();
        break;
    case MAIN_TEXT:
        main_text_window->clear();
        break;
    case INPUT:
        input_window->clear();
        input_window->print((char*)"Answer: ");
        input_window->update();
        break;
    case EXTRA:
        extra_window->clear();
        break;
    default:
        return true;
        break;
    };
    // If everything is OK, return the false value
    return false;
}

// Print a text to the window (false - OK, true - ERROR)
bool Terminal::print_window(DISPLAY_WINDOWS window_name, std::string_view text)
{
    if (text == nullptr)
        return true;
    
    clear_window(window_name);
    
    int head_width, head_height;
    switch (window_name)
	{
    case HEAD:
        head_window->get_width_and_height(head_width, head_height);
        head_window->print((head_width - text.size())/2, head_height - 1, text);
        head_window->update();
        break;
    case MAIN_TEXT:
        main_text_window->print(text);
        main_text_window->update();
        print_system_window();
        break;
    case INPUT:
        input_window->print(text);
        input_window->update();
        break;
    case EXTRA:
        extra_window->print(text);
        extra_window->update();
        break;
    default:
        return true;
        break;
    };
    // If everything is OK, return the false value
    return false;
}

// Print the system information to the window (false - OK, true - ERROR)
void Terminal::print_system_window(std::string const& exception_text)
{
    system_window->clear();
    WINDOW* print_window = system_window->get_main();
    int current_text_page = main_text_window->set_current_page() + 1;
    int num_text_pages = main_text_window->get_num_pages();
    int num_chr_in_text = main_text_window->get_num_chr();
    mvwprintw(print_window, 0, 1, "Page: %d / %d", current_text_page, num_text_pages);
    mvwprintw(print_window, 1, 1, "All characters: %d", num_chr_in_text);
    mvwprintw(print_window, 2, 1, "Exception: %s", exception_text.c_str());
    system_window->update();
}

// Printing help window
void Terminal::print_help_window()
{
    // Clear the help window
    help_window->clear();
    // Print the help window
    help_window->print(
    "\t\t  HELP\n"
    "LEFT or RIGHT - navigate between pages\n"
    "ENTER - entering the answer\n"
    "ESC - program exit\n"
    "  Interpreter created by DSuhoi (2020):\n"
    "https://github.com/DSuhoi/tqml_interpreter\n"
    "      <Press any key to continue...>");
    // Update the window
    help_window->update();
    // Pause
    getchar();
    // Clear the help window
    help_window->clear();
}


// Scanning input text from the input window
void Terminal::scan_input_window()
{
    // Move the cursor to the input window
    wmove(input_window->get_main(), 0,8);
    // Enable the display of the cursor
    curs_set(1);
    // Enable the display of characters
    echo();
    // Get the input text line
    wgetstr(input_window->get_main(), input_buffer.data());
    // Disable the display of characters
    noecho();
    // Disable the display of the cursor
    curs_set(0);
    // Clear this window
    clear_window(INPUT);
}


// The main loop to enter keys on the keyboard
bool Terminal::input_loop()
{
    // This is the ENTER key of the keyboard
    const int ENTER = 10;
    // ESC key of the keyboard
    const int ESC = 27;
    
    int current_text_page = main_text_window->set_current_page();
    int num_text_pages = main_text_window->get_num_pages();
    // Infinite loop
    while (1)
	{
        // Catch a key from the keyboard
        int current_button = wgetch(input_window->get_main());
        switch (current_button)
	    {
        /* // Backup keys
        case KEY_DOWN:
            break;
        case KEY_UP:
            break;
        */
        case KEY_LEFT:
            if (current_text_page > 0)
                main_text_window->set_current_page() = --current_text_page;
            // Update current text page and systemm info
            main_text_window->update_page();
            print_system_window();
            break;
        case KEY_RIGHT:
            if (current_text_page < num_text_pages - 1)
                main_text_window->set_current_page() = ++current_text_page;
            // Update current text page and system info
            main_text_window->update_page();
            print_system_window();
            break;
        case ESC:
            // End of the program
            return true;
            break;
        case ENTER:
            // Scan the input text
            scan_input_window();
            // If everything is OK, return the false value
            return false;
            break;
        default:
            break;
        };
    }
}
