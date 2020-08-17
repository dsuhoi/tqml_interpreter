#include "files.h"

// Read the text file (false - OK, true - ERROR)
bool Filesystem::ReadFile(char *pathName, char **readText)
{
	// File path
	fs::path pathToFile = pathName;
	// Open this file
	std::ifstream readFile (pathToFile.native());
	if(!readFile){
		return true;	
	}
	// Check the pointer to the read text and delete it
	if((*readText) != nullptr){
		delete [] (*readText);
		(*readText) = nullptr;
		std::cout << "Helllooooo!!!\n";
	}
	
	// ONLY FOR UNIX !!!
	// Get the file size
	size_t fileSize = readFile.seekg(0, std::ios::end).tellg();
	readFile.seekg(0);
	// Create the read text buffer
	(*readText) = new char [fileSize + 1];
	// Read the text file
	readFile.read((*readText), fileSize);
	(*readText)[fileSize] = 0;
	readFile.close();
	// If everything is OK, return the false value
	return false;
}
