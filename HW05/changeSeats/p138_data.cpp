/**
 * @file    p138_data.cpp
 * @name    p138随机测试数据生成程序
 * @date    2022-11-20
 */

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctime>

class SeatingChart
{
private:
    std::vector<int> old_chart, new_chart;
    int rows, cols;

public:
    /**
     * @brief   生成两张随机座位表
     */
    SeatingChart(int n, int m) : rows(n), cols(m), old_chart(n * m), new_chart(n * m)
    {
        shuffle(old_chart);
        shuffle(new_chart);
    }
    /**
     * @brief   计算最小交换次数
     */
    int solve()
    {
        std::vector<int> index_chart(rows * cols);
        for (int i = 0; i < rows * cols; i++)
        {
            index_chart[old_chart[i]] = i;
        }
        std::vector<bool> bo(rows * cols, false);
        int count = 0;
        for (int i = 0; i < rows * cols; i++)
        {
            if (bo[i] == true)
            {
                continue;
            }
            bo[i] = true;
            count++;
            int next = index_chart[new_chart[i]];
            while (next != i)
            {
                bo[next] = true;
                next = index_chart[new_chart[next]];
            }
        }
        return rows * cols - count;
    }
    /**
     * @brief       打印座位表
     * @param old   打印旧（old=true）或新（old=false）座位表
     */
    void printChart(std::ostream &out, bool old = true)
    {
        for (int i = 0; i < rows * cols; i++)
        {
            if (old)
            {
                out << getName(old_chart[i]);
            }
            else
            {
                out << getName(new_chart[i]);
            }
            if ((i + 1) % cols == 0)
            {
                out << std::endl;
            }
            else
            {
                out << ' ';
            }
        }
    }

private:
    /**
     * @brief   随机洗牌程序
     */
    void shuffle(std::vector<int> &list, int size = 0)
    {
        if (size <= 0)
            size = list.size();
        else
            list.resize(size);

        for (int i = 0; i < size; i++)
            list[i] = i;
        for (int i = size - 1; i > 0; i--)
        {
            int j = rand() % (i + 1);
            int t = list[i];
            list[i] = list[j];
            list[j] = t;
        }
    }
    /**
     * @brief   根据id生成名字
     */
    std::string getName(int n)
    {
        if (n == 0)
            return std::string(1, 'a');
        std::string name;
        while (n)
        {
            name += (n % 26) + 'a';
            n /= 26;
        }
        std::reverse(name.begin(), name.end());
        return name;
    }
};

int main()
{
    srand((unsigned)time(NULL));
    int test_num = 10; // 测试点个数
    for (int index = 1; index <= test_num; index++)
    {
        std::string input_file = "input" + std::to_string(index) + ".txt";
        std::string output_file = "output" + std::to_string(index) + ".txt";
        std::ofstream fin(input_file.c_str());
        std::ofstream fout(output_file.c_str());

        int n, m;
        if (index <= test_num * 0.2)
        {
            n = rand() % 3 + 3;
            m = rand() % 3 + 3;
        }
        else if (index <= test_num * 0.4)
        {
            n = rand() % 6 + 45;
            m = rand() % 6 + 45;
        }
        else
        {
            n = rand() % 11 + 190;
            m = rand() % 11 + 190;
        }

        // 文件输出代码
        fin << n << ' ' << m << std::endl;
        SeatingChart sc(n, m);
        sc.printChart(fin, true);
        if (index % 7 == 0)
        { // 不需要交换
            sc.printChart(fin, true);
            fout << 0 << std::endl;
        }
        else
        {
            sc.printChart(fin, false);
            fout << sc.solve() << std::endl;
        }

        fin.close();
        fout.close();
    }
}