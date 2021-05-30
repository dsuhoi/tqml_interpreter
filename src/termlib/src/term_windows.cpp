
#include <cstring>
#include <iterator>
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
void TERM_WINDOW::print(std::string const& text)
{
    wprintw(main, text.c_str());
}

// Print the text in the main subwindow (mvwprintw)
void TERM_WINDOW::print(int x, int y, std::string const& text)
{
    mvwprintw(main, y, x, text.c_str());
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
void MAIN_TEXT_WINDOW::print(std::string const& text)
{
    // Check the pointer to the input text
    if (text.empty())
        return;
    
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
    std::string copy_text = text;
    for (int i = 0; i < num_pages; ++i)
    {
        // Get the visual characters number
        size_t index = 0;
        for (int page_text = 0; index < copy_text.size() && (page_text + index) < full_area; ++index)
            if (copy_text[index] == '\n')
                page_text += width - (index + page_text) % width - 1;
        // Copy text to the text_buffer page
        text_buffer.push_back({copy_text.c_str(), index});
        copy_text = copy_text.substr(index, copy_text.size());
    }
    // Print the main text page
    TERM_WINDOW::print(text_buffer[current_page]);
}

// Erase all main text variables
void MAIN_TEXT_WINDOW::clear()
{
    text_buffer.clear();
    // Set zero in all main text variables
    current_page = 0;
    num_pages = 0;
    num_chr = 0;
    
    TERM_WINDOW::clear();
}
