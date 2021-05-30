#ifndef __FILES_H__
#define __FILES_H__

#include <sstream>
#include <fstream>
#include <string>
#include <filesystem>


struct Filesystem
{
    Filesystem() = delete;
    // Read the text file (false - OK, true - ERROR)
    static bool read_file(std::string_view path_name, std::string& read_text)
    {
        namespace fs = std::filesystem;
        // File path
        fs::path path_to_file = path_name;
        // Open this file
        std::ifstream read_file (path_to_file.native());
        if (!read_file)
            return true;    
        // Check the pointer to the read text and delete it
        read_file.clear();
        
        // Create the read text buffer
        std::stringstream ss;
        ss << read_file.rdbuf();
        read_file.close();
        read_text = ss.str();
        // If everything is OK, return the false value
        return false;
    }
    // Get the absolute path
    static std::string get_dir(std::string_view file_path)
    {
        namespace fs = std::filesystem;
        return fs::canonical(file_path).parent_path().native() + '/';
    }
};

#endif
