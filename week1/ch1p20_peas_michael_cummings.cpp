/*
 * Michael Cummings
 * CS-131 08:30am
 * Inclass First C++ Program page 20
 * Data: 20180404
 */
#include <iostream>

using namespace std;
int main() {
    int number_of_pods, peas_per_pod, total_peas;
    char dummy;
    cout << "Press return after entering number.\n";
    cout << "Enter the number of pods: ";
    cin >> number_of_pods;
    cout << "\nEnter number of peas in a pod: ";
    cin >> peas_per_pod;
    total_peas = number_of_pods * peas_per_pod;
    cout << "\nIf you have " << number_of_pods << " pea pods\n";
    cout << "and " << peas_per_pod << " peas in each pod, then\n";
    cout << "you have " << total_peas << " peas in all the pods.\n";
    cin >> dummy;
    return 0;
}
