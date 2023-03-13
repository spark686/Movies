#include "movies.h"
#include <string>
#include <iostream>

using namespace std;

Movies::Movies(string inName, double inRating) : name(inName), rating(inRating) {}

void Movies::setMovies(string inName, double inRating) {
    name = inName;
    rating = inRating;
}

bool operator<(const Movies& lhs, const Movies& rhs) {
    if (lhs.name < rhs.name) {
        return true;
    }
    return false;
}

ostream & operator<<(ostream& out, const Movies movie) {
    out << movie.name << ", " << movie.rating << endl;
    return out;
}

bool operator==(string prefix, const Movies& movie) {
    string movieName = movie.name;
    if (prefix.length() > movieName.length()) {
        return false;
    }
    string front = movieName.substr(0, prefix.length());
    if (prefix == front) {
        return true;
    }
    return false;
}

double Movies::getRating() const {return rating;}

string Movies::getName() const{return name;}

