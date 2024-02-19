// TODO: remove and replace this file header comment
// This is a .cpp file you will edit and turn in.

// Remove starter comments and add your own
// comments on each function and on complex code sections.

#include "search.h"
using namespace std;


bool testCleanToken() {
    string ans;
    int pass = 0, fail = 0;

    // ans == cleanToken(".hello") ? ++pass : ++fail;
    // ans == cleanToken("") ? ++pass: ++fail;
    ans == cleanToken("EGGS! milk, fish,      @  bread cheese") ? ++pass: ++fail;
    set<string> tokens = gatherTokens(ans);
    return 0 == fail;
}



int main() {

    
    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.
    // cout << testCleanToken();
    
    // string filename;
    // getline(cin, filename);
    // searchEngine(filename);

    return 0;
}

