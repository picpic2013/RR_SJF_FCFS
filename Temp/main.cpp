#include <iostream>
#include "JCB.h"

using namespace std;
int main() {
    cout << "Hello World!" << endl;
    DateTime d;
    for (int i = 0; i < 200; i++) {
        cout << d << endl;
        d.tickHour();
    }
    
}
