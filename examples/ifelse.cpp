#include <iostream>

using namespace std;

int main() {
    int x;

    cout << "Enter a number: ";
    cin >> x;

    if (x > 10) {
        cout << "Greater than 10" << endl;
    } else {
        cout << "10 or smaller" << endl;
    }

    return 0;
}