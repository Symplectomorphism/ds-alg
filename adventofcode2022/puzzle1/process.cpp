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
        Elf () : cal_sum(0) {};
        void add_cal(int c) { cal.push_back(c); cal_sum += c; }
        vector<int> get_cal() { return cal; }
        int get_sum() { return cal_sum; }
    private:
        vector<int> cal;
        int cal_sum;

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

    return input;
}

int main() {
    vector<Elf> elves {};
    ifstream ist {"input"};

    /*
     * I'm not sure why, but the following
     * does not work!
     *
    for ( Elf e; ist >> e; ) {
        elves.push_back(e);
    }
    */

    while (!ist.eof()) {
        Elf e;
        ist >> e;
        elves.push_back(e);
    }

    vector<int> sums {};
    for ( Elf e : elves ) 
        sums.push_back(e.get_sum());

    auto it = max_element(sums.begin(), sums.end());
    cout << "Max index " << it-sums.begin() << ", max value: " << *it << endl;

    return 0;
}
