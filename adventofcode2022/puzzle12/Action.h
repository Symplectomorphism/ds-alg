#ifndef ACTION_H
#define ACTION_H

#include <cstdio>
using namespace std;

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

#endif
