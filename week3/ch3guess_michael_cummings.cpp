/**
 * @file ch3guess_michael_cummings.cpp
 * @author Michael Cummings
 * @date 2018-04-15
 *
 * CS131 08:30am
 * ch3 guess game.
 */
/*
 * Algorithm
 * START
 * Init global var.
 * Declare local vars.
 * Init lambda closures.
 * Init random number generator.
 * DO
 *     Prompt user for range to use.
 *     Set random secret.
 *     Set tries and max tries.
 *     DO
 *         Prompt user for guess.
 *         IF secret < guess
 *             Output lower hint.
 *         ELSE IF secret > guess
 *             Output higher hint.
 *         ELSE
 *             Output congrats.
 *     WHILE guess is wrong and tries <= max tries.
 *     Prompt try again.
 * WHILE user says yes.
 * END
 */

#include <iostream>
#include <random>
// Only include in Visual Studio.
#ifdef _MSC_VER
#include "stdafx.h"
#endif
using namespace std;
/**
 * Init global var.
 */
int range = 10;
/**
 * Prompts user for range validated integer input.
 *
 * @param prompt Initial prompt for value.
 * @param badPrompt Bad value prompt.
 * @param valid Function pointer to validator which takes int as param and returns bool.
 * @returns int
 */
int getInput(const string &prompt, const string &badPrompt, bool (*valid)(int value));
/**
 * Main function for guessing game.
 *
 * @return int
 */
int main() {
#ifdef _MSC_VER
    system("cls");
#endif
    cout << "Guessing Game by Michael Cummings\n"
         << "For a short, easy game enter a range of 10 but for a longer, harder game try 25\n" << "Good luck!!!\n";
    // Declare local vars.
    string inpString, prompt, badPrompt;
    int guess, secret, tries, maxTries;
    // Init lambda closures (functions).
    auto checkRange = [](int value) {
        return (value >= 10 && value <= 100);
    };
    auto checkRangeOfGuesses = [](int value) {
        return (value >= 1 && value <= range);
    };
    // Init random seed.
    srand((unsigned int) time(0));
    do {
        // Set needed prompts and get range.
        prompt = "Set guessing range (10 - 100):\n";
        badPrompt = "Range MUST be between 10 and 100\n";
        range = getInput(prompt, badPrompt, checkRange);
        /* Generate secret number between 1 and range. */
        secret = rand() % range + 1; // NOLINT
        // Used to limit number of tries the user gets.
        tries = 0;
        maxTries = range / 4;
        do {
            // Change prompt for last guess.
            if (tries != maxTries) {
                prompt = "Guess the number (1 to " + to_string(range) + "):\n";
            } else {
                prompt = "Last guess:\n";
            }
            badPrompt = "Range MUST be between 10 and " + to_string(range) + "\n";
            guess = getInput(prompt, badPrompt, checkRangeOfGuesses);
            if (secret < guess) {
                cout << "The secret number is lower\n";
            } else if (secret > guess) {
                cout << "The secret number is higher\n";
            } else {
                cout << "Congratulations!\n";
            }
        } while (secret != guess && tries++ < maxTries);
        cout << "The secret number was " << secret << endl;
        /*
         * Ask to repeat.
         */
        cout << "Try again (Y/n)?:\n";
        cin >> inpString;
    } while (inpString[0] != 'n');
    return 0;
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
