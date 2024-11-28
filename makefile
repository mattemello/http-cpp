all: src/server src/client src/quit

clear:
	rm -f build/* bin/*

server: src/server 

client: src/client src/quit

CPP = g++

CFLAG= -g -Wall -Wextra -Wpedantic -Wconversion

# INCLUDES= src/*.h

# COMMON_DEPS= $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CPP) $(CFLAGS) -c $< -o $@

src/server: src/serverTCP.cpp  $(COMMON_DEPS)
	$(CPP) -o bin/server src/serverTCP.cpp

src/client: src/clientTCP.cpp $(COMMON_DEPS)
	$(CPP) -o bin/client src/clientTCP.cpp

src/quit: src/quitTCP.cpp $(COMMON_DEPS)
	$(CPP) -o bin/quit src/quitTCP.cpp

