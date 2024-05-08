#include <iostream>
#include <cstring>
using namespace std;

const int MAX_NODE = 100005;

class MyStack {
private:
    int data[MAX_NODE];
    int top;

public:
    MyStack() {
        top = -1;
    }

    void push(int value) {
        if (top < MAX_NODE - 1) {
            data[++top] = value;
        }
    }

    void pop() {
        if (top >= 0) {
            --top;
        }
    }

    int topValue() {
        if (top >= 0) {
            return data[top];
        }
        return -1;  
    }

    bool empty() {
        return top == -1;
    }
};

char s[MAX_NODE * 2];

int main() {
    int cnt = 0;
    while (cin.getline(s, MAX_NODE * 2)) {
        if (s[0] == '#')
            break;

        int n = strlen(s);
        int d = 0;
        int tree_dep = 0, btree_dep = 0;

        for (int i = 0; i < n; ++i) {
            int add = s[i] == 'd' ? 1 : -1;
            d += add;
            if (d > tree_dep) {
                tree_dep = d;
            }
        }

        MyStack fa;
        d = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'd') {
                fa.push(d);
                d += 1;
            }
            else {
                if (s[i + 1] == 'd') {
                    d += 1;
                    ++i;
                }
                else {
                    d = fa.topValue();
                    fa.pop();
                }
            }
            if (d > btree_dep) {
                btree_dep = d;
            }
        }
        cout << "Tree " << ++cnt << ": " << tree_dep << " => " << btree_dep << endl;
    }
    cin.get();
    return 0;
}
