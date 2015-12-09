all: gc.cpp object.cpp object.h
	g++ -Wall -Wextra -O0 -std=gnu++11 -g -ogc gc.cpp object.cpp
