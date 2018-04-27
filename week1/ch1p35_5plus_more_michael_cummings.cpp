/*
 * Michael Cummings
 * CS-131 08:30am
 * Ch1p35_5PlusMore
 * Data: 20180404
 */
#include <iostream>

using namespace std;
/*
 * Takes width and height of area in feet and calculates amount of fencing needed.
 */
int main() {
    // Pretty up printing of doubles.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);
    // Declare vars
    double width, height, totalLength;
    // Dummy var used when pausing program.
    char dummy;
    // Prompt user
    cout << "Press 'return' after entering numbers.\n";
    cout << "Enter the width of area in feet:\n";
    // Get input
    cin >> width;
    // Prompt user
    cout << "\nEnter height of area in feet:\n";
    // Get input
    cin >> height;
    // Calculate
    totalLength = width * 2 + height * 2;
    // Output
    cout << "\nIf you have an area with width " << width << " feet\n";
    cout << "and a height of " << height << " feet, then\n";
    cout << "you need a total of " << totalLength << " feet of fencing to enclose it.\n";
    // Wait to continue
    do {
        cout << "Enter 'x' to exit or 'c' to continue then 'return':\n";
        cin >> dummy;
        if ('x' == dummy) {
            return 0;
        }
    } while ('c' != dummy);
    // Plus more
    cout << "\nPlus more stuff just for Robin!!!\n\n";
    cout << "The sum of the width and height is " << (width + height) << endl;
    cout << "The diff of the width and height is " << (width - height) << endl;
    cout << "The area of the width and height is " << (width * height) << " sq. feet\n";
    cout << "The ratio of the width and height is " << (width / height) << endl;
    cout << "Done.\n";
    // Wait to continue
    do {
        cout << "Enter 'x' to exit or 'c' to continue then 'return':\n";
        cin >> dummy;
        if ('x' == dummy) {
            return 0;
        }
    } while ('c' != dummy);
    return 0;
}
