#ifndef __FILES_H__
#define __FILES_H__

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


struct Filesystem
{
    Filesystem() = delete;
    // Read the text file (false - OK, true - ERROR)
    static bool read_file(std::string_view path_name, std::string& read_text);
    // Get the absolute path
    static void get_dir(std::string_view file_path, std::string& str);
};

#endif
