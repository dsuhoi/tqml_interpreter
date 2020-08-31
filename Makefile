CC = g++
CFLAGS = -std=c++17 -O2 -Wall -c 
OFLAGS = -Wall -o
LIBS = -lncurses -lstdc++fs
LIB_PACK = ar rc
OBJ = main.o interpreter.o text_data.o regex_parser.o terminal.o term_windows.o files.o

.PHONY: tqml clean help lib

all: tqml


help:
	@echo 'clean      Delete automatically created files.'
	@echo 'lib        Create ".a" static library.'
	@echo 'help       Show this text.'

tqml: $(OBJ)
	$(CC) $(OFLAGS) tqml $(OBJ) $(LIBS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

interpreter.o: interpreter/interpreter.cpp interpreter/interpreter.h parserlib/text_data.h parserlib/regex_parser.h
	$(CC) $(CFLAGS) interpreter/interpreter.cpp

text_data.o: parserlib/text_data.cpp parserlib/text_data.h parserlib/regex_parser.h
	$(CC) $(CFLAGS) parserlib/text_data.cpp
	
regex_parser.o: parserlib/regex_parser.cpp parserlib/regex_parser.h parserlib/text_data.h
	$(CC) $(CFLAGS) parserlib/regex_parser.cpp

terminal.o: termlib/terminal.cpp termlib/terminal.h termlib/term_windows.h
	$(CC) $(CFLAGS) termlib/terminal.cpp

term_windows.o: termlib/term_windows.cpp termlib/term_windows.h
	$(CC) $(CFLAGS) termlib/term_windows.cpp

files.o: filesystem/files.cpp filesystem/files.h
	$(CC) $(CFLAGS) filesystem/files.cpp
	

clean:
	rm -rf tqml *.o

lib: $(OBJ)
	 $(LIB_PACK) libTQML.a $(OBJ)
