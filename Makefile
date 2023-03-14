# CXXFLAGS = -std=c++11 -g -Wall -O0
# Sungchae Park

all: runMovies

runMovies: main.cpp movies.cpp
	g++ main.cpp movies.cpp -o runMovies

clean:
	rm *.o runMovies 
