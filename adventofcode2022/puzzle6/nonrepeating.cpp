#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

#define WINDOW_LENGTH 4

class DataStream {
    public:
        DataStream () : state(0), found(false) {
            for (int i=97; i<123; ++i) {
                freq.insert( make_pair<char, int> ((char)(i), 0) );
            }
        }
        string get_data() { return data; }
        string get_window() { return window; }
        int get_state() { return state; }
        bool get_found() { return found; }
        void assignWindow() { 
            window = data.substr(state, WINDOW_LENGTH); 
            cout << window << endl;
        }
        void processWindow();
    private:
        unordered_map<char, int> freq;
        string data;
        string window;
        int state;
        bool found;
        friend istream& operator >>(istream& input, DataStream& ds);
};

istream& operator >>( istream& input, DataStream& ds ) {
    input >> ds.data;
    ds.assignWindow();
    return input;
}

void DataStream::processWindow() {
    char ch;
    for (int i=0; i<WINDOW_LENGTH; ++i) {
        ch = window.at(i);
        freq.at(ch) += 1;
    }

    using pair_type = decltype(freq)::value_type;

    auto pr = std::max_element
    (
        std::begin(freq), std::end(freq),
        [] (const pair_type & p1, const pair_type & p2) {
            return p1.second < p2.second;
        }
    );

    if (pr->second > 1) {
        state += 1;
        for ( auto& el : freq ) { el.second = 0; }
        assignWindow();
    } else {
        found = true;
    }
}

int main() {
    ifstream ist {"input"};
    DataStream ds;
    ist >> ds;

    while (!ds.get_found())
        ds.processWindow();
    cout << ds.get_state()+WINDOW_LENGTH << endl;


    return 0;
}
