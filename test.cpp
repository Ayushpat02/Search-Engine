#include <iostream>
#include <string>
#include <set>
#include <map>
using namespace std;

#include <sstream>
#include <fstream>
#include <algorithm>

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
string cleanToken(string s) {
    // cout << s << endl;
    string tokentrim = "";
    string empytstr = "";
    int a = 0;
    for (int i = 0; i < s.length(); i++) {
        if (!ispunct(s.at(i))) {
            a = i;
            break;
        }
    }
    int b = s.length() - a;
    // s.erase(s.begin(), s.end() - b);

    int c = s.length();
    for (int i = s.length()-1; i >= 0; i--) {
        if (!ispunct(s.at(i))) {
            c = i;
            break;
        }
    }
    // cout << s << endl;
    int d = s.length() - c;
    s = s.substr(a, c - a + 1);
    // cout << s << endl;
    // s.erase(s.begin()+c+1, s.end());
    int counter = 0;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s.at(i))) {
            counter++;
            tokentrim += tolower(s.at(i));
        }
        else {
            tokentrim += s.at(i);
        }
        // if (isalpha(s.at(i))) {
        //     // counter++;
        // }
    }

    if (counter == 0) {
        return empytstr;
    }
    if (tokentrim.size() != 0) {
        return tokentrim;
    }
    else {
        return empytstr;
    }
    
    // TODO:  Write this function.
    
    
    return tokentrim;  // TODO:  update this.
}

set<string> gatherTokens(string text) {
    set<string> tokens;
    
    stringstream strstream(text);
    string x;
    while (strstream >> x) {
        // cout << '.' << x << '.'<< endl;
        if (!x.empty()) {
            tokens.insert(cleanToken(x));
        }
        // tokens.insert(cleanToken(x));
    }
    if (tokens.count("")) {
        tokens.erase("");
    }
    return tokens;  // TODO:  update this.
}

int buildIndex(string filename, map<string, set<string> >& index) {
    set<string> word;
    set<string> urls;
    set<string> link;
    ifstream thefile(filename);
    int count = 0;
    string bodyline;
    string websitelink;
    if (!thefile.is_open()) {
        cout << "Error with file" << endl;
        return count;
    }
    while ((getline(thefile, websitelink)) && getline(thefile, bodyline)) {
        urls.insert(websitelink);
        link = urls;
        word = gatherTokens(bodyline); 
        for (string match : word) {
            index[match].insert(websitelink);
        }
         count++;
    }
   
    // TODO:  Write this function.

    return count;
}

// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    set<string> one;
    set<string> two;
    set<string> temp;
    // string queryterm = cleanToken(sentence);
    string queryterm = cleanToken(sentence);
    istringstream ss(queryterm);
    string token;
    int space = 0;
    int modifier = 0;
    for (int i = 0; i < queryterm.length(); i++) {
        if (queryterm.at(i) == ' ' && queryterm.at(i) != '+' && queryterm.at(i) != '-') {
            space++;
        }
        else if (queryterm.at(i) == '+' && queryterm.at(i) == ' ') {
            modifier++;
            space++;
        }
    }
    if (space == 0) {
        result = index[queryterm];
    }
    
    int counter = 0;
    string o;
    string t;
    int iter = 0;
    int none = 0;
    int plus = 0;
    int minus = 0;
    int i = 0; 

    while (getline(ss, token, ' ')) {
        result.insert(index[token].begin(), index[token].end());
        if (token.at(0) != '+' && token.at(0) != '-') {
            set_union(begin(result), end(result), begin(index[token]), end(index[token]), inserter(temp, end(temp)));
            result.insert(temp.begin(), temp.end());
        }
        if (token.at(0) == '+') {
            set_intersection(begin(result), end(result), begin(index[token]), end(index[token]), inserter(temp, end(temp)));
            result.insert(temp.begin(), temp.end());
        }
    }
    // while (getline(ss, token, ' '))  {
    //     if (counter % 2 == 0) {
    //         // one.insert(token);
    //         one.insert(index[token].begin(), index[token].end());
    //         counter++;
    //         continue;
    //         result.insert(index[token].begin(), index[token].end());
    //         iter++;
    //         // result = index[token];
    //     }
    //     else {
    //         two.insert(index[token].begin(), index[token].end());
    //         // two.insert(token);
    //         counter++;
    //         iter++;
    //         if (token.at(0) != '+' && token.at(0) != '-') {
    //             set_union(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    //             }
    //         if (token.at(0) == '+') {
    //             set_intersection(begin(two), end(two), begin(result), end(result), inserter(temp, end(temp)));
    //             result.insert(temp.begin(), temp.end());
    //         }
    //         if (token.at(0) == '-') {
    //             set_difference(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    //         }
    //         // if (token.at(0) == '+') {
    //         //     plus++;
    //         // }
    //         // else if (token.at(0) == '-') {
    //         //     minus++;
    //         // }
    //         // else {
    //         //     none++;
    //         // }
    //     }
    // }
    
    // if (token.at(0) != '+' && token.at(0) != '-') {
    //     set_union(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    //     }
    // else if (token.at(0) == '+') {
    //     set_intersection(begin(one), end(one), begin(one), end(two), inserter(result, end(result)));
    // }
    // else if (token.at(0) == '-') {
    //     set_difference(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    // }


            // if (token.at(0) != '+' && token.at(0) != '-') {
            //     set_union(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
            // }
            // else if (token.at(0) == '+') {
            //     set_intersection(begin(one))
            // }
    
    // while (getline(ss, token, ' ')) {
    //     if (counter == 0) {
    //         one.insert(token);
    //         counter++;
    //         continue;
    //     }
    //     else {
    //         if (token.at(0) == '+') {
    //             plus++;
    //         } 
    //         else if (token.at(0) == '-') {
    //             minus++;
    //         }
    //         two.insert(token);
    //         counter = 0;
    //         continue;
    //     }
    //     iter++;
    // }
    // if (iter == 1) {
    //     result = index[token];
    // }
    // // else if (iter > 1) 
    // for (string match1 : one) {
    //     one = index[match1];
    // }
    // for (string match2 : two) {
    //     two = index[match2];
    //     if (match2.at(0) == '+') {
    //         set_intersection(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    //     }
    //     else if (match2.at(0) == '-') {
    //         set_difference(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    //     }
    //     else {
    //         set_union(begin(one), end(one), begin(two), end(two), inserter(result, end(result)));
    //     }
    // }

    
    // TODO:  Write this function.
    
    
    return result;  // TODO:  update this.
}


// TODO: Add a function header comment here to explain the
// behavior of the function and how you implemented this behavior
void searchEngine(string filename) {

    
    // TODO:  Write this function.
    
    
}
