/**
 * @file ch5_4coin_michael_cummings.cpp
 * @author Michael Cummings
 * @date 4/26/2018
 *
 * CS131 08:30am
 * ch5_4coin_michael_cummings.cpp
 */
/*
 * Algorithm
 * START
 * Init global constants for coins types.
 * Show intro.
 * Init vars.
 * DO
 *     Get cents value from user.
 *     FOREACH coin type
 *         Compute number of coins.
 *         Display num of coins needed for type.
 * WHILE User wants to continue.
 * END
 */
#include <iostream>
#include <array>
// Only include in Visual Studio.
#ifdef _MSC_VER
#include <string>
#include "stdafx.h"
#endif
using namespace std;
const int QUARTER = 25;
const int DIME = 10;
const int PENNY = 1;
/**
 *
 * @param coin_value int
 * @param num int
 * @param amount_left int
 *
 * @throws out_of_range
 */
void compute_coins(int coin_value, int &num, int &amount_left);
/**
 * @brief  Get and validate int input.
 *
 * @param prompt const string
 * @param badPrompt const string
 * @param valid function
 *
 * @return int
 */
int getInput(const string &prompt, const string &badPrompt, bool (*valid)(int));
void intro();
/**
 * @brief Prompt and valid if user want to continue.
 *
 * @return bool
 */
bool tryAgain();
/**
 * @brief  Main function that starts program.
 *
 * @return int
 */
int main() {
    intro();
    int amount_left, coin_value, num;
    array<int, 3> coins = {QUARTER, DIME, PENNY};
    auto checkAmount = [](int value) {
        return (0 <= value && 100 > value);
    };
    do {
        num = 0;
        amount_left =
            getInput("Enter amount in cents:\n",
                     "MUST enter amount as integer number of cents(pennies)\n",
                     checkAmount);
        // FOREACH coin type
        for (int &coin: coins) {
            try {
                compute_coins(coin, num, amount_left);
            } catch (out_of_range e) {
                cout << "The following exception happened: \n" << e.what() << endl;
            }
            switch (coin) {
                case QUARTER:
                    cout << num << " quarters\n";
                    break;
                case DIME:
                    cout << "and " << num << " dimes\n";
                    break;
                default:
                    cout << "and " << num << " pennies\n";
            }
        }
    } while (tryAgain());
}
/**
 *
 * Precondition: 0 < coin_value < 100; 0 <= amount_left < 100.
 *
 * Postcondition: num has been set equal to the maximum number
 * of coins of denomination coin_value cents that can be obtained
 * from amount_left. Additionally, amount_left has been decreased
 * by the value of the coins, that is, decreased by
 * num * coin_value.
 *
 * @param coin_value
 * @param num
 * @param amount_left
 *
 * @throws out_of_range
 */
void compute_coins(int coin_value, int &num, int &amount_left) {
    if (0 >= coin_value || coin_value > 100) {
        const char *mess = "Coin value MUST be between 0 and 100";
        throw out_of_range(mess);
    }
    if (0 >= amount_left || amount_left > 100) {
        const char *mess = "Amount left MUST be between 0 and 100";
        throw out_of_range(mess);
    }
    if (amount_left >= coin_value) {
        num = amount_left / coin_value;
        amount_left %= coin_value;
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
void intro() {
    cout << "Welcome to coin changer by Michael Cummings\n"
         << "You can enter any amount under $1 and I'll tell you what coins you need to make the change\n";
}
bool tryAgain() {
    string inpString;
    while (true) {
        // Ask to repeat.
        cout << "Try another amount(Y/n)?:\n";
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
