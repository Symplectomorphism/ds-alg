#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
// using namespace Eigen;

#define GAMMA 0.9

enum class Action {
    down, 
    up, 
    right, 
    left
};

ostream& operator<<(ostream& os, const Action& a) {
    switch (a) {
        case Action::down: os << "down"; break;
        case Action::up: os << "up"; break;
        case Action::right: os << "right"; break;
        case Action::left: os << "left"; break;
    }
    return os;
}

struct Odom {
    Odom(Action a) :  a(a) {
        switch (a) {
            case Action::down:
                cout << endl << "Going down!" << endl;
                x = 1;
                y = 0;
                break;
            case Action::up:
                cout << endl << "Going up!" << endl;
                x = -1;
                y = 0;
                break;
            case Action::right:
                cout << endl << "Going right!" << endl;
                x = 0;
                y = 1;
                break;
            case Action::left:
                cout << endl << "Going left!" << endl;
                x = 0;
                y = -1;
                break;
        }
    };
    Odom ( int x, int y ) : a(Action::down), x(x), y(y) {}; 

    Action a;
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
    friend bool operator== ( Point const&lhs, Point const& rhs );
};

bool operator== ( Point const& lhs, Point const& rhs ) {
    if ( lhs.x == rhs.x && lhs.y == rhs.y )
        return true;
    return false;
}

bool operator< ( Point const& lhs, Point const& rhs ) {
    if ( lhs.x < rhs.x )
        return true;
    else if ( lhs.x == rhs.x )
        if ( lhs.y < rhs.y ) { return true; }
    return false;
}

namespace std {

  template <>
  struct hash<Point>
  {
    std::size_t operator()(const Point& p) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:

      return ((hash<int>()(p.x)
               ^ (hash<int>()(p.y) << 1)) >> 1);
    }
  };

}

Odom relative ( Point p, Point q ) { return Odom {p.x-q.x, p.y-q.y}; }

int taxicab ( Odom rel ) { return abs( rel.x ) + abs( rel.y ); }

int taxicab ( Point p, Point q ) {
    Odom rel = relative(p, q);
    return taxicab( rel );
}

class ElvenHill {
    public:
        Point get_start() { return start; }
        Point get_end() { return end; }
        int get_elevation(Point p) { return elevation[p]; }
        float get_value(Point p) { return value[p]; }
        Action get_policy(Point p) { return policy[p]; }
        pair<int, int> get_size () { return size; }
        void processLine(string, int);
        int reward( Point p ) { return taxicab(p, end); }
        Point transition ( Point p, Action a );
        void next_state ( Point p, Action a ) { state = transition(p, a); }
    private:
        Point start;
        Point end;
        map<Point, int> elevation;
        map<Point, float> value;
        unordered_map<Point, Action, std::hash<Point>> policy;
        Point state;
        pair<int, int> size;

        friend ostream& operator <<(ostream& os, const ElvenHill& m);
        friend istream& operator >>(istream& input, ElvenHill& m);
};

istream& operator >>( istream& is, ElvenHill& m ) {
    int i = 0;
    string line;
    getline(is, line);
    m.processLine(line, i);
    i++;
    m.size.second = line.length();
    while ( !is.eof() ) {
        getline(is, line);
        m.processLine(line, i);
        i++;
    }
    m.size.first = i-1;

    return is;
}

ostream& operator<<(ostream& os, const ElvenHill& m) {
    return os;
}

void ElvenHill::processLine(string line, int i) {
    char a = 'a';
    char c = '0';
    Point p {0, 0};
    for (int j=0; j<line.length(); j++) {
        p.x = i;
        p.y = j;
        c = line.at(j);
        if (c == 'S') { 
            start = p; 
            c = 'a';
        }
        if (c == 'E') { 
            end = p; 
            c = 'z';
        }
        elevation.insert( make_pair(p, c-a) );
        value.insert( make_pair(p, 0.0) );
        policy.insert( make_pair(p, Action::down) );
        cout << "(" << p.x << ", " << p.y << "): " << (int)(c-a) << endl;
    }
    state = start;
}

Point ElvenHill::transition ( Point p, Action a ) {
    Odom o {a};
    Point tmp {p.x + o.x, p.x+o.y};
    if (tmp.x < 0 || tmp.x > size.first)
        return p;
    if (tmp.y < 0 || tmp.y > size.second)
        return p;
    if (elevation[tmp] > elevation[p]+1) 
        return p;
    return tmp;
}

int main() {
    ifstream ist {"myinput"};
    ElvenHill m;
    ist >> m;

    cout << m.get_elevation(m.get_end()) << endl;
    cout << m.get_policy(m.get_end()) << endl;
    cout << m.get_size().first << " " << m.get_size().second << endl;

    return 0;
}
