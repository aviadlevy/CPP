CC=g++ -std=c++11 -lm
CFLAGS=-c -Wall -Wextra -Wvla
EXECUTABLE=mastermindplay mastermindsolver
SOURCES=MasterMindSolver.cpp MasterMindPlay.cpp MasterMind.cpp GameArgs.cpp
SOURCES_HEADER=MasterMindSolver.hpp MasterMindPlay.hpp MasterMind.hpp GameArgs.hpp
COMMON_OBJECTS=MasterMind.o GameArgs.o
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

mastermindsolver: $(COMMON_OBJECTS) MasterMindSolver.o
	$(CC) $(COMMON_OBJECTS) MasterMindSolver.o -o mastermindsolver

mastermindplay: $(COMMON_OBJECTS) MasterMindPlay.o
	$(CC) $(COMMON_OBJECTS) MasterMindPlay.o -o mastermindplay

.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

tar:
	tar cvf ex1.tar $(SOURCES) $(SOURCES_HEADER) makefile

clean:
	rm -rf *.o
