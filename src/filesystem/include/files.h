#ifndef __FILES_H__
#define __FILES_H__

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


class Filesystem {
private:
    Filesystem(){}
public:
    // Read the text file (false - OK, true - ERROR)
    static bool readFile(char *pathName, char **readText);
    // Get the absolute path
    static void getDir(char *filePath, std::string &str);
};

#endif
