#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> solveQueries(const vector<int>& nums, const vector<int>& queries) {
        // 排序原始数字序列
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());

        // 存储结果
        vector<int> answer(queries.size());

        for (int i = 0; i < queries.size(); ++i) {
            int sum = 0;
            int left = 0, right = sortedNums.size() - 1;

            // 在排序后的序列中使用双指针查找
            while (left <= right) {
                if (sortedNums[left] + sum <= queries[i]) {
                    sum += sortedNums[left];
                    ++left;
                }
                else {
                    --right;
                }
            }

            answer[i] = left;
        }

        return answer;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
        cin >> nums[i];

    vector<int> queries(m);
    for (int i = 0; i < m; ++i)
        cin >> queries[i];

    Solution solution;
    vector<int> result = solution.solveQueries(nums, queries);

    for (int i = 0; i < m; ++i) 
        cout << result[i] << " ";
    return 0;
}
