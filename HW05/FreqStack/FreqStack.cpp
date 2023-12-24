/**
 * @name    template.cpp
 * @brief   p142ģ�����
 * @date    2022-12-02
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
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
class FreqStack {
public:
    FreqStack() : maxFreq(0) {}

    void push(int val) {
        freq[val]++;
        maxFreq = max(maxFreq, freq[val]);
        group[freq[val]].push(val);
        elems.push_back(val);
    }
    int pop() {
        int val = group[maxFreq].top();
        group[maxFreq].pop();
        if (group[maxFreq].empty())
            maxFreq--;
        elems.erase(remove(elems.begin(), elems.end(), val), elems.end());

        freq[val]--;
        return val;
    }

private:
    int maxFreq;
    vector<int> elems;
    map<int, int> freq;
    map<int, stack<int>> group;
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n--) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}
