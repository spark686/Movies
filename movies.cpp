// name: Sungchae Park
// perm: 5683206
#include "movies.h"
#include <string>
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

Movies::Movies(string inName, double inRating) : name(inName), rating(inRating) {}

void Movies::setMovies(string inName, double inRating) {
    name = inName;
    rating = inRating;
}

bool operator<(const Movies& lhs, const Movies& rhs) {
    return lhs.name < rhs.name;
}

ostream & operator<<(ostream& out, const Movies movie) {
    out << movie.name << ", " << fixed << setprecision(1) << movie.rating << endl;
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

bool operator==(const Movies& lhs, const Movies& rhs) {
    if (lhs.name != rhs.name) {
        return false;
    }
    if (lhs.rating != rhs.rating) {
        return false;
    }
    return true;
}

bool operator!=(string prefix, const Movies& movie) {
    if (prefix.length() > movie.name.length()) {
        return true;
    }
    string sub = movie.name.substr(0, prefix.length());
    if (prefix == sub) {
        return false;
    }
    return true;
}


// Movies& Movies::operator=(const Movies& orig) {
//     Movies m;
//     m.name = orig.name;
//     m.rating = orig.rating;
//     return *this;
// }

double Movies::getRating() const {return rating;}

string Movies::getName() const{return name;}

