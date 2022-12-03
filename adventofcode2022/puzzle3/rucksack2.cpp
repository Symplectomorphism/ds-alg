#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Rucksack {
    public:
        Rucksack () : value(0) {
            unordered_map<char, int> tmp;
            for (int i=97; i<123; ++i) {
                dict.insert( make_pair<char, int> ((char)(i), i-96) );
                tmp.insert( make_pair<char, int> ((char)(i), 0) );
            }
            for (int i=65; i<91; ++i) {
                dict.insert( make_pair<char, int> ((char)(i), i-64+26) );
                tmp.insert( make_pair<char, int> ((char)(i), 0) );
            }
            for (int j=0; j<3; ++j)
                freq.push_back(tmp);
        }
        vector<string> get_contents() { return contents; }
        unordered_map<char, int> get_dict() { return dict; }
        char get_same() { return same; }
        int get_value() { return value; }
        void find_same();
    private:
        vector<string> contents;
        unordered_map<char, int> dict;
        char same;
        int value;
        vector<unordered_map<char, int>> freq;

        friend istream& operator >>(istream& input, Rucksack& r);
};

istream& operator >>( istream& input, Rucksack& r ) {
    string s;
    for (int i=0; i<3; ++i) {
        input >> s;
        r.contents.push_back(s);
    }
    r.find_same();
    return input;
}

void Rucksack::find_same() {
    bool flag = true;
    for ( int i=0; i<3; ++i ) {
        for ( auto& ch : contents[i] ) {
            freq[i].at(ch) += 1;
        }
    }
    for (int i=97; i<123; ++i) {
        char ch = (char)(i);
        ++value;
        if (freq[0].at(ch) * freq[1].at(ch) * freq[2].at(ch) != 0) { 
            flag = false; 
            break; 
        }
    }
    if ( flag ) {
        for (int i=65; i<91; ++i) {
            ++value;
            char ch = (char)(i);
            if (freq[0].at(ch) * freq[1].at(ch) * freq[2].at(ch) != 0) { break; }
        }
    }
    
    for ( auto& iter : dict ) { 
        if ( iter.second == value ) { same = iter.first; }
    }
}


int main() {
    ifstream ist {"input"};
    vector<Rucksack> sacks {};
    vector<int> priorities {};

    while (!ist.eof()) {
        Rucksack r;
        ist >> r;
        sacks.push_back(r);
    }
    sacks.pop_back();

    for ( Rucksack r : sacks ) {
        priorities.push_back(r.get_value());
        cout << r.get_contents()[0] << endl;
        cout << r.get_contents()[1] << endl;
        cout << r.get_contents()[2] << endl;
        cout << "Same letter: " << r.get_same() << ", with value: " << r.get_value() << endl << endl;
    }
    cout << accumulate(priorities.begin(), priorities.end(), 0) << endl;

    return 0;
}
