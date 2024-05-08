#include <iostream>
#include <cstring>
using namespace std;

struct node {
    node* ls, * rs;
    char data;
    node() : data(0), ls(0), rs(0) {}
};

string preOrder, inOrder;
int map_inorder[256]; 

node* generate(int l0, int r0, int l1, int r1, bool& error) {
    if (error) {
        return NULL;
    }

    if (l0 > r0) {
        return NULL;
    }

    node* p = new node;
    p->data = preOrder[l0];
    int pos = map_inorder[p->data];
    if (pos < l1 || pos > r1) {
        cout << "Error" << endl;
        delete p; // 释放之前分配的节点内存
        error = true; // 设置错误标志为 true
        return NULL;
    }

    p->ls = generate(l0 + 1, pos - l1 + l0, l1, pos - 1, error);
    p->rs = generate(pos - l1 + l0 + 1, r0, pos + 1, r1, error);

    return p;
}

void backTraversal(node* root) {
    if (!root)
        return;
    else {
        backTraversal(root->ls);
        backTraversal(root->rs);
        cout << root->data;
    }
}

int main() {
    while (cin >> preOrder) {
        cin >> inOrder;
        memset(map_inorder, -1, sizeof(map_inorder)); 
        bool error = false;

        int len = preOrder.size();
        for (int i = 0; i < len; ++i)
            map_inorder[inOrder[i]] = i;

        node* root = generate(0, len - 1, 0, len - 1, error);
        if (!error && root) {
            backTraversal(root);
            cout << endl;
        }
        else {
            // 清空读入的数据
            preOrder.clear();
            inOrder.clear();
        }
    }

    return 0;
}
