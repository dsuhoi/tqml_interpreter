#include <iostream>
#include <string>
#include <map>
#include "interpreter/interpreter.h"


// Main function
int main(int argc, char **argv)
{
	// Map to the text parts and its link
	std::map<int, TextBlock*> textParts;
	// Path to the folder with the question
	std::string mainPath;

	if(argc < 2){
		std::cout << "No text file specified.\n";
		return 1;
	}
	
	int result = 0;
	// Initialize the interpreter components
	if((result = Initialize(argv[1], textParts, mainPath)) != 0){
		return result;
	}
	// Main loop of the interpreter
	if((result = Process(textParts, mainPath)) != 0){
		EndProgram(textParts);
		return result;
	}
	// End of the program
	EndProgram(textParts);
	
	return 0;
}



