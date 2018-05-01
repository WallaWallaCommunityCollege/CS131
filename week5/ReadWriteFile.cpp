//DISPLAY 6.1 Simple File Input/Output
//Reads three numbers from the file infile.dat, sums the numbers,
//and writes the sum to the file outfile.dat.
//(A better version of this program will be given in Display 6.2.)
#include <fstream>
#include <iostream>
// Only include in Visual Studio.
#ifdef _MSC_VER
#include <string>
#include "stdafx.h"
#endif
using namespace std;
int main() {
    using namespace std;
    ifstream in_stream;
    ofstream out_stream;
    in_stream.open("infile.dat");
    if (in_stream.fail()) {
        cout << "Input file opening failed.\n";
        exit(1);
    }
    out_stream.open("outfile.dat");
    if (out_stream.fail()) {
        cout << "Output file opening failed.\n";
        exit(1);
    }
    int first, second, third, forth;
    in_stream >> first >> second >> third >> forth;
    out_stream << "The sum of the first 4\n" << "numbers in infile.dat\n" << "is " << (first + second + third + forth)
               << endl;
    in_stream.close();
    out_stream.close();
    return 0;
}
