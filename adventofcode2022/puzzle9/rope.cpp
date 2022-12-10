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
    Odom(char c, int d) :  c(c), d(d) {
        switch (c) {
            case 'L':
                cout << endl << "Going left!" << endl;
                x = -1;
                y = 0;
                break;
            case 'R':
                cout << endl << "Going right!" << endl;
                x = 1;
                y = 0;
                break;
            case 'D':
                cout << endl << "Going down!" << endl;
                x = 0;
                y = -1;
                break;
            case 'U':
                cout << endl << "Going up!" << endl;
                x = 0;
                y = 1;
                break;
        }
    };
    Odom ( int x, int y ) : c(0), d(0), x(x), y(y) {}; 

    char c;
    int d;
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

class Rope {
    public:
        Point get_head() { return head; }
        Point get_tail() { return tail; }
        set<Point> get_visited() { return tail_visited; }
        void processLine(Odom o);
        void move(int ox, int oy); 
    private:
        Point start;
        Point head;
        Point tail;
        set<Point> tail_visited;
        
        friend ostream& operator <<(ostream& os, const Rope& r);
        friend istream& operator >>(istream& input, Rope& r);
};

istream& operator >>( istream& input, Rope& r ) {
    char c;
    int d;
    input >> c >> d;
    Odom o {c, d};
    cout << o.c << " " << o.d << endl;
    r.processLine(o);

    return input;
}

ostream& operator<<(ostream& os, const Rope& r) {
    os << "H: " << "(" << r.head.x << ", " << r.head.y << ");\t"
        << "T: " << "(" << r.tail.x << ", " << r.tail.y << ")." << endl;
    return os;
}

void Rope::processLine(Odom o) {
    cout << o.x << " " << o.y << endl;
    cout << *this;
    for (int i=0; i<o.d; ++i) {
        move(o.x, o.y);
        cout << *this;
    } 
}

void Rope::move ( int ox, int oy ) {
    int distance = taxicab(head, tail);
    Point next_head { head.x+ox, head.y+oy };
    Odom rel_ht = relative(head, tail);
    Odom rel_nhh = relative(next_head, head);
    Odom rel_nht = relative(next_head, tail);

    switch (distance) {
        case 1:
            if ( rel_ht.x == 1 && rel_nhh.x == 1 ) { tail = head; }
            if ( rel_ht.x == -1 && rel_nhh.x == -1 ) { tail = head; }
            if ( rel_ht.y == 1 && rel_nhh.y == 1 ) { tail = head; }
            if ( rel_ht.y == -1 && rel_nhh.y == -1 ) { tail = head; }
            break;
        case 2:
            if ( taxicab(rel_nht) > 2 )
                tail = head;
            break;
    }
    head = next_head;

    if ( tail_visited.find(tail) == tail_visited.end() )
        tail_visited.insert(tail);
}

int main() {
    ifstream ist {"input"};
    Rope r;

    do {
        ist >> r;
        // cout << "Hello" << endl;
    } while (ist.good() );

    cout << r.get_visited().size() << endl;

    return 0;
}
