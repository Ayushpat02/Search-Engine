//Program 2: Search Engine
//Ayush Patel, 677448035, apate554@uic.edu
//CS 251, Fall 2023, UIC
//12 PM, Professot Koehler
//This program is about taking in user input of a word and see if it matches with a url as they search the word on the browser

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

//the clean token functions takes a string an it strips off any punctuations in the beggining and in the end of the stirng
//I created an emptry string tokentrim to store the trimmed off string s
//I used a for loop to check the first instance where there is not a punct in s
//I captured the index where it is not a punct in int a
//I did the same to check the first instance where there is no punct in the end of the string, where int c captured the index
//I used substr to trim off s to no puncts in the beginning and the end of the string s, a was the starting val with the first index
//it would go up to the difference between c and a + 1, where there are no puncts in the string
//I did anther for loop where if s trimmed is an alpha chararcter, then it gets added to the tokentrim empty string to store s trimmed with lowercase letters
//else if there are no letters but puncts in the middle and numbers, then it gets added without lowercase
//the counter was to detect if there is a string s with alphabets in it, so it can be returned
//else s with digits can't be returned
//if there is no emptry string, then s trimmed gets returned as well
//however, if none of those cases apply, then an emptry string is returned
string cleanToken(string s) {
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
    int c = s.length();
    for (int i = s.length()-1; i >= 0; i--) {
        if (!ispunct(s.at(i))) {
            c = i;
            break;
        }
    }
    int d = s.length() - c;
    s = s.substr(a, c - a + 1);
    int counter = 0;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s.at(i))) {
            counter++;
            tokentrim += tolower(s.at(i));
        }
        else {
            tokentrim += s.at(i);
        }
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
    return tokentrim; 
}

//gatherTokens takes in a text from the body line
//this function uses stringstream to split the string line into individual strings using a while loop
//if the individual strings aren't empty strings, then the set insterts the solo string
//if there is a empty string in the tokens set after insertion, erase it
//return the set with individual strings of the body line
set<string> gatherTokens(string text) {
    set<string> tokens;
    
    stringstream strstream(text);
    string x;
    while (strstream >> x) {
        if (!x.empty()) {
            tokens.insert(cleanToken(x));
        }
    }
    if (tokens.count("")) {
        tokens.erase("");
    }
    return tokens;
}

//buildIndex takes ina filename and a map of a set
//ifstream opens the file
//if the file doesn't open, output error message
//return count which is an int that stores the amount of matches the word has with a website
//while loop that takes in the whole line of the url which is first and the body text which is second after the url
//a set string urls inserts the website link
//a set string word inserts the body text from gathertokens, which returns a set string with individual strings from one line trimmed
//for each loop that goes through the word set and updates the inverted index where the word is in the website
//return count that stores the amount of lines were indexed
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
    return count;
}

//findQueryMatches takes in the inverted index, and the sentence that the user wants to search from the website link
//I used stringstream to sepreate the sentence line from the user into mutiple strings
//a for loop was used to see if the sentence input was a single word, hence it checked if a character was a space
//no spaces meant that space equals 0, and the set string result inserted the website url where the word can be found
//while loop that seperated the single line of string into seperate strings (token) by whitespace
//if the first index of the individual strings equalled a + operator, then I cleared the token string
//I used set_intersection to store urls that were in both strings
//I used the format of the result value, current Index value, and set string temp value that stored the result of the function for ser string result to insert
//I cleared the result set because I didn't want it to hold any old values from the other cases
//then, I inserted the values in the temp set to update result based off the case
//same process for the - operator expect used set_difference to store where there are urls where neither word is there
//same process if there was no operator, used set_union to combine the webstite urls of the body line
//I cleared the temp values after each iteration of the while loop because it didn't work with mutiple operators in one line, hence cleaning out the elements in temp
//return the result set of the urls of the setence
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result;
    set<string> one;
    set<string> two;
    set<string> temp;
    string queryterm = cleanToken(sentence);
    stringstream ss(sentence);
    string token;
    int space = 0;
    int modifier = 0;
    for (int i = 0; i < queryterm.length(); i++) {
        if (queryterm.at(i) == ' ') {
            space++;
        }
    }
    if (space == 0) {
        result.insert(index[queryterm].begin(), index[queryterm].end());
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
        if (token.at(0) == '+') {
            token = cleanToken(token); 
            set_intersection(begin(result), end(result), begin(index[token]), end(index[token]), inserter(temp, end(temp)));
            result.clear();
            result.insert(temp.begin(), temp.end());
        }
        else if (token.at(0) == '-') {
            token = cleanToken(token); 
            set_difference(begin(result), end(result), begin(index[token]), end(index[token]), inserter(temp, end(temp)));
            result.clear();
            result.insert(temp.begin(), temp.end());
        }
        else {
            set_union(begin(result), end(result), begin(index[token]), end(index[token]), inserter(temp, end(temp)));
            result.clear();
            result.insert(temp.begin(), temp.end());
        }
        temp.clear();
    }
    return result; 
}



//searchEngine takes in a filename and outputs the search engine for the user
//I declared a map of a set index to refer to the values in the index map of set
//buildIndex was called to output the amount of lines index, and the index map of set gets updated with the urls of the word
//I used getline to get the whole user input sentence where it includes whitespaces as well
//while the user input query isn't an empty string (the enter command ending the program), get user input
//the set string final is for getting the set string of the urls where the words match depending on if there is an operator or not
//final has all of the urls depending on the user input
//outputted the values of final using for each loop, assigning string url as the strings in final, then I got used input to continue the while loop
//after the while loop stops, output thank you message
void searchEngine(string filename) {
    map<string, set<string> > index;
    string query;
    set<string> final;
    int indexn = buildIndex(filename, index); 
    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << indexn << " pages containing " << index.size() << " unique terms" << endl;
    cout << "Enter query sentence (press enter to quit): ";
    getline(cin, query);
    while (query != "") {
        final = findQueryMatches(index, query);
        cout << "Found " << final.size() << " matching pages" << endl;
        for (string url : final) {
            cout << url << endl;
        }
        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, query);
    }
    cout << "Thank you for searching!" << endl;
    
    
}
