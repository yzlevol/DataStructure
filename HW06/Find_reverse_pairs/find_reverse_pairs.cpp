#include <iostream>
#include <vector>
using namespace std;

vector<int> a;  

long long sum;
vector<int> temp; 

void merge(int left, int mid, int right) {
    int p1 = left, p2 = mid + 1, i = left;
    temp.resize(right - left + 1);

    while (p1 <= mid && p2 <= right) {
        if (a[p1] <= a[p2])
            temp[i++ - left] = a[p1++];
        else {
            temp[i++ - left] = a[p2++];
            sum += mid - p1 + 1;
        }
    }

    while (p1 <= mid) temp[i++ - left] = a[p1++];
    while (p2 <= right) temp[i++ - left] = a[p2++];

    for (i = left; i <= right; i++) a[i] = temp[i - left];
}

void find_pairs(int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        find_pairs(left, mid);
        find_pairs(mid + 1, right);
        merge(left, mid, right);
    }
}

int main() {
    int N;
    while (cin >> N && N) {
        a.resize(N);  
        for (int i = 0; i < N; i++) cin >> a[i];
        temp.resize(N);  
        sum = 0;
        find_pairs(0, N - 1);
        cout << sum << endl;
    }
    return 0;
}

/*1.超时：全局函数
*/