CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = BunnySimulator
	
all: $(TARGET)

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp
	
board.o: board.h bunny.h misc.h
	$(CXX) $(CXXFLAGS) -c board.cpp
	
bunny.o: bunny.h
	$(CXX) $(CXXFLAGS) -c bunny.cpp
	
misc.o: misc.h board.h bunny.h
	$(CXX) $(CXXFLAGS) -c misc.cpp
	
randgen.o: randgen.h
	$(CXX) $(CXXFLAGS) -c randgen.cpp
	
turn.o: turn.h board.h bunny.h misc.h
	$(CXX) $(CXXFLAGS) -c turn.cpp
	

$(TARGET): main.o board.o bunny.o misc.o randgen.o turn.o
	$(CXX) -o $(TARGET) main.o board.o bunny.o misc.o randgen.o turn.o
