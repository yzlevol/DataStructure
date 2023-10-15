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

string multiplyStrings(string num1, string num2) {
    int len1 = num1.length();
    int len2 = num2.length();
    string result(len1 + len2, '0');

    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int res = (num1[i] - '0') * (num2[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = res / 10;
            result[i + j + 1] = res % 10 + '0';
        }
        result[i] += carry;
    }
    //查找第一个不为0的位置
    int startPos = 0;
    while (startPos < result.length() && result[startPos] == '0') {
        startPos++;
    }
    if (startPos < result.length()) {
        return result.substr(startPos);
    }
    else {
        return "0";
    }
}

int main() {
    int N, A;
    while (cin >> N >> A) {
        string result = "0";
        string term = "1";
        for (int i = 1; i <= N; ++i) {
            term = multiplyStrings(term, to_string(A)); 
            string res = multiplyStrings(to_string(i), term); 
            result = addStrings(result, res); 
        }

        cout << result << endl;
    }

    return 0;
}
