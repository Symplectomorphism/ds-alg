#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

struct Odom {
    Odom ( int x, int y ) : x(x), y(y) {}; 

    int x;
    int y;
};

struct Point {
    Point() : x(0), y(0) {};
    Point(int x, int y) : x(x), y(y) {};
    int x;
    int y;

    void move(Odom v) {
        x += v.x;
        y += v.y;
    }

    friend bool operator< ( Point const&lhs, Point const& rhs );
};

bool operator< ( Point const& lhs, Point const& rhs ) {
    if ( lhs.x < rhs.x )
        return true;
    else if ( lhs.x == rhs.x )
        if ( lhs.y < rhs.y ) { return true; }
    return false;
}

Odom relative ( Point p, Point q ) { return Odom {p.x-q.x, p.y-q.y}; }

int taxicab ( Odom rel ) { return abs( rel.x ) + abs( rel.y ); }

int taxicab ( Point p, Point q ) {
    Odom rel = relative(p, q);
    return taxicab( rel );
}

class ElvenMap {
    public:
        int get_elevation(Point p) { return elevation[p]; }
        void processLine(string, int);
    private:
            Point start;
            Point end;
            map<Point, int> elevation;

            friend ostream& operator <<(ostream& os, const ElvenMap& m);
            friend istream& operator >>(istream& input, ElvenMap& m);
};

istream& operator >>( istream& is, ElvenMap& m ) {
    int i = 0;
    while ( !is.eof() ) {
        string line;
        getline(is, line);
        m.processLine(line, i);
        i++;
    }

    return is;
}

ostream& operator<<(ostream& os, const ElvenMap& m) {
    return os;
}

void ElvenMap::processLine(string line, int i) {
    char a = 'a';
    char c = '0';
    Point p {0, 0};
    for (int j=0; j<line.length(); j++) {
        p.x = i;
        p.y = j;
        c = line.at(j);
        elevation.insert( make_pair(p, c-a) );
        if (c == 'S') { 
            start = p; 
            elevation[start] = 0;
        }
        if (c == 'E') { 
            end = p; 
            elevation[end] = 'z' - a;
        }
        cout << "(" << p.x << ", " << p.y << "): " << (int)(c-a) << endl;
    }

}

int main() {
    ifstream ist {"myinput"};
    ElvenMap m;
    ist >> m;

    cout << m.get_elevation(Point{1,2}) << endl;

    return 0;
}
