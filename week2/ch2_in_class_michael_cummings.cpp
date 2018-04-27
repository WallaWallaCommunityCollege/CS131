/**
 * @file ch2_in_class_michael_cummings.cpp
 * @author Michael Cummings
 * @date 2018-04-10
 *
 * CS131 08:30am
 * Ch 2 in class
 */
#include <iostream>
#include <cmath>
/*
 * Algorithm
 * START
 * Prompt user for angle in degrees.
 * Prompt user for side length.
 * Calculate other angle, side, and hypotenuse, etc.
 * Display results.
 * END
 */
using namespace std;
/**
 * Prompts user for range validated double input.
 *
 * @param [in,out] result Returned value.
 * @param prompt Initial prompt for value.
 * @param badPrompt Bad value prompt.
 * @param valid Function pointer to validator which takes double as param and returns bool.
 */
void getInput(double &result, const string &prompt, const string &badPrompt, bool (*valid)(double value));
/**
 * Check that value (angle) is between 0 and 90 degrees(exclusively).
 * @param value
 * @return bool
 */
bool validAngle(double value);
/**
 * Check if side is a positive number.
 * @param value
 * @return bool
 */
bool validSide(double value);
/**
 * Solves right triangle given an angle and it's side.
 * @return int
 */
int main() {
    // Pretty up printing of doubles.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    double angleA, sideA, angleB, sideB, sideC;
    bool (*checkAngle)(double);
    bool (*checkSide)(double);
    checkAngle = &validAngle;
    checkSide = &validSide;
    /**
     * Temp input variable.
     */
    string inpString;
    do {
        cout << "Press 'return' after entering values.\n";
        string prompt = "Angle in degrees:\n";
        string badPrompt = "Angle MUST be greater than 0 and less than 90!\n";
        getInput(angleA, prompt, badPrompt, checkAngle);
        prompt = "Length of opposite side:\n";
        badPrompt = "Side MUST be greater than 0!\n";
        getInput(sideA, prompt, badPrompt, checkSide);
        // Calculate other angle and convert to radians.
        angleB = (90.0 - angleA);
        // Convert angle to radians to do calculation.
        sideB = sideA / tan(angleA * M_PI / 180.0);
        sideC = sqrt(pow(sideA, 2) + pow(sideB, 2));
        cout << "Given angle a = " << angleA << endl;
        cout << "angle b = " << angleB << endl;
        cout << "angle c = " << 90.0 << endl;
        cout << "Given side a = " << sideA << endl;
        cout << "side b = " << sideB << endl;
        cout << "side c (hypotenuse) = " << sideC << endl;
        int diff, remain;
        diff = (int) sideC / (int) sideA;
        remain = (int) sideC % (int) sideA;
        cout << "The integer ratio of side c (hypotenuse) to the given side is " << diff << " with a remainder of "
             << remain << endl;
        /*
         * Ask to repeat.
         */
        cout << "Solve another triangle(Y/n)?:\n";
        cin >> inpString;
    } while (inpString[0] != 'n');
}
void getInput(double &result, const string &prompt, const string &badPrompt, bool (*valid)(double)) {
    string inpString;
    while (true) {
        cout << prompt;
        cin >> inpString;
        try {
            result = stod(inpString);
        } catch (...) {
            cout << "Invalid number, please try again.\n";
            continue;
        }
        if (valid(result)) {
            break;
        }
        cout << badPrompt;
    }
}
bool validAngle(double value) {
    return (value > 0.0 && value < 90.0);
}
bool validSide(double value) {
    return (value > 0.0);
}
