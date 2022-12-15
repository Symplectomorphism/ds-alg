#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
// #include <Eigen/Dense>

using namespace std;
// using namespace Eigen;

#define GAMMA 1.0

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
    Odom(Action a) : a(a) {
        switch (a) {
            case Action::down:
                x = 1;
                y = 0;
                break;
            case Action::up:
                x = -1;
                y = 0;
                break;
            case Action::right:
                x = 0;
                y = 1;
                break;
            case Action::left:
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

    friend ostream& operator<< ( ostream& os, const Point& p );
    friend bool operator< ( Point const&lhs, Point const& rhs );
    friend bool operator== ( Point const&lhs, Point const& rhs );
};

ostream& operator<<(ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";

    return os;
}

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
        ElvenHill () {};
        Point get_start() { return start; }
        Point get_end() { return end; }
        int get_elevation() { return elevation[get_state()]; }
        int get_elevation(Point p) { return elevation[p]; }
        float get_value() { return value[get_state()]; }
        float get_value(Point p) { return value[p]; }
        Point get_state() { return state; }
        Action get_policy() { return policy[get_state()]; }
        Action get_policy(Point p) { return policy[p]; }
        void set_policy(Action a) { policy[get_state()] = a; }
        void set_policy(Point p, Action a) { policy[p] = a; }
        void set_state(Point p) { state = p; }
        pair<int, int> get_size () { return size; }
        void processLine(string, int);
        float reward( Point p, Point q ) { 
            if ( p == end ) { return 0.0; }
            return -1.0;
        }
        float reward_taxi( Point p, Point q ) { 
            if ( p == end ) { return 0.0; }
            return -taxicab(q, end);
        }
        Point transition ( Point p, Action a );
        void next_state () { state = transition(get_state(), get_policy(get_state())); }
        void next_state ( Point p ) { state = transition(p, get_policy(p)); }
        void next_state ( Action a ) { state = transition(get_state(), a); }
        void next_state ( Point p, Action a ) { state = transition(p, a); }
        void ValueIteration(float theta);
        void bestStart();
    private:
        Point start;
        Point end;
        Point beststart;
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
    m.size.second = line.length()-1;
    while ( !is.eof() ) {
        getline(is, line);
        m.processLine(line, i);
        i++;
    }
    m.size.first = i-2;
    m.value[m.get_end()] = 0.0;

    m.ValueIteration(1);
    m.bestStart();

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
        value.insert( make_pair(p, -520.0) );
        policy.insert( make_pair(p, Action::down) );
    }
    state = start;
    beststart = start;
}

Point ElvenHill::transition ( Point p, Action a ) {
    Odom o {a};
    Point tmp {p.x + o.x, p.y+o.y};
    if (tmp.x < 0 || tmp.x > size.first)
        return p;
    if (tmp.y < 0 || tmp.y > size.second)
        return p;
    if (elevation[tmp] > elevation[p]+1)
        return p;
    if ( p == end )
        return p;
    return tmp;
}

void ElvenHill::ValueIteration (float theta) {
    float Delta = 100000.0;
    int i = 0;
    while ( Delta > theta ) {
        Delta = 0.0;
        map<Point, int>::iterator it;
        for (it=elevation.begin(); it!=elevation.end(); it++) {
            Point s = it->first;
            float v = value[s];
            vector<Action> actions {Action::down, Action::up, Action::right, Action::left};
            vector<float> vals;
            for ( const auto& a : actions ) {
                Point tmp = transition(s, a);
                vals.push_back( reward(s, tmp) + GAMMA*value[tmp] );
                // vals.push_back( reward_taxi(s, tmp) + GAMMA*value[tmp] );
            }
            value[s] = *max_element(vals.begin(), vals.end());
            Delta = max( Delta, abs(v-value[s]) );
        }
        cout << "Value[start] = " << value[start] << ", Delta = " << Delta 
             << ", Iteration = " << ++i << endl;
    }
}

void ElvenHill::bestStart() {
    map<Point, int>::iterator it;
    for (it=elevation.begin(); it!=elevation.end(); it++) {
        Point s = it->first;
        if (elevation[s] == 0) {
            if ( value[s] > value[beststart] ) { beststart = s; }
        }
    }
    cout << "Best start = " << beststart << ", with Value[beststart] = " 
         << value[beststart] << endl;
}

int main() {
    ifstream ist {"input"};
    ElvenHill m;
    ist >> m;

    return 0;
}
