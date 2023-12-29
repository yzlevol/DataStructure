/**
 * @file    template.cpp
 * @name    模板程序
 * @date    2022-11-22
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
struct {
    bool operator()(string a, string b) const {
		string s1 = a + b;
        string s2 = b + a;
        return s1 > s2;
	}
}cmp;
class Solution {
public:
    std::string largestNumber(std::vector<int>& nums) {
        if(nums.size() == 0) return "";
        vector<string> str;
        for (int i = 0; i < nums.size(); i++) {
			str.push_back(to_string(nums[i]));
		}
        sort(str.begin(), str.end(), cmp);
        string ans = "";
        for (int i = 0; i < str.size(); i++) {
            ans += str[i];
        }
        if (ans[0] == '0') return "0";
        else return ans;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
    }
    Solution s;
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}