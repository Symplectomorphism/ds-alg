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
            cout << "Empty line." << endl;
            break;
        }
        istringstream tmp {s};
        int n;
        tmp >> n;
        e.add_cal(n);
    }
    
    for ( auto c : e.get_cal() )
        cout << c << endl;

    return input;
}

int main() {
    vector<Elf> elves {};
    ifstream ist {"input"};

    int n = 0;

    // for ( Elf e; ist >> e; ) {
    //     elves.push_back(e);
    //     n++;
    // }
    // cout << n << endl;

    Elf e1, e2, e3;
    ist >> e1 >> e2 >> e3;

    elves.push_back(e1);
    elves.push_back(e2);
    elves.push_back(e3);

    for ( Elf e : elves )
        for ( auto c : e.get_cal() )
            cout << c << endl;

    return 0;
}
