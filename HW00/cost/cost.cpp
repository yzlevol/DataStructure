#include <iostream>
#include <iomanip> 
using namespace std;

int main() {
    double total = 0.0;

    for (int i = 0; i < 12; i++) {
        double income;
        cin >> income;
        total += income;
    }

    double averageIncome = total / 12;
    std::cout << "¥" << fixed << setprecision(2) << averageIncome << endl;

    return 0;
}
