#include <iostream>
using namespace std;

/* 你可以在本地完成类Solution后提交仅包含类定义的代码 */
/* 以下是你需要提交的代码 */
class Solution {
public:
    int solve(int a, int b) {
        return a+b;
    }
};
/*************************/

int main() {
    int a, b;
    cin >> a >> b;
    Solution s;
    cout << s.solve(a, b) << endl;
    return 0;
}