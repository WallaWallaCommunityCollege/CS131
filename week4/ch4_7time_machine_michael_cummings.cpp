/**
 * @file ch4_7time_machine_michael_cummings.cpp
 * @author Michael Cummings
 * @date 4/23/2018
 *
 * CS131 08:30am
 * ch4_7time_machine_michael_cummings.cpp
 */
/*
 * Algorithm
 * START
 * Init start and future time structures.
 * Init lambda closures (functions) for validating hours and minutes
 * Display welcome.
 * DO
 *     Get start hour from user.
 *     Get start minutes from user.
 *     Get start am/pm from user.
 *     Get future hour from user.
 *     Get future minutes from user.
 *     Get future am/pm from user.
 *     Calculate travel time in minutes.
 *     Display travel time and travel info.
 *     Ask user if they want to do more travelling,
 * WHILE try again (more travel).
 * END
 */
#include <iostream>
// Only include in Visual Studio.
#ifdef _MSC_VER
#include <string>
#include "stdafx.h"
#endif
using namespace std;
const int MINUTES_IN_DAY = 1440;
struct time_type {
    int hour;
    int minute;
    bool isAM;
};
bool isAM();
bool tryAgain();
int computeDifference(time_type start, time_type future);
int getInput(const string &prompt, const string &badPrompt, bool (*valid)(int));
void intro();
int main() {
    // Init start and future time structures.
    time_type start = {};
    time_type future = {};
    int travelTime;
    auto checkHour = [](int value) {
        return (value >= 1 && value <= 12);
    };
    auto checkMinute = [](int value) {
        return (value >= 0 && value <= 59);
    };
    intro();
    do {
        // Get start info.
        start.hour = getInput("Enter start hour:\n", "Hour MUST be between 1 and 12\n", checkHour);
        start.minute = getInput("Enter start minutes:\n", "Minute MUST be between 0 and 59\n", checkMinute);
        start.isAM = isAM();
        // Get future info.
        future.hour = getInput("Enter future hour:\n", "Hour MUST be between 1 and 12\n", checkHour);
        future.minute = getInput("Enter future minutes:\n", "Minute MUST be between 0 and 59\n", checkMinute);
        future.isAM = isAM();
        // Calculate travel time.
        travelTime = computeDifference(start, future);
        // Display travel info.
        cout << "Travelling " << travelTime << " minutes into the future!\n" << "Travelling.\n" << "Travelling..\n"
             << "Travelling...\n" << "Travelling.....\n" << "Travelling.....\n" << "It is now the future\n"
             << "Wasn't this exciting!!!\n";
        // Ask user if they want to do more travelling,
    } while (tryAgain());
}
bool isAM() {
    string inpString;
    while (true) {
        cout << "(A)m or (P)m?:\n";
        cin >> inpString;
        if (tolower(inpString[0]) == 'a') {
            return true;
        } else if (tolower(inpString[0]) == 'p') {
            return false;
        }
        cout << "Please enter (A)m or (P)m!\n";
    }
}
bool tryAgain() {
    string inpString;
    while (true) {
        // Ask to repeat.
        cout << "Try another trip(Y/n)?:\n";
        cin >> inpString;
#ifdef _MSC_VER
        system("cls");
#endif
        if (tolower(inpString[0]) == 'n') {
            return false;
        } else if (tolower(inpString[0]) == 'y') {
            return true;
        }
        cout << "Please enter (y)es or (n)o!\n";
    }
}
int computeDifference(time_type start, time_type future) {
    // Change to 24 hour clock to make calculations easier.
    if (start.isAM) {
        // Special handling for midnight.
        if (12 == start.hour) {
            start.hour = 0;
        }
        // Else is PM and need to add 12.
    } else {
        if (start.hour < 12) {
            start.hour += 12;
        }
    }
    // Change to 24 hour clock to make calculations easier.
    if (future.isAM) {
        // Special handling for midnight.
        if (12 == future.hour) {
            future.hour = 0;
        }
        // Else is PM and need to add 12.
    } else {
        if (future.hour < 12) {
            future.hour += 12;
        }
    }
    int departTime = start.hour * 60 + start.minute;
    int arriveTime = future.hour * 60 + future.minute;
    if (arriveTime < departTime) {
        // add a day in minutes.
        arriveTime += MINUTES_IN_DAY;
    }
    return arriveTime - departTime;
}
int getInput(const string &prompt, const string &badPrompt, bool (*valid)(int)) {
    string inpString;
    int result;
    while (true) {
        cout << prompt;
        cin >> inpString;
        try {
            result = stoi(inpString);
        } catch (...) {
            cout << "Invalid number, please try again.\n";
            continue;
        }
        if (valid(result)) {
            break;
        }
        cout << badPrompt;
    }
    return result;
}
void intro() {
    cout << "Welcome to time machine control by Michael Cummings\n" << "You can travel up to 24 hours into the future\n"
         << "You will need to enter the start time and the end time you wish to go to.\n";
}
