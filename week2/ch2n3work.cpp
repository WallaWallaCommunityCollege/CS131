/**
 * @file ch2n3work.cpp
 * @author Michael Cummings
 * @date 4/13/2018
 *
 * CS131 08:30am
 * ch2n3work.cpp
 */
// Ch2n3Work.cpp : Defines the entry point for the console application.
// Inclass by: Robin Greene
// Modified by: Michael Cummings
//

#include <iostream>
#include <string>

using namespace std;
int main() {
    //Declare Vars
    int amount, bonus, count, change, cnt1, cnt2;
    double total, discount, time, rush_factor;
    //Initialize Vars
    amount = 1;
    bonus = 10;
    change = 25;
    cnt1 = 2;
    cnt2 = 3;
    count = 0;
    discount = 7.55;
    total = 100.50;
    rush_factor = 15;
    time = 120;
    string ans;
    do {
        for (int i = 0; i < 5; ++i) {
            //Calculations
            count += 2;            //count = count + 2;
            total -= discount; //total = total – discount;
            bonus *= 2;            //bonus = bonus * 2;
            time /= rush_factor; //time = time / rush_factor;
            change %= 100;        //change = change % 100;
            amount *= cnt1 + cnt2; //amount = amount * (cnt1 + cnt2);
            // Pretty up printing of doubles.
            cout.setf(ios::fixed);
            cout.setf(ios::showpoint);
            cout.precision(2);
            //Output
            cout << "The count += 2 value is: " << count << endl;
            cout << "The total – discount value is: " << total << endl;
            cout << "The bonus value is: " << bonus << endl;
            cout << "The time value is: " << time << endl;
            cout << "The change value is: " << change << endl;
            cout << "The amount value is: " << amount << endl;
        }
        cout << "Hello\n";
        cout << "Do you want another greeting?\n" << "Press y for yes, n for no,\n" << "and then press return: ";
        cin >> ans;
    } while (ans[0] == 'y' || ans[0] == 'Y');
    cout << "Good-Bye\n";
    return 0;
}


