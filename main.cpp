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
line 71 and 72 have runtime O(1)
line 73, the upper_bound for the set has runtime O(logn)
the if statement at line 74 has O(1) and inside, there is while loop that iterate k times O(k)
inside of the while loop, the code(line 76-80) have runtime O(1)
while loop for line 74 ended.
line 83 has time complexity of O(1) 
line 84 if statement has time complexity of O(1) <2>
inside of the if statement<2>,
there is sort fucntion for vector has rumtime O(klogk) runtime. 
line 86 has O(1) time complexity in <2>
Then there exist the while loop in <2> which has the runtime O(k)
line 91-92 has O(1) runtime 
<2> ended 
Then the code for 94 and 95 have runtime (O(1))
line 96, the clear function for the vector has runtime O(k)
The <1>loop ended 
The runtime for <1> is O(m(O(1) + O(logn) + O(k) + O(klogk)))
which equates to O(m + mlogn + mk + mklogk)
Since O(m) <= O(mk) for any k greater or equal to 1,
overall runtime of <1> is O(mlogn + mk + mklogk)

line 99 has O(1) complexity


The while loop at line 100 has runtime complexity O(m) and inside of the loop, the code has O(1) runtime 
*empty(), pop(), and front() for queue all have O(1)
The while loop overall has runtime O(m)

Then overall, O(mlogn + mk + mklogk) + O(1) + O(m)
Since O(1) <= O(mk) for any m,k that are greater or equal to 1
and O(m) <= O(mk) for any k that is greater or equal to 1,
The final runtime of the program is O(mlogn + mk + mklogk)

3b.
line 64-68, the declaration of string,queue, pair, vector, Movies object, and iterator for set all have space complexity of O(1)
The vector stores k elements but it is cleared out at the end of the every iteration
so it has the space complexity of O(k)
line 85, there is declaration of vector iterator inside of while loop that iterates m times so
it has the space complexity of O(m)
The queue takes m number of pairs so it has space complexity of O(m)
So overall space complexity is O(k + m)



3c.
I mainly focused on the low runtime rather than low space complexity but maintain a reasonable space complexity.

Rather than having the nested loop that has n^2 runtime to find the all elements that matches the prefixes
I focused on maintaining the low runtime using the low bound function for set container which has time complexity of 
O(logn). 
Also, to sort the vector that contains the k elements, I used the sort function for vector class which 
has runtime of O(klogk) instead of using the nested loop which has time complexity of O(k^2).

The queue front,empty, and pop functions have time complexity of O(1) which is the lowest time complexity that it can achieve.

________
  
The space complexity for the algorithm is in reasonable range because I did not declare the object in side of the loop every time except for the iterator for the vector that stores filtered elements from the set.
The same string, Movies, vector<Movies> variables was used throughout the <1>loop. (note. clearing the vector has worst runtime of O(k) which is < O(klogk) so it does not affect the worst-case runtime Big-O)

There is some trade off between the time complexity and space complexity. With O(k^2), there exist algorithm for evaluating the prefix and sorting exist such that 
it does not require the filtered vector.
But since I focused more on the low time complexity, the vector was used to store the filtered elements. Then sorted using the vector sort function which has O(klogk) time complexity.

In general, low time complexity was harder to achieve compared to the low space complexity. 
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
