#ifndef __FILES_H__
#define __FILES_H__

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


class Filesystem
{
public:
    Filesystem() = delete;
    // Read the text file (false - OK, true - ERROR)
    static bool read_file(char *path_name, char **read_text);
    // Get the absolute path
    static void get_dir(char *file_path, std::string &str);
};

#endif
