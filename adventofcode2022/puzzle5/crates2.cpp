#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

void insert( stack<char>& k , char j){
    if(k.empty()){
        k.push(j);
        return;
    }
    int temp = k.top();
    k.pop();
    insert(k, j);
    k.push(temp);
}

void reverse(stack<char> &s){
    if(s.empty()){
        return;
    }
    int temp = s.top();
    s.pop();
    reverse(s);
    insert(s,temp);
}

class Stacks {
    public:
        Stacks () {
            stack<char> s;
            for (int i=0; i<9; ++i) { stacks.push_back(s); }
        }
        vector<stack<char>> get_stacks() { return stacks; }
        void rev_stacks() { 
            for (int i=0; i<9; ++i) {
                reverse(stacks[i]);
            }
        }
        void pop(int i) { stacks[i].pop(); }
        void move(int n, int m, int l) {
            for(int j=0; j<n; ++j) {
                stacks[l-1].push(stacks[m-1].top());
                stacks[m-1].pop();
            }
        }
    private:
        vector<stack<char>> stacks {};
        friend istream& operator >>(istream& input, Stacks& st);
};


istream& operator >>( istream& input, Stacks& st ) {
    string s;
    while( getline(input, s) ) {
        if (s.empty()) {
            break;
        }
        istringstream tmp {s};
        char b;
        int i = 0;
        int n = 0;
        tmp >> noskipws;

        while ( tmp >> b ) {
            if ( b >= 65 && b <= 90 ) {
                st.stacks[i].push(b);
            }
            else if ( b == 91 ) { 
                i += n/4;
                n = 0;
                continue; 
            }
            else if ( b == 93 ) {
                ++i;
                continue;
            }
            else if ( b == 32 ) {
                ++n;
            }
            else { break; }
        }
    }

    return input;
}

int main() {
    ifstream ist {"input"};
    Stacks st;
    ist >> st;

    st.rev_stacks();

    int n, m, l;
    string s;
    while ( ist >> s ) {
        ist >> n >> s >> m >> s >> l;
        st.move(n, m, l);
    }

    
    // for (int i=0; i<9; ++i) {
    //     while ( st.get_stacks()[i].size() ) {
    //         cout << st.get_stacks()[i].top() << " ";
    //         st.pop(i);
    //     }
    //     cout << endl;
    // }

    for (int i=0; i<9; ++i)
        cout << st.get_stacks()[i].top();
    cout << endl;

    return 0;
}
