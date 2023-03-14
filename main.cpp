// Spring'22
// Instructor: Diba Mirza
// Student name: Sungchae Park
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <map>
#include <utility>
#include "movies.h"
using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);
bool compare(const Movies& lhs, const Movies& rhs);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
  // Create an object of a STL data-structure to store all the movies
  string line, movieName;
  double movieRating;
  set<Movies> listMovies;
  Movies newMovie;
  while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        newMovie.setMovies(movieName, movieRating);
        listMovies.insert(newMovie);
        // Use std::string movieName and double movieRating
        // to construct your Movie objects
        // cout << movieName << " has rating " << movieRating << endl;
        // insert elements into your data structure
  }

  movieFile.close();

  if (argc == 2){
        //print all the movies in ascending alphabetical order of movie names
        // cout << "Testing part2" << endl;
        set<Movies>::iterator it = listMovies.begin();
        while (it != listMovies.end()) {
            cout << *it;
            ++it;
        }
        return 0;
  }

  //  For each prefix,
  // set.lower_bound("");
  string prefix;
  queue<pair<string,Movies>> maxFilteredMovies;
  Movies temp;
  string name;
  double r;
  pair<string, Movies> add;
  vector<Movies> filtered;
  for (int i = 2; i < argc; ++i) {
    //setting prefix
    prefix = argv[i];
    vector<Movies> filtered;

    auto iter = listMovies.lower_bound(prefix);
    if (iter != listMovies.end()) {
        while (prefix == *iter) {
            filtered.push_back(*iter);
            ++iter;
            if (iter == listMovies.end()) {
                break;
            }
        }

    }
    // while (iter != listMovies.end()) {
    //     if (temp != *iter) {
    //         break;
    //     }
    //     temp = *iter;
    //     cout << temp;
    //     filtered.push(temp);
    //     ++iter;
    // }
    add.first = prefix;
    Movies max;
    if (!filtered.empty()) {
        sort(filtered.begin(), filtered.end(), compare);
        for (int8_t i = 0; i < filtered.size(); ++i) {
            cout << filtered.at(i);
        }
        max = filtered.at(0);
        cout << endl;
        // cout << max << "After" << endl;
    }
    // cout << max << "1" << endl;
    add.second = max;
    maxFilteredMovies.push(add);
    // cout << "TEsting" << endl;
    // cout << maxFilteredMovies.front().second << endl;

    // queue<Movies> filteredMovies;
    // while (iter != listMovies.end()) {
    //     temp = *iter;
    //     filteredMovies.push(temp);
    //     listMovies.erase(temp);
    //     iter = listMovies.find(prefix);
    // }
    // pair<string, Movies> add;
    // add.first = prefix;
    // if (filteredMovies.empty()) {
    //     Movies a;
    //     add.second = a;
    // }
    // else {
    //     max = filteredMovies.front();
    //     while (!filteredMovies.empty()) {
    //         temp = filteredMovies.front();
    //         if (max.getRating() < temp.getRating()) {
    //             max = temp;
    //         }
    //         listMovies.insert(temp);
    //         filteredMovies.pop();
    //     }
    //     add.second = max;
    // }
    // maxFilteredMovies.push(add);
}

Movies compare;
while (!maxFilteredMovies.empty()) {
    compare = maxFilteredMovies.front().second;
    if (compare.getRating() < 0) {
        cout << "No movies found with prefix "<< maxFilteredMovies.front().first << endl << endl;

    }
    else {
        cout << "Best movie with prefix " << maxFilteredMovies.front().first << " is: " << compare.getName() << " with rating " << std::setprecision(1) << compare.getRating() << endl;

    }
    maxFilteredMovies.pop();
}


  

  //  Find all movies that have that prefix and store them in an appropriate data structure
  //  If no movie with that prefix exists print the following message
//   cout << "No movies found with prefix "<<"<replace with prefix>" << endl << endl;

//   //  For each prefix,
//   //  Print the highest rated movie with that prefix if it exists.
//   cout << "Best movie with prefix " << "<replace with prefix>" << " is: " << "replace with movie name" << " with rating " << std::fixed << std::setprecision(1) << "replace with movie rating" << endl;

  return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    if (line.length() <= 0) return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < line.length(); i++){
        if(flag) tempRating += line[i];
        else if(line[i]==','&& line[0]!='"') flag = true;
        else {
            if(i==0 && line[0]=='"') continue;
            if(line[i]=='"'){ i++; flag=true; continue;}
            movieName += line[i];
        }
    }
    
    movieRating = stod(tempRating);
    return true;
}
bool compare(const Movies& lhs, const Movies& rhs) {
    if (lhs.getRating() == rhs.getRating()) {
        if (lhs.getName() < rhs.getName()) {
            return true;
        }
        else {
            return false;
        }
    }
    if (lhs.getRating() > rhs.getRating()) {
        return true;
    }
    return false;
}
