/**
 * @file ch2_6pay_michael_cummings.cpp
 * @author Michael Cummings
 * @date 2018-04-07
 *
 * CS131 08:30am
 * Ch 2 Project 6 Pay
 */
#include <iostream>
#include <cmath>
/*
 * Algorithm
 * START
 * DO
 *     Prompt user for hours worked and number of dependants.
 *     Calculate gross pay.
 *     Display gross pay.
 *     Calculate Taxes.
 *     Display taxes.
 *     Calculate net pay from gross pay and taxes.
 *     Calculate net pay after union dues.
 *     Display union dues.
 *     IF number of dependants is > maximum free dependants
 *     THEN
 *         Display additional dependant insurance fee.
 *         IF number of dependants > 8
 *         THEN
 *             Display rabbit message.
 *         Calculate net pay - fee.
 *     IF net pay >= 0.0
 *     THEN
 *         Display net pay.
 *     ELSE
 *         Display shake down.
 *     Prompt to do another employee.
 * WHILE input != 'n'
 * END
 */
using namespace std;
/**
 * A couple of useful constants.
 *
 * @var
 */
const unsigned int MAX_REGULAR_HOURS = 40, MAX_HOURS_IN_WEEK = 168, MAX_FREE_DEPENDANTS = 2;
/**
 * Structure to hold all the required tax information.
 *
 * @author Michael Cummings
 * @date 2018-04-07 08:30am
 */
struct taxes_type {
    double federal, socialSecurity, state;
};
// Forward declare display tax function.
void displayTaxes(taxes_type taxes);
double getDoubleInput(const string &prompt, const string &badPrompt, bool (*valid)(double));
int getIntInput(const string &prompt, const string &badPrompt, bool (*valid)(int));
double
calcNetPay(double grossPay, taxes_type taxAmounts, double unionDues, double numOfDependants, double depInsuranceFees);
/**
 * Calculates pay and taxes given hours worked and # of dependants.
 *
 * @author Michael Cummings
 * @date 2018-04-07 08:30am
 */
int main() {
    // Pretty up printing of doubles.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    /**
     * Set tax rates.
     * @var
     */
    taxes_type taxRates = {0.14, 0.06, 0.05};
    double depInsuranceFees = 35.0,/// Extra fee charged for more than 2 dependants.
        grossPay = 0.0,/// Gross pay.
        hourlyWage = 16.78,/// Hourly wage.
        hoursWorked = 0.0,/// Weekly hours worked.
        netPay = 0.0,/// Net pay after subtractions.
        overTimeRate = 0.5,/// Rate for overtime pay.
        unionDues = 10.0;/// Union dues.
    auto checkHours = [](double value) {
        return (value >= 0.0 && value <= MAX_HOURS_IN_WEEK);
    };
    auto checkDependants = [](int value) {
        return value > 0;
    };
    /**
     * Temp input variable.
     */
    string inpString;
    /**
     * Number of dependants.
     */
    int numOfDependants;
    // Allow user to process another person.
    do {
        cout << "Press 'return' after entering values.\n";
        /*
         * Get weekly hours.
         */
        string prompt = "Hours worked this week?\n";
        string badPrompt = "Hours worked MUST be >= 0 and < ";
        badPrompt += to_string(MAX_HOURS_IN_WEEK) + "!\n";
        hoursWorked = getDoubleInput(prompt, badPrompt, checkHours);
        /*
         * Get number of dependants.
         */
        prompt = "Number of dependants (including self)?\n";
        badPrompt = "Number of dependants MUST be greater than 0!\n";
        numOfDependants = getIntInput(prompt, badPrompt, checkDependants);
        // Calculate gross pay.
        grossPay = hourlyWage * hoursWorked;
        // Any overtime pay?
        if (hoursWorked > MAX_REGULAR_HOURS) {
            // Add the extra overtime pay.
            grossPay += hourlyWage * overTimeRate * (hoursWorked - MAX_REGULAR_HOURS);
        }
        // Display gross pay.
        cout << "Gross pay is $" << grossPay << endl;
        // Calculate the taxes amounts and display them.
        taxes_type
            taxAmounts = {grossPay * taxRates.socialSecurity, grossPay * taxRates.federal, grossPay * taxRates.state};
        displayTaxes(taxAmounts);
        netPay = calcNetPay(grossPay, taxAmounts, unionDues, numOfDependants, depInsuranceFees);
        // Display final net pay.
        if (netPay >= 0.0) {
            cout << "Net pay is $" << netPay << endl;
        } else {
            netPay = abs(netPay);
            cout << "Employee owes the company $" << netPay << ", please have security shake them down!!!\n";
        }
        cout << "Process another(Y/n):\n";
        cin >> inpString;
    } while (tolower(inpString[0]) != 'n');
}
double
calcNetPay(double grossPay, taxes_type taxAmounts, double unionDues, double numOfDependants, double depInsuranceFees) {
    // Subtract taxes and union dues.
    double netPay = grossPay - taxAmounts.socialSecurity - taxAmounts.federal - taxAmounts.state;
    netPay -= unionDues;
    cout << "Union dues $" << unionDues << endl;
    if (numOfDependants > MAX_FREE_DEPENDANTS) {
        cout << "Additional dependants insurance fee $" << depInsuranceFees << " for " << numOfDependants
             << " dependants.\n";
        if (numOfDependants > 8) {
            cout << "Check with insurance company if employees can be rabbits!\n";
        }
        netPay -= depInsuranceFees;
    }
}
/**
 * Display all the tax information.
 *
 * @author Michael Cummings
 * @date 2018-04-08
 * @param taxes Tax structure to display.
 */
void displayTaxes(taxes_type taxes) {
    cout << "Social Security taxes $" << taxes.socialSecurity << endl;
    cout << "Federal taxes $" << taxes.federal << endl;
    cout << "State taxes $" << taxes.state << endl;
}
/**
 * Get weekly hours.
 *
 * @param prompt Initial prompt for value.
 * @param badPrompt Bad value prompt.
 */
double getDoubleInput(const string &prompt, const string &badPrompt, bool (*valid)(double)) {
    string inpString;
    double result;
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
    return result;
}
/**
 * Get number of dependants.
 *
 * @param prompt Initial prompt for value.
 * @param badPrompt Bad value prompt.
 */
int getIntInput(const string &prompt, const string &badPrompt, bool (*valid)(int)) {
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
            // Exclude self for calculations.
            result--;
            break;
        }
        cout << badPrompt;
    }
    return result;
}
