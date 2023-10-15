#include <iostream>
#include <string>

using namespace std;

string addStrings(string num1, string num2) {
    int carry = 0;
    int i = num1.length() - 1;
    int j = num2.length() - 1;
    string result = "";

    while (i >= 0 || j >= 0 || carry > 0) {
        int x = (i >= 0) ? num1[i] - '0' : 0;
        int y = (j >= 0) ? num2[j] - '0' : 0;
        int sum = x + y + carry;
        result = to_string(sum % 10) + result;
        carry = sum / 10;
        i--;
        j--;
    }

    return result;
}

string multiplyStrings(string num1, int num2) {
    if (num2 == 0) return "0";
    if (num2 == 1) return num1;

    string result = "0";
    for (int i = 0; i < num2; i++) {
        result = addStrings(result, num1);
    }
    return result;
}

int main() {
    int N, A;
    while (cin >> N >> A) {
        string result = "0";
        string term = "1";

        for (int i = 1; i <= N; ++i) {
            term = multiplyStrings(term, A);
            string ith_term = multiplyStrings(to_string(i), stoi(term)); 
            result = addStrings(result, ith_term); 
        }
        cout << result << endl;
    }

    return 0;
}
