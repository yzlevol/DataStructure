#include <iostream>
#include <vector>
#include <string>
using namespace std;

constexpr int MAX_N = 10005;
constexpr int MAX_P = 10008;

class HashTable {
public:
    HashTable(int P) : M(P), K(P / 2), hashTable(P, 0) {}

    int myhash(const char s[MAX_N]) {
        int h = 0;
        int i = 0;
        while (s[i]) {
            h = (h * 37 + static_cast<int>(s[i++])) % M;
        }

        if (!hashTable[h]) {
            hashTable[h] = 1;
            return h;
        }
        else {
            int newh;
            for (int i = 1; i <= K; i++) {
                newh = (h + i * i) % M;
                if (!hashTable[newh]) {
                    hashTable[newh] = 1;
                    return newh;
                }
                newh = (h - i * i + M * i) % M;
                if (!hashTable[newh]) {
                    hashTable[newh] = 1;
                    return newh;
                }
            }
            return -1;
        }
    }

    void insertNames(int N) {
        for (int i = 0; i < N; i++) {
            char name[MAX_N];
            cin >> name;
            int ans = myhash(name);
            cout << (ans == -1 ? "-" : to_string(ans));
            if (i != N - 1) {
                cout << " ";
            }
        }
    }

private:
    int M;
    int K;
    vector<int> hashTable;
};

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int nextPrime(int num) {
    if (num <= 1) {
        return 2;
    }
    while (!isPrime(num)) {
        num++;
    }
    return num;
}

int main() {
    int N, P;
    cin >> N >> P;

    P = nextPrime(P);
    HashTable hashTable(P);
    hashTable.insertNames(N);

    return 0;
}


/*
* 有个位置应该是1但是输出了 -，表示未找到
3 1
qCCIyttkQfoHCoFpPUNGTPRHgpTgivuEQGDezlBIrFvsCaFAWNTGMVfMWXGiSgxcpjWAXTaRChyGcYBZGVrOoTEMUw heSEeE FmagTdZHLxzolnFIwWcbggcNWvJlGczDAGPeseNnWWRejovuSRjMoZKQnVbIcrHoiqvGYrbtFoE 
但是输出3 - -

2 / 2

ChatGPT
抱歉，我看到了你的问题。问题可能出在 isPrime 函数上，因为你的代码中 isPrime 只判断了是否为奇数。在这里，nextPrime 函数应该返回比给定数字大的下一个素数，而不是仅仅是比给定数字大的下一个奇数。

下面是修改的 isPrime 和 nextPrime 函数，使用了更准确的素数判断：
*/