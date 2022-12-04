#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;


class Assignment {
    public:
        Assignment() : overlap(false) { }
        pair<int, int> get_first_range() { return range1; }
        pair<int, int> get_second_range() { return range2; }
        bool get_overlap() { return overlap; }
        void compute_overlap();
    private:
        pair<int, int> range1;
        pair<int, int> range2;
        bool overlap;

        friend istream& operator >>(istream& input, Assignment& a);
};

istream& operator >>( istream& input, Assignment& a ) {
    int first, second, third, fourth;
    string s;
    getline(input, s);

    if (input) {
        size_t dash1 = s.find("-");
        size_t comma = s.find(",", dash1);
        size_t dash2 = s.find("-", comma);

        first = stoi(s.substr(0, dash1));
        second = stoi(s.substr(dash1+1, comma-dash1-1));
        third = stoi(s.substr(comma+1, dash2-comma-1));
        fourth = stoi(s.substr(dash2+1, s.size()));

        a.range1 = make_pair(first, second);
        a.range2 = make_pair(third, fourth);
    }
    a.compute_overlap();

    return input;
}

void Assignment::compute_overlap() {
    if ( range1.first > range2.second || range2.first > range1.second ) { 
        overlap = false; 
    }
    else { overlap = true; }
}

int main() {
    ifstream ist {"input"};
    vector<Assignment> assignments{};
    vector<int> overlaps;
    
    Assignment a;
    while (ist >> a)
        assignments.push_back(a);

    for ( auto& a : assignments )
        overlaps.push_back(a.get_overlap());

    cout << accumulate(overlaps.begin(), overlaps.end(), 0) << endl;

    return 0;
}
