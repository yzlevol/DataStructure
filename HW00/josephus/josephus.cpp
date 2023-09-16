#include <iostream>
using namespace std;

int josephus(int n, int m) {
    int result = 0;
    for (int i = 2; i <= n; i++) {
        result = (result + m) % i;
    }
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    int sur = josephus(n, m);

    cout << sur << endl;
    return 0;
}
