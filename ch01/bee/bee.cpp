#include <iostream>
using namespace std;

int main() {
    int n;
    while (true) {
        cin >> n;
        if (n == -1) {
            break; 
        }

        unsigned long long a = 1, b = 0; 
        unsigned long long c, d;

        for (int i = 0; i < n; i++) {
            c = b + 1;
            d = a + b;
            a = c;
            b = d;
        }

        cout << b << ' ' << a + b << endl;
    }

    return 0;
}
