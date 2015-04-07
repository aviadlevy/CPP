CC=g++ -std=c++11 -lm
CFLAGS=-c -Wall -Wextra -Wvla
EXECUTABLE=chess
SOURCES=Bishop.cpp Board.cpp chess.cpp King.cpp Knight.cpp Pawn.cpp Piece.cpp Queen.cpp Rook.cpp
SOURCES_HEADER=Bishop.hpp Board.hpp King.hpp Knight.hpp Pawn.hpp Piece.hpp Queen.hpp Rook.hpp chess.hpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

tar:
	tar cvf ex2.tar $(SOURCES) $(SOURCES_HEADER) makefile README

clean:
	rm -rf *.o
