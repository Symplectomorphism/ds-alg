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
        if (s.empty())
            break;
        else {
            istringstream tmp {s};
            int n;
            tmp >> n;
            e.add_cal(n);
        }
    }
    
    return input;
}

int main() {
    vector<Elf> elves {};
    ifstream ist {"myinput"};

    Elf e {};
    ist >> e;
    
    vector<int> cals = e.get_cal();
    for ( auto c : cals )
        cout << c << endl;
    // for ( Elf e; ist >> e; ) // need to implement operator>> for Elf
    //     elves.push_back(e);

    return 0;
}
