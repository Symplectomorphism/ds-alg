#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#include "Point.h"
#include "Odom.h"
#include "Action.h"
// #include <Eigen/Dense>

using namespace std;
// using namespace Eigen;

#define GAMMA 1.0

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
        void next_state () { 
            state = transition(get_state(), get_policy(get_state())); }
        void next_state ( Point p ) { state = transition(p, get_policy(p)); }
        void next_state ( Action a ) { state = transition(get_state(), a); }
        void next_state ( Point p, Action a ) { state = transition(p, a); }
        void ValueIteration(float theta);
        void bestStart();
        void simulate(int steps);
        void simulate(int steps, Point p);
    private:
        Point start;
        Point end;
        Point beststart;
        map<Point, int> elevation;
        map<Point, float> value;
        unordered_map<Point, Action, std::hash<Point>> policy;
        Point state;
        pair<int, int> size;
        vector<Point> trajectory;

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

        if ( i++ % 25 == 0 ) {
            cout << "Value[start] = " << value[start] << ", Policy[start] = " 
                 << policy[start] << ", Iteration = " << i-1 << endl;
        }

        for (it=elevation.begin(); it!=elevation.end(); it++) {
            Point s = it->first;
            float v = value[s];
            vector<Action> actions {Action::down, Action::up, Action::right, 
                                    Action::left};
            vector<float> vals;
            for ( const auto& a : actions ) {
                Point tmp = transition(s, a);
                vals.push_back( reward(s, tmp) + GAMMA*value[tmp] );
                // vals.push_back( reward_taxi(s, tmp) + GAMMA*value[tmp] );
            }
            auto iter = max_element(vals.begin(), vals.end());
            policy[s] = Action(iter-vals.begin());
            value[s] = *iter;
            Delta = max( Delta, abs(v-value[s]) );
        }
    }
    cout << endl << "Value[start] = " << value[start] << ", Policy[start] = " 
         << policy[start] << ", Iteration = " << i << ", Delta = " << Delta 
         << "." << endl;
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
         << value[beststart] << ", Policy[beststart] = " << policy[beststart] 
         << "." << endl;
}


void ElvenHill::simulate(int steps, Point p) {
    state = p;
    Odom v {Action::down};
    trajectory.push_back(state);
    ofstream myfile;
    myfile.open ("trajectory.csv");
    for (int i=0; i<steps; ++i) {
        myfile << state.y << "," << -state.x << endl;
        v.set_odom(policy[state]);
        state.move(v);
        trajectory.push_back(state);
    }
    myfile << state.y << "," << -state.x << endl;
    myfile.close();
}

void ElvenHill::simulate(int steps) {
    simulate(steps, start);
}


int main() {
    ifstream ist {"input"};
    ElvenHill m;
    ist >> m;

    m.simulate( abs(m.get_value(m.get_state())) );

    return 0;
}
