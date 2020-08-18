#include "interpreter/interpreter.h"

int main(int argc, char **argv)
{
	if(argc < 2){
		std::cout << "No text file specified.\n";
		return 1;
	}
	
	Interpreter *program = new Interpreter();
	program->Initialize(argv[1]);
	program->Process();
	delete program; 
	return 0;
}

