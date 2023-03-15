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
bool com(const Movies& lhs, const Movies& rhs);

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
  pair<string, Movies> add;
  vector<Movies> filtered;
  Movies max;
  auto iter = listMovies.begin();
  for (int i = 2; i < argc; ++i) {
    prefix = argv[i];
    vector<Movies> filtered;
    iter = listMovies.lower_bound(prefix);
    if (iter != listMovies.end()) {
        while (prefix == *iter) {
            filtered.push_back(*iter);
            ++iter;
            if (iter == listMovies.end()) {
                break;
            }
        }
    }
    add.first = prefix;
    if (!filtered.empty()) {
        sort(filtered.begin(), filtered.end(), com);
        auto a = filtered.begin();
        while (a != filtered.end()) {
            cout << *a;
            ++a;
        }
        max = filtered.at(0);
        cout << endl;
    }
    add.second = max;
    maxFilteredMovies.push(add);
    filtered.clear();
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

/*  m = the number of prefix
    n = the number of movies
    k = the number of movies begin with the given prefix
3a.
the <1>for loop (for (i = 2; i < argc; ++i)) iterate m times
inside of the loop,
line 71 and 72 have runtime O(1) -> O(m)
line 73, the find function for the set has runtime O(nlogn) -> O(m) + O(m*nlogn)
the if statement at line 74 has O(1) and inside, there is while loop that iterate k times
inside of the while loop, the code(line 76-80) have runtime O(1) -> O(m) + O(mnlogn) + O(mk) 
line 83 has time complexity of O(1) -> O(m) + O(mnlogn) + O(mk)
the if statement at line 86 has O(1) rumtime 
and inside of the if statement, there is sort fucntion for vector
it has rumtime O(nlogn) Then there exist the while loop inside the if statement too which has the runtime O(k)
line 91-92 has O(1) runtime -> O(m) + O(mnlogn) + O(mk) + O(mnlogn + mk)
Then the code for 94 and 95 have runtime (O(1))
line 96, the clear function for the vector has runtime O(k)->O(km) -> O(m) + O(mnlogn) + O(mk) + O(mnlogn + mk)
The <1>loop ended 
The while loop at line 100 has runtime complexity O(m) and inside of the loop, the code has O(1) runtime 
*empty(), pop(), and front() for queue all have O(1)
-> O(m) + O(mnlogn) + O(mk) + O(mnlogn + mk)
So overall worst runtime is O(m) + O(mnlogn) + O(mk) + O(mnlogn + mk)
Since for any m that is greater or equal to 1 and k that, O(m) < O(mnlogn + mk) we can eliminate O(m)
->O(mnlogn) + O(mk) + O(mnlogn + mk)
Since for any m that is greater or equal to 1 and any k that is positive, for any n that is greater than 1,
mk is positive, mnlogn is positive -> 
O(mnlogn) < O(mnlogn + mk)
and 
O(mk) < O(mnlogn + mk),
The final worst-case runtime is: O(mnlogn + mk)

3b.
since the string variable to store prefix declared outside of the loop that iterate m times, it has constant space complexity: O(1)
max movie object declared before the loop, constant space complexity(1) overall:O(1) 
iterator for the set was declared before the loop, which has the constant space complexity: O(1)
pair with the string and Movies object declared before the loop also, which has the constant space complexity: O(1)
vector variable filtered stores the k elements, space complexity: O(k) + O(1)
line 86, iterator for the vector is delcared every iteration for the most outter loop,
space complexity: O(m) + O(k) + O(1)
the queue that stores the pair that composed of string and Movie object has space complexity 3*m overall: O(m) + O(k) + O(1)
On line 100, Movie object variable compare is declared, which has constant space complexity O(1)
For any m and k that is greater or equal to 1, there exist c st 
O(1) < c*O(k) 
and
O(1) < c*O(m)
Then overall: O(m) + O(k)

3c.
I mainly focused on the low runtime rather than low space complexity but maintain a reasonable space complexity.

Rather than having the nested loop that has n^2 runtime, I focused on maintaining nlogn runtime using the functions that has nlogn runtime 
such as lower_bound and sort. Since using 2 independent functions that have the same runtime insignificantly affect the runtime of algorithm, 
I first used lower_bound function to find the smallest element in the set that match the prefix. Then after adding all elements that match the prefix in vector, the sort function was used 
on the vector. In this case, the space complexity get larger due to vector but it enables the algorithm to reach lower runtime.  

The space complexity for the algorithm is in reasonable range because I did not declare the object in side of the loop every time except for the iterator for the vector that stores filtered elements from the set.
The same string, Movies, vector<Movies> variables was used throughout the <1>loop. (note. clearing the vector has worst runtime of O(n) which is < O(nlogn) so it did not affect the worst-case runtime Big-O)

Low time complexity was harder to achieve compared to the low space complexity. 
*/

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
bool com(const Movies& lhs, const Movies& rhs) {
    if (lhs.getRating() > rhs.getRating()) {
        return true;
    }
    else if (lhs.getRating() < rhs.getRating()) {
        return false;
    }
    else {
        if (lhs.getName() < rhs.getName()) {
            return true;
        }
    }
    return false;

}
