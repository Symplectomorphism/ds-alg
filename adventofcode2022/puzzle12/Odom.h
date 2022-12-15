#ifndef ODOM_H
#define ODOM_H

#include "Action.h"

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

    void set_odom(Action a) { 
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
    }
};

#endif
