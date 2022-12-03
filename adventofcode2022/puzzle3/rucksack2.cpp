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
        Rucksack () {
            for (int i=97; i<123; ++i) {
                dict.insert( make_pair<char, int> ((char)(i), i-96) );
            }
            for (int i=65; i<91; ++i) {
                dict.insert( make_pair<char, int> ((char)(i), i-64+26) );
            }
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
    for ( auto& ch : first ) {
        for ( auto& ch2 : second ) {
            if (ch == ch2) {
                same = ch;
                value = dict.at(same);
            }
        }
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
    }

    cout << accumulate(priorities.begin(), priorities.end(), 0) << endl;


    return 0;
}
