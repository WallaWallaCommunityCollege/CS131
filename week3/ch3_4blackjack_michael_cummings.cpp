/**
 * @file ch3_4blackjack_michael_cummings.cpp
 * @author Michael Cummings
 * @date 2018-04-15
 *
 * CS131 08:30am
 * ch3 project 4 blackjack
 */
#include <iostream>
// Needed for sort.
#include <algorithm>
// Needed to hold cards.
#include <array>
// Only include in Visual Studio.
#ifdef _MSC_VER
#include "stdafx.h"
#endif
/*
 * Algorithm
 * START
 * Prompt user for number of cards.
 * Prompt user for each card.
 * Sort cards.
 * Add up cards while handle special case for aces.
 * Display total.
 * Display win or busted.
 * Prompt user to try again.
 * END
 */
using namespace std;
/**
 * Prompts user for range validated string input.
 *
 * @param prompt Initial prompt for value.
 * @param badPrompt Bad value prompt.
 */
int getCard(const string &prompt, const string &badPrompt);
/**
 * Prompts user for range validated double input.
 *
 * @param prompt Initial prompt for value.
 * @param badPrompt Bad value prompt.
 * @param valid Function pointer to validator which takes double as param and returns bool.
 * @returns int
 */
int getInput(const string &prompt, const string &badPrompt, bool (*valid)(int value));
int main() {
    cout << "Welcome to Blackjack by Michael Cummings.\n" << "You will be allowed to enter between 2 and 5 cards.\n"
         << "Enter the numbers 2 - 9, (t)en for 10, (j)ack, (q)ueen, (k)ing, or (a)ce.\n" << "Good luck!!!\n";
    // vars for user input and input prompting.
    string inpString, prompt, badPrompt;
    int numberOfCards, total;
    // Use array to hold cards.
    array<int, 5> cards = {0, 0, 0, 0, 0};
    // Init lambda closure (function).
    auto checkNumberOfCards = [](int value) {
        return (value >= 2 && value <= 5);
    };
    // Play again loop.
    do {
        // (Re-)initialize card array to 0.
        cards.fill(0);
        // (Re-)initialize total to 0.
        total = 0;
        // Prompt and get number of cards the user will be entering.
        prompt = "Enter number of cards (2-5):\n";
        badPrompt = "Number MUST be between 2 and 5(inclusively)\n";
        numberOfCards = getInput(prompt, badPrompt, checkNumberOfCards);
        badPrompt = "MUST enter 2-9, (t)en, (j)ack, (q)ueen, (k)ing, (a)ce\n";
        // Per card prompt user loop.
        for (int i = 0; i < numberOfCards; ++i) {
            prompt = "Enter card " + to_string(i + 1) + ":\n";
            cards[i] = getCard(prompt, badPrompt);
        }
        // Sort cards to make handling aces easier.
        sort(cards.begin(), cards.end());
        // Range (Iterator) for loop to total up cards.
        for (int &card : cards) {
            // Special ace handling.
            if (total > 10 && 11 == card) {
                card = 1;
            }
            total += card;
        }
        // Output total.
        cout << "Total = " << total << endl;
        if (total <= 21) {
            cout << " You won!!!\n";
        } else {
            cout << "BUSTED!\n";
        }
        // Ask to repeat.
        cout << "Try another hand(Y/n)?:\n";
        cin >> inpString;
#ifdef _MSC_VER
        system("cls");
#endif
    } while (tolower(inpString[0]) != 'n');
}
int getCard(const string &prompt, const string &badPrompt) {
    string inpString;
    while (true) {
        cout << prompt;
        cin >> inpString;
        // Just check first char and return as int value.
        switch (tolower(inpString[0])) {
            case 't':
            case 'j':
            case 'q':
            case 'k':
                return 10;
            case 'a':
                return 11;
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return inpString[0] - '0';
            default:
                break;
        };
        cout << badPrompt;
    }
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
