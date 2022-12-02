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
};

int main() {
    vector<Elf> elves {};
    ifstream ist {"input"};
    
    for ( Elf e; ist >> e; ) // need to implement operator>> for Elf
        elves.push_back(e);

    return 0;
}
