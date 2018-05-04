/**
 * @file ch6_2scores_michael_cummings.cpp
 * @author Michael Cummings
 * @date 5/1/2018
 *
 * CS131 08:30am
 * ch6_2scores_michael_cummings.cpp
 */
/*
 * Algorithm
 * START
 * Declare global structs. One for input and one for output.
 * Declare functions used.
 * Declare/Init vars.
 * Display intro.
 * DO
 *     Get input and output path and file names from user.
 *     WHILE NOT end of input file.
 *         (Re-)Initialize input struct and total.
 *         Get row from input file.
 *         IF input row is not empty.
 *         THEN
 *             Calculate total from scores in input row.
 *             Cast input row to output row and add grade.
 *             Display output row.
 *             Write output row to output file.
 *     Close file handles.
 * WHILE User wants to continue.
 * END
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <algorithm>
// Only include in Visual Studio.
#ifdef _MSC_VER
#include <string>
#include "stdafx.h"
#endif
using namespace std;
/**
 * @brief Structure to hold one row of student's scores and grade.
 *
 * This is used while write to output file.
 */
struct GradeRow {
    string firstName;
    string lastName;
    // Initialize score vector since not done by default like simple types.
    vector<int> scores = vector<int>();
    // Initialize to make CLang-Tidy happy.
    double grade = 0.0;
};

/**
 * @brief Structure to hold one row of student's scores.
 *
 * This is used while read from the input stream.
 */
struct ScoreRow {
    string firstName;
    string lastName;
    // Initialize score vector since not done by default like simple types.
    vector<int> scores = vector<int>();
    /**
     * @brief Used to explicit casting to a GradeRow.
     *
     * Overloading casting to allow converting ScoreRow structure into GradeRow which has addition 'grade' field.
     *
     * @return GradeRow
     */
    explicit operator GradeRow() {
        GradeRow gr;
        gr.lastName = lastName;
        gr.firstName = firstName;
        gr.scores = scores;
        gr.grade = 0.0;
        return gr;
    }
};

/**
 * @brief Prompt and valid if user want to continue.
 *
 * @return bool
 */
bool tryAgain();
/**
 * @brief Overloading stream '>>' operator to accept ScoreRow structure.
 *
 * Allow direct inputting of ScoreRow structure from any stream just like built-in types.
 *
 * Preconditions: N/A overloading existing operator for istream. Everything is pass by ref.
 * Postconditions: Must return stream so it can be chained.
 *
 * @param is
 * @param row
 * @return istream
 */
std::istream &operator>>(std::istream &is, ScoreRow &row);
/**
 * @brief Overloading stream '<<' operator to accept ScoreRow structure.
 *
 * Preconditions: N/A overloading existing operator for ostream. Everything is pass by ref.
 * Postconditions: Must return stream so it can be chained.
 *
 * @param os
 * @param row
 * @return ostream
 */
std::ostream &operator<<(std::ostream &os, const ScoreRow &row);
/**
 * @brief Overloading stream '<<' operator to accept GradeRow structure.
 *
 * Preconditions: N/A overloading existing operator for ostream. Everything is pass by ref.
 * Postconditions: Must return stream so it can be chained.
 *
 * @param os
 * @param row
 * @return istream
 */
std::ostream &operator<<(std::ostream &os, const GradeRow &row);
/**
 * @brief Output brief intro to program for user.
 */
void intro();
/**
 * @brief Cross platform get current working directory.
 *
 * Taken from
 * https://stackoverflow.com/questions/2869594/how-return-a-stdstring-from-cs-getcwd-function/2869667
 *
 * Preconditions: N/A
 * Postconditions: N/A
 *
 * @return string
 */
string getCwd();
/**
 * @brief Get path and name of input or output file from user.
 *
 * Preconditions: None
 * Postconditions: None
 *
 * @param prompt Prompt to show user.
 * @param defaultFile Default path and file name if user just hits enter.
 *
 * @return string Returns the path and file name.
 */
string getPathName(const string &prompt, const string &defaultFile);
/**
 * @brief Get path and file name of input file from user and open it.
 *
 * Preconditions: None
 * Postconditions: None
 *
 * @param fin Stream handle to use.
 * @param mess Prompt shown to user when getting path and file name.
 * @param defaultFile Default path and file name that will be used if user just hits enter.
 */
void openInputFile(ifstream &fin, const string &mess, const string &defaultFile);
/**
 * @brief Get path and file name of output file from user and open it.
 *
 * Preconditions: None
 * Postconditions: None
 *
 * @param fout Stream handle to use.
 * @param mess Prompt shown to user when getting path and file name.
 * @param defaultFile Default path and file name that will be used if user just hits enter.
 */
void openOutputFile(ofstream &fout, const string &mess, const string &defaultFile);
/**
 * @brief Main program (Application).
 *
 * @return int
 */
