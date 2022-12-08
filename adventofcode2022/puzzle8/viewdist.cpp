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

#define MAXBUFSIZE  ((int) 1e6)

MatrixXd readMatrix( const char* filename ) {
    int cols = 0, rows = 0;
    double buff[MAXBUFSIZE];

    // Read numbers from file into buffer.
    ifstream infile;
    infile.open(filename);
    while ( !infile.eof() ) {
        string line;
        getline(infile, line);

        int temp_cols = 0;
        char x = '0';
        for (int i=0; i<line.length(); i++)
            buff[cols*rows+temp_cols++] = line.at(i)-x;

        // stringstream stream(line);
        // while( !stream.eof() )
        //     stream >> buff[cols*rows+temp_cols++];

        if ( temp_cols==0 )
            continue;

        if ( cols==0 )
            cols = temp_cols;

        rows++;
    }
    infile.close();

    // rows--;

    // Populate matrix with numbers.
    MatrixXd result {rows, cols};
    for ( int i=0; i<rows; i++ )
        for ( int j=0; j<cols; j++ )
            result(i,j) = buff[ cols*i+j ];

    return result;
}

int viewDistance ( MatrixXd& A ) {
    int bestview = 0;
    int dist_west = 1, dist_east = 1, dist_north = 1, dist_south = 1;

    for ( int i=1; i<A.rows()-1; ++i ) {
        for ( int j=1; j<A.cols()-1; ++j ) {
            while (j-dist_west>0 && A(i,j-dist_west) < A(i,j)) { dist_west++; } 
            while (j+dist_east<A.cols()-1 && A(i,j+dist_east) < A(i,j)) { dist_east++; } 
            while (i-dist_north>0 && A(i-dist_north, j) < A(i,j)) { dist_north++; } 
            while (i+dist_south<A.rows()-1 && A(i+dist_south, j) < A(i,j)) { dist_south++; } 

            int tmp_view = dist_west * dist_east * dist_north * dist_south;

            if ( tmp_view > bestview ) 
                bestview = tmp_view; 
            dist_west = 1, dist_east = 1, dist_north = 1, dist_south = 1;
        }
    }

    return bestview;
}

int main() {
    MatrixXd A = readMatrix("input");
    int score = viewDistance(A);
    cout << score << endl;

    return 0;
}
