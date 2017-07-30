CXX = g++
CXXFLAGS = -Wall -std=c++11 -c
TARGET = BunnySimulator

all: $(TARGET)

main.o: main.cpp board.h bunny.h misc.h randgen.o turn.o
	$(CXX) $(CXXFLAGS) main.cpp
	
board.o: board.cpp board.h bunny.h misc.h
	$(CXX) $(CXXFLAGS) board.cpp
	
bunny.o: bunny.cpp bunny.h
	$(CXX) $(CXXFLAGS) bunny.cpp
	
misc.o: misc.cpp misc.h board.h bunny.h
	$(CXX) $(CXXFLAGS) misc.cpp
	
randgen.o: randgen.cpp randgen.h
	$(CXX) $(CXXFLAGS) randgen.cpp
	
turn.o: turn.cpp turn.h board.h bunny.h misc.h
	$(CXX) $(CXXFLAGS) turn.cpp
	

$(TARGET): main.o board.o bunny.o misc.o randgen.o turn.o
	$(CXX) -Wall -o $(TARGET) main.o board.o bunny.o misc.o randgen.o turn.o

