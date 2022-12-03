#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

#define ALPHABETS_COUNT 26 

class Rucksack {
    public:
        Rucksack () : same(0) {
            for (int i=97; i<123; ++i) {
                dict.insert( make_pair<char, int> ((char)(i), i-96) );
            }
            for (int i=65; i<91; ++i) {
                dict.insert( make_pair<char, int> ((char)(i), i-64+26) );
            }
        }
        string get_contents() { return contents; }
        string get_first() { return first; }
        string get_second() { return second; }
        int get_value() { return value; }
        unordered_map<char, int> get_dict() { return dict; }
        char get_same() { return same; }
        void split();
        void find_same();
    private:
        string contents;
        string first;
        string second;
        char same;
        int value;
        unordered_map<char, int> dict;

        friend istream& operator >>(istream& input, Rucksack& r);
};

istream& operator >>( istream& input, Rucksack& r ) {
    input >> r.contents;
    r.split();
    r.find_same();
    return input;
}

void Rucksack::split() {
    int n = contents.size();
    first = contents.substr(0, n/2);
    second = contents.substr(n/2, n);
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
    vector<int> proxies {};

    while (!ist.eof()) {
        Rucksack r;
        ist >> r;
        sacks.push_back(r);
    }
    sacks.pop_back();

    // cout << sacks.size() << endl;
    for ( Rucksack r : sacks ) {
        proxies.push_back(r.get_value());
        // cout << r.get_contents() << ": " << r.get_same() << ", " << r.get_value()
        //      << endl;
    }

    cout << accumulate(proxies.begin(), proxies.end(), 0) << endl;

    // cout << endl << sacks[0].get_first() << " | " << sacks[0].get_second() << endl;
    // cout << sacks[0].get_same() << " with value: " << sacks[0].get_value() << endl;

    return 0;
}
