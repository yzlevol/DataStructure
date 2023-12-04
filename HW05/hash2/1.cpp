#include <iostream>
#include <vector>
#include <cmath>
using ull = unsigned long long;

class Hash
{
    int BASE;
    int n;
    int table_size;
    std::vector<int> table;

    bool is_prime(const ull number)
    {
        if (number == 1)
            return false;
        for (ull i = 2, l = (ull)std::sqrt(number); i <= l; i++)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    int hash(const std::string &s) const
    {
        ull res = 0;
        for (auto iter : s)
        {
            res = res * BASE + iter;
        }
        return res % table_size;
    }

    void construct_table(int N, int P)
    {
        n = N;
        if (is_prime(P))
            table_size = P;
        else
        {
            while (is_prime(++P) == false)
                ;
            table_size = P;
        }
        table.resize(table_size, 0);
    }

    inline int Square(const int t) { return t * t; }

    int insert(const std::string &s)
    {
        int h = hash(s) % table_size;

        if (table[h] == 0)
        {
            table[h] = 1;
            return h;
        }
        else
        {
            ull t = 0;
            for (int i = 0; i <= table_size; i++)
            {
                t = ((h + Square((i + 1) / 2 % table_size) * (i % 2 ? 1 : -1)) %
                         table_size +
                     table_size) %
                    table_size;

                if (table[t] == 0)
                {
                    table[t] = 1;
                    return t;
                }
            }
        }
        return -1;
    }

public:
    Hash() { BASE = 37; }

    void solve()
    {
        int N, P;
        std::cin >> N >> P;
        construct_table(N, P);

        std::string s;
        for (int i = 0; i < n; i++)
        {
            std::cin >> s;
            int pos = insert(s);
            if (pos == -1)
                std::cout << '-';
            else
                std::cout << pos;
            std::cout << " \n"[i == n - 1];
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Hash Solution;
    Solution.solve();

    return 0;
}
