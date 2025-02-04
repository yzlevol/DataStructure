/**
 * @file    template.cpp
 * @name    p138模板程序
 * @date    2022-11-20
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
class Solution {
public:
    int solve(std::vector<std::vector<std::string>>& old_chart, std::vector<std::vector<std::string>>& new_chart) {
        int n = old_chart.size();
        int m = old_chart[0].size();

        // 将二维座位表映射到一维数组
        std::vector<std::string> flat_old_chart(n * m);
        std::vector<std::string> flat_new_chart(n * m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                flat_old_chart[i * m + j] = old_chart[i][j];
                flat_new_chart[i * m + j] = new_chart[i][j];
            }
        }

        // 构建从学生名字到座位编号的映射
        std::map<std::string, int> old_seat_map;
        for (int i = 0; i < n * m; ++i) {
            old_seat_map[flat_old_chart[i]] = i;
        }

        int swaps = 0;

        // 计算最小交换次数，使用类似冒泡排序的思想
        for (int i = 0; i < n * m; ++i) {
            while (old_seat_map[flat_new_chart[i]] != i) {
                // 交换当前位置和正确位置的学生
                std::swap(flat_old_chart[i], flat_old_chart[old_seat_map[flat_new_chart[i]]]);
                std::swap(old_seat_map[flat_old_chart[i]], old_seat_map[flat_old_chart[old_seat_map[flat_new_chart[i]]]]);
                swaps++;
            }
        }

        return swaps;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> old_chart[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> new_chart[i][j];
        }
    }

    Solution s;
    std::cout << s.solve(old_chart, new_chart) << std::endl;
    return true;
}
