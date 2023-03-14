// name: Sungchae Park
// perm number: 5683206

#ifndef MOVIES_H
#define MOVIES_H
#include <string>
#include <iostream>

using namespace std;

class Movies {
    public:
    Movies(string inName = "none", double inRating = -1.0);
    void setMovies(string inName, double inRating);
    friend bool operator<(const Movies& lhs, const Movies& rhs);
    void print() const;
    friend ostream & operator<<(ostream& out, const Movies movie);
    friend bool operator==(string prefix, const Movies& movie);
    friend bool operator!=(string prefix, const Movies& movie);
    friend bool operator==(const Movies& lhs, const Movies& rhs);
    double getRating() const;
    string getName() const;
    // Movies& operator=(const Movies& orig);
    
    private:
    string name;
    double rating;

};

#endif