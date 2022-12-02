#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Elf {
    public:
        void add_cal(int c) { cal.push_back(c); }
        vector<int> get_cal() { return cal; }
    private:
        vector<int> cal;

        friend istream& operator >>(istream& input, Elf& e);
};

istream& operator >>( istream& input, Elf& e ) {
    string s;
    while ( getline(input, s) )
    {
        if (s.empty()) {
            break;
        }
        istringstream tmp {s};
        int n;
        tmp >> n;
        e.add_cal(n);
    }
    
    // for ( auto c : e.get_cal() )
    //     cout << c << endl;

    return input;
}

int main() {
    vector<Elf> elves {};
    ifstream ist {"input"};

    /*
     * I'm not sure why, but the following
     * does not work!
    for ( Elf e; ist >> e; ) {
        elves.push_back(e);
        n++;
    }
    */

    while (!ist.eof()) {
        Elf e;
        ist >> e;
        elves.push_back(e);
    }

    for ( auto c : elves[251].get_cal() )
        cout << c << endl;

    return 0;
}
