#ifndef __TERM_WINDOWS_H__
#define __TERM_WINDOWS_H__

#include <ncurses.h>

// Class the main windows
class TERM_WINDOW
{
private:
    WINDOW *main;       // This is the main subwindow
    WINDOW *background; // and its background window
public:
    // Basic constructor
    TERM_WINDOW(int height, int width, int pos_y, int pos_x);
    // Constructor with color
    TERM_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors);
    // Virtual destructor
    virtual ~TERM_WINDOW();
    // Function for adding a color scheme
    void set_colors(chtype colors);
    // This function is an analog refresh() for two windows (main and background)
    virtual void update();
    // Clear the text in the main subwindow (wclear)
    virtual void clear();
    // Print the text in the main subwindow (wprintw)
    virtual void print(char *text);
    // Print the text in the main subwindow (mvwprintw)
    void print(int x, int y, char *text);
    // Get the main subwindow width and height
    void get_width_and_height(int &width, int &height);
    // Return a pointer to the main subwindow
    WINDOW *get_main();
};


// Class of main text window
class MAIN_TEXT_WINDOW : public TERM_WINDOW
{
private:
    char **text_buffer;   // Pointer to the main text buffer
    int num_pages;       // Number of pages in the text
    int current_page;    // Current page number
    int num_chr;         // Number of characters in the text
public:
    // Constructors
    MAIN_TEXT_WINDOW(int height, int width, int pos_y, int pos_x);
    MAIN_TEXT_WINDOW(int height, int width, int pos_y, int pos_x, chtype colors);
    // Destructor
    ~MAIN_TEXT_WINDOW();
    
    // This function is an analog refresh() for two windows (main and background)
    void update() override;
    // Update the main text page
    void update_page();
    // Erase all main text variables
    void clear() override;
    // Print the text in the main text window
    void print(char *text) override;
    // Set/Get current page
    int &set_current_page();
    // Return the number of pages
    int get_num_pages();
    // Return the number of characters
    int get_num_chr();
};


#endif
