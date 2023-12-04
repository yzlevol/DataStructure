#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class HashTable {
public:
    HashTable(int P) : M(P), K(P / 2), hashTable(P, -1) {}

    unsigned long long int myhash(const char* s) {
        unsigned long long int h = 0;
        int i = 0;
        while (s[i]) {
            h = (h * 37 + static_cast<unsigned long long int>(s[i++]));
        }

        if (hashTable[h % M] == -1) {
            hashTable[h % M] = 1;
            return h % M;
        }
        else {
            unsigned long long int newh;
            for (int j = 1; j <= K; j++) {
                newh = (h + j * j) % M;
                if (hashTable[newh] == -1) {
                    hashTable[newh] = 1;
                    return newh;
                }
                newh = (h - j * j + M) % M;
                if (hashTable[newh] == -1) {
                    hashTable[newh] = 1;
                    return newh;
                }
            }
            return -1;
        }
    }

    void insertNames(int N) {
        for (int i = 0; i < N; i++) {
            char* name = new char[MAX_NAME_LENGTH];  
            cin >> name;
            unsigned long long int ans = myhash(name);
            cout << (ans == -1 ? "-" : to_string(ans));
            if (i != N - 1) {
                cout << " ";
            }
            delete[] name;  
        }
    }

private:
    const int MAX_NAME_LENGTH = 10005;  
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
