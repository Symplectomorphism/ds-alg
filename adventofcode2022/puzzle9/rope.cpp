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
    Odom(char c, int d) :  x(0), y(0) {
        switch (c) {
            case 'L':
                x = -1;
            case 'R':
                x = 1;
            case 'D':
                y = -1;
            case 'U':
                y = 1;
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
};

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
        void processLine(Odom o);
        void move(int ox, int oy); 
    private:
        Point start;
        Point head;
        Point tail;
        
        friend ostream& operator <<(ostream& os, const Rope& r);
        friend istream& operator >>(istream& input, Rope& r);
};

istream& operator >>( istream& input, Rope& r ) {
    char c;
    int d;
    input >> c >> d;
    Odom o {c, d};
    r.processLine(o);

    return input;
}

ostream& operator<<(ostream& os, const Rope& r) {
    os << "H: " << "(" << r.head.x << ", " << r.head.y << ");\t"
        << "T: " << "(" << r.tail.x << ", " << r.tail.y << ")." << endl;
    return os;
}

void Rope::processLine(Odom o) {
    cout << *this;
    for (int i=0; i<o.d; ++i) {
        move(o.x, o.y);
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
            if ( rel_ht.x == -1 ) {
                if (rel_nhh.x == -1)
                    tail = head;
                else if (rel_nhh.y != 0) {
                    Odom tmp { -1, 0 };
                    tail.move( tmp );
                }
            }
            else if ( rel_ht.x == 1 ) {
                if (rel_nhh.x == 1)
                    tail = head;
                else if (rel_nhh.y != 0) {
                    Odom tmp { 1, 0 };
                    tail.move( tmp );
                }
            }
            else if ( rel_ht.y == -1 ) {
                if (rel_nhh.y == -1)
                    tail = head;
                else if (rel_nhh.x != 0) {
                    Odom tmp { 0, -1 };
                    tail.move( tmp );
                }
            }
            else {
                if (rel_nhh.y == 1)
                    tail = head;
                else if (rel_nhh.x != 0) {
                    Odom tmp {0, 1};
                    tail.move(tmp);
                }
            }
        case 2:
            if ( taxicab(rel_nht) > 2 )
                tail = head;
    }
    head = next_head;
}

int main() {
    ifstream ist {"myinput_cropped"};
    Rope r;
    ist >> r;

    return 0;
}
