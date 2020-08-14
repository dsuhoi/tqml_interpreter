CC = g++
CFLAGS = -std=c++17 -O2 -Wall -c 
OFLAGS = -Wall -o
LIBS = -lncurses -lstdc++fs
#LIB_PACK = ar rc
OBJ = main.o terminal.o files.o

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

terminal.o: termlib/terminal.cpp termlib/terminal.h
	$(CC) $(CFLAGS) termlib/terminal.cpp

files.o: filesystem/files.cpp filesystem/files.h
	$(CC) $(CFLAGS) filesystem/files.cpp

clean:
	rm -rf tqml *.o