int main() {
    ScoreRow iRow;
    GradeRow oRow;
    double total;
    string defaultFile, mess, pathFileName = "";
    ifstream fin;
    ofstream fout;
    // Pretty up printing of doubles to cout.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    intro();
    // Another file?
    do {
        defaultFile = getCwd() + "/scores.dat";
        mess = "Path and file name of scores file to process (" + defaultFile + "):\n";
        // Re-prompt user as needed to get an usable input file and opens it.
        openInputFile(fin, mess, defaultFile);
        cout << "Inputting scores from " << pathFileName << endl;
        defaultFile = getCwd() + "/result.dat";
        mess = "Path and file name of result output file (" + defaultFile + "):\n";
        // Re-prompt user as needed to get an usable output file.
        openOutputFile(fout, mess, defaultFile);
        cout << "Outputting scores to " << pathFileName << endl;
        // Loop until end of input file.
        while (!fin.eof()) {
            // (Re-)initialize structure for each row.
            iRow.lastName = "";
            iRow.firstName = "";
            iRow.scores.clear();
            // Reset running total.
            total = 0.0;
            // Get ScoreRow structure using overloaded stream '>>' operator.
            // Allows missing scores per Project 3 enhancement.
            fin >> iRow;
            // Only output lines with name and scores.
            // Ignores any empty lines etc.
            if ("" != iRow.lastName || !iRow.scores.empty()) {
                // Iterator for loop over scores.
                for (int &score : iRow.scores) {
                    // Calculate total.
                    total += score;
                }
                // Use explicit cast from ScoreRow to GradeRow.
                oRow = static_cast<GradeRow>(iRow);
                // Add the calculated grade to structure for output.
                oRow.grade = total / 10.0;
                cout << oRow;
                fout << oRow;
            }
        }
        // Close out file handles.
        fin.close();
        fout.close();
    } while (tryAgain());
    #ifdef _MSC_VER
    system("pause");
    #endif
    exit(0);
}
bool tryAgain() {
    string inpString;
    while (true) {
        // Ask to repeat.
        cout << "Try again(Y/n)?:\n";
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
std::istream &operator>>(std::istream &is, ScoreRow &row) {
    int score = 0;
    // Use noskipws to manually manage white space skipping.
    is >> noskipws >> ws >> row.lastName >> ws >> row.firstName;
    // Insure not skipping over to next line or already at end of file while reading in scores.
    while ('\n' != is.peek() && EOF != is.peek()) {
        is >> ws >> score;
        row.scores.push_back(score);
    }
    return is;
}
std::ostream &operator<<(std::ostream &os, const GradeRow &row) {
    // Write last and first names with single space between them.
    os << row.lastName << " " << row.firstName;
    // Loop through and write scores with single space between.
    for (const int &score : row.scores) {
        os << " " << score;
    }
    // Write space grade and end of line.
    os << " " << row.grade << endl;
    // Must return stream.
    return os;
}
std::ostream &operator<<(std::ostream &os, const ScoreRow &row) {
    // Write last and first names with single space between them.
    os << row.lastName << " " << row.firstName;
    // Loop through and write scores with single space between.
    for (const int &score : row.scores) {
        os << " " << score;
    }
    // Write final end of line.
    os << endl;
    // Must return stream.
    return os;
}
string getPathName(const string &prompt, const string &defaultFile) {
    char inp = ' ';
    string pathFileName = "";
    cout << prompt;
    do {
        cin.get(inp);
        if (isprint(inp)) {
            pathFileName += inp;
        }
    } while ('\n' != inp);
    if (0 == pathFileName.length()) {
        pathFileName = defaultFile;
    }
    return pathFileName;
}
string getCwd() {
    // Start with 1kB buffer.
    string result(1024, '\0');
    // test and continue to increase buffer size until big enough for path.
    while (getcwd(&result[0], result.size()) == 0) {
        if (errno != ERANGE) {
            // Bomb out for any unexpected errors.
            throw std::runtime_error(strerror(errno));
        }
        result.resize(result.size() * 2);
    }
    // Resize buffer to actual string size before returning.
    result.resize(result.find('\0'));
    return result;
}
void intro() {
    cout << "Welcome to score grading program by Michael Cummings.\n"
         << "You will be prompted for a score input directory/file name and output directory/file name to use.\n";
}
void openInputFile(ifstream &fin, const string &mess, const string &defaultFile) {
    string pathFileName;
    // Loop until user inputs a good path and file name.
    while (true) {
        // Call out to function to process getting path and file name.
        pathFileName = getPathName(mess, defaultFile);
        // Try to open the input file.
        fin.open(pathFileName);
        // Done if open didn't fail.
        if (!fin.fail()) {
            break;
            // If fails to open file tell user and prompt user to enter path and file name again.
        } else {
            cout << "Failed to open input scores file: " << pathFileName << endl;
            cout << "Check that path and file name are correct\n";
        }
    }
}
void openOutputFile(ofstream &fout, const string &mess, const string &defaultFile) {
    string pathFileName;
    // Loop until user inputs a good path and file name.
    while (true) {
        // Call out to function to process getting path and file name.
        pathFileName = getPathName(mess, defaultFile);
        // Try to open the input file.
        fout.open(pathFileName);
        // Done if open didn't fail.
        if (!fout.fail()) {
            break;
            // If fails to open file tell user and prompt user to enter path and file name again.
        } else {
            cout << "Failed to open output result file: " << pathFileName << endl;
            cout << "Check that path and file name are correct\n";
        }
    }
    // Insures pretty output of doubles to file stream.
    fout.setf(ios::fixed);
    fout.setf(ios::showpoint);
    fout.precision(2);
}
