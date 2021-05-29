#include <cstring>
#include <string>
#include "term_windows.hpp"


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
    set_colors(colors);
    update();
}

// Destructor
TERM_WINDOW::~TERM_WINDOW()
{
    delwin(main);
    delwin(background);
}

// Function for adding a color scheme
void TERM_WINDOW::set_colors(chtype colors)
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
void TERM_WINDOW::print(std::string_view text)
{
    wprintw(main, std::string(text).c_str());
}

// Print the text in the main subwindow (mvwprintw)
void TERM_WINDOW::print(int x, int y, std::string_view text)
{
    mvwprintw(main, y, x, std::string(text).c_str());
}
    
// Get the main subwindow width and height
void TERM_WINDOW::get_width_and_height(int &width, int &height)
{
    getmaxyx(main, height, width);
}

// Return a pointer to the main subwindow
WINDOW *TERM_WINDOW::get_main()
{
    return main;
}



// Basic constructor
MAIN_TEXT_WINDOW::MAIN_TEXT_WINDOW(int height, int width, int pos_y, int pos_x) : 
TERM_WINDOW(height, width, pos_y, pos_x)
{
}

// Constructor with color
MAIN_TEXT_WINDOW::MAIN_TEXT_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors) :
TERM_WINDOW(height, width, pos_y, pos_x, colors)
{
    num_pages = 0;
    current_page = 0;
    num_chr = 0;
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
void MAIN_TEXT_WINDOW::update_page()
{
    TERM_WINDOW::clear();
    TERM_WINDOW::print(text_buffer[current_page]);
    TERM_WINDOW::update();
}

// Print the text in the main text window
void MAIN_TEXT_WINDOW::print(std::string_view text)
{
    // Check the pointer to the input text
    if (text.empty())
        return;
    
    // Check the pointer to the text_buffer
    text_buffer.clear();
    
    // Set the value on the first page
    current_page = 0;
    num_chr = text.size();
    // Get the window width and height
    int width, height;
    get_width_and_height(width, height);
    // Found the visual characters in the text ('\n', etc.)
    int visual_chr = 0;
    for (int i = 0; i < num_chr; ++i)
        if (text[i] == '\n')
            visual_chr += width - (i + visual_chr) % width - 1;

    visual_chr += num_chr;
    // Get the window area
    int full_area = width * height;
    // Processing number of pages
    num_pages = visual_chr / full_area;
    if (visual_chr % full_area != 0)
        ++num_pages;
    
    // Pointer to the main text
    std::string copy_text(text);
    // Create the text buffer
    for (int i = 0; i < num_pages; ++i)
    {
        // Get the visual characters number
        int page_text = 0, index;
        for (index = 0; index < copy_text.size() && (page_text + index) < full_area; ++index)
            if (copy_text[index] == '\n')
                page_text += width - (index + page_text) % width - 1;
        // Copy text to the text_buffer page
        text_buffer[i] = std::string(copy_text, index);
        text_buffer[i][index] = 0;
        copy_text = &copy_text[index];
    }
    // Print the main text page
    TERM_WINDOW::print(text_buffer[current_page]);
}

// Erase all main text variables
void MAIN_TEXT_WINDOW::clear()
{
    // Delete the text buffer
    text_buffer.clear();
    // Set zero in all main text variables
    current_page = 0;
    num_pages = 0;
    num_chr = 0;
    
    TERM_WINDOW::clear();
}

// Set/Get current page
int &MAIN_TEXT_WINDOW::set_current_page()
{
    return current_page;
}
// Return the number of pages
int MAIN_TEXT_WINDOW::get_num_pages()
{
    return num_pages;
}

// Return the number of characters
int MAIN_TEXT_WINDOW::get_num_chr()
{
    return num_chr;
}
