#ifndef __FILES_H__
#define __FILES_H__

#include <iostream>
#include <fstream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class Filesystem {
private:
	Filesystem(){}
public:
	// Read the text file (false - OK, true - ERROR)
	static bool ReadFile(char *pathName, char *readText);
};

#endif
