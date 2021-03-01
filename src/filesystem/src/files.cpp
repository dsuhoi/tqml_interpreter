#include "files.hpp"

// Read the text file (false - OK, true - ERROR)
bool Filesystem::read_file(char *path_name, char **read_text)
{
    namespace fs = std::filesystem;
    // File path
    fs::path path_to_file = path_name;
    // Open this file
    std::ifstream read_file (path_to_file.native());
    if (!read_file)
        return true;    
    // Check the pointer to the read text and delete it
    if ((*read_text) != nullptr) {
        delete [] (*read_text);
        (*read_text) = nullptr;
    }
    
    // ONLY FOR UNIX !!!
    // Get the file size
    size_t file_size = read_file.seekg(0, std::ios::end).tellg();
    read_file.seekg(0);
    // Create the read text buffer
    (*read_text) = new char [file_size + 1];
    // Read the text file
    read_file.read((*read_text), file_size);
    (*read_text)[file_size] = 0;
    read_file.close();
    // If everything is OK, return the false value
    return false;
}

// Get the absolute path
void Filesystem::get_dir(char *file_path, std::string &str)
{
    namespace fs = std::filesystem;
    fs::path path_to_file = fs::canonical(file_path);
    str = path_to_file.parent_path().native() + '/';
}
