#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    
    double sum = 0;
    int dataLength = argc - 1;
    if (argc == 1) {
        cout << "Please input numbers to find average.\n";
    } else {
        for (int i = 1; i <= dataLength; i++) {
            sum += atof(argv[i]);
        }
        cout << "---------------------------------\n";
        cout << "Average of " << dataLength << " numbers = ";
        cout << sum / dataLength << endl;
        cout << "---------------------------------\n";

    }

    return 0;
}
