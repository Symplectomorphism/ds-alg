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
        void compute_outcome();
    private:
        string opponent;
        string player;
        string outcome;
        int score;

        friend istream& operator >>(istream& input, Game& g);
};

istream& operator >>( istream& input, Game& g ) {
    input >> g.opponent >> g.outcome;
    g.compute_outcome();
    return input;
}

void Game::compute_outcome() {
    int n = 0;
    if (opponent == "A") {
        if (outcome == "X") {
            n = 0;
            player = "Z";
        }
        else if ( outcome == "Y" ) {
            n = 1;
            player = "X";
        }
        else {
            n = 2;
            player = "Y";
        }
    }
    else if (opponent == "B") {
        if (outcome == "X") {
            n = 0;
            player = "X";
        }
        else if ( outcome == "Y" ) {
            n = 1;
            player = "Y";
        }
        else {
            n = 2;
            player = "Z";
        }
    }
    else {
        if (outcome == "X") {
            n = 0;
            player = "Y";
        }
        else if ( outcome == "Y" ) {
            n = 1;
            player = "Z";
        }
        else {
            n = 2; 
            player = "X";
        }
    }

    if ( player == "X" )
        score = 1;
    else if ( player == "Y" )
        score = 2;
    else 
        score = 3;
    score += 3*n;
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
