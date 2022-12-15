#ifndef POINT_H
#define POINT_H

#include <cstdio>
#include "Odom.h"

using namespace std;

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

#endif
