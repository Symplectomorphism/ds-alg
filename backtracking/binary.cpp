#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

void binary(int);
void binaryHelper(string, int);

vector<string> answer;

void getStrings( string s, int digitsLeft )
{
   if( digitsLeft == 0 ) // the length of string is n
      answer.push_back( s );
   else
   {
      getStrings( s + "0", digitsLeft - 1 );
      getStrings( s + "1", digitsLeft - 1 );
   }
   cout << s << endl;
}


void binary(int n) {
    binaryHelper("", n);
}

void binaryHelper(string s, int n) {
    if ( s.length() == n )
        cout << s << endl; // print string
    else {
        s.push_back('0');
        binaryHelper(s, n);
        s.pop_back();
        s.push_back('1');
        binaryHelper(s, n);
        s.pop_back();
    }
}

int main() {
    binary(3);
    // getStrings( "", 3 ); 
    return 0;
}
