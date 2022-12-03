#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

class Game {
    public:
        Game () : score(0) {}
        string get_player() { return player; }
        string get_opponent() { return opponent; }
        int get_score() { return score; }
        int compute_outcome();
    private:
        string opponent;
        string player;
        int score;

        friend istream& operator >>(istream& input, Game& g);
};

istream& operator >>( istream& input, Game& g ) {
    input >> g.opponent >> g.player;
    g.compute_outcome();
    return input;
}

int Game::compute_outcome() {
    int n = 0;
    if (opponent == "A") {
        if (player == "X")
            n = 1;
        else if ( player == "Y" )
            n = 2;
        else
            n = 0;
    }
    else if (opponent == "B") {
        if (player == "X")
            n = 0;
        else if ( player == "Y" )
            n = 1;
        else
            n = 2;
    }
    else {
        if (player == "X")
            n = 2;
        else if ( player == "Y" )
            n = 0;
        else
            n = 1; 
    }

    if ( player == "X" )
        score = 1;
    else if ( player == "Y" )
        score = 2;
    else 
        score = 3;
    score += 3*n;

    return n;
}

int main() {
    ifstream ist {"input"};
    vector<Game> games {};
    vector<int> scores {};

    while (!ist.eof()) {
        Game g;
        ist >> g;
        games.push_back(g);
    }
    games.pop_back();

    cout << games.size() << endl;
    for ( Game g : games ) {
        int n = g.get_score();
        scores.push_back(n);
        cout << g.get_opponent() << " " << g.get_player() << ": " 
             << n << endl;
    }

    cout << "Total score: " << accumulate(scores.begin(), scores.end(), 0) << endl;

    return 0;
}
