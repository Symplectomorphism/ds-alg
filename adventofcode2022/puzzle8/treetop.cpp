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

int countVisible( MatrixXd& A ) {
    int vis_count = 0;
    int max_west = 0, max_east = 0, max_north = 0, max_south = 0;

    for ( int i=1; i<A.rows()-1; ++i ) {
        for ( int j=1; j<A.cols()-1; ++j ) {
            auto it = max_element( A(i, seq(0, j-1)).begin(), A(i, seq(0, j-1)).end() );
            max_west = *it;
            it = max_element( A(i, seq(j+1, last)).begin(), A(i, seq(j+1, last)).end() );
            max_east = *it;
            auto iter = max_element( A(seq(0, i-1), j).begin(), A(seq(0, i-1), j).end() );
            max_north = *iter;
            iter = max_element( A(seq(i+1, last), j).begin(), A(seq(i+1, last), j).end() );
            max_south = *iter;
// 
            if ( max_west < A(i,j) || max_east < A(i,j) || max_north < A(i,j) || max_south < A(i,j) )
                vis_count++;
        }
    }

    return vis_count + 2*(A.rows()-1) + 2*(A.cols()-1);
}

int main() {
    MatrixXd A = readMatrix("input");
    cout << A.rows() << " " << A.cols() << endl;
    int vis_count = countVisible(A);
    cout << vis_count << endl;

    return 0;
}
