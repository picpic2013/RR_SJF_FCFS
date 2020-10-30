#include <iostream>
#include "JCB.h"

using namespace std;
int main() {
    cout << "Hello World!" << endl;
    DateTime d = DateTime(-59);
    DateTime b;
    /*for (int i = 0; i < 200; i++) {
        int dd = d;
        DateTime ddd = DateTime(d);
        DateTime dddd = DateTime(dd);
        cout << d << "\t" << dd << "\t" << ddd << "\t" << dddd << endl;
        d.tickHour();
    }*/
    DateTime c = d + b;
    cout << (c);
}
