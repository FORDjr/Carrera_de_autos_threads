CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: carrera

carrera: carrera.cpp
	$(CXX) $(CXXFLAGS) carrera.cpp -o carrera -pthread

clean:
	rm -f carrera
