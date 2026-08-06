#include <iostream>

using namespace std;

int main() {
    int total = 0;
    
    for (int i = 0; i < 1000000; i++) {
        total += i;
    }
    
    cout << "Total sum: " << total << endl;
    
    return 0;
}
