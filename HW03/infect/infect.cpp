#include <iostream>
#include <cstring>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(NULL), right(NULL) {}
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

struct MyVector {
    int* data;
    int size;
    int capacity;

    MyVector() {
        capacity = 1;
        size = 0;
        data = new int[capacity];
    }

    ~MyVector() {
        delete[] data;
    }

    void push_back(int val) {
        if (size == capacity) {
            int* newData = new int[capacity * 2];
            memcpy(newData, data, sizeof(int) * capacity);
            delete[] data;
            data = newData;
            capacity *= 2;
        }
        data[size++] = val;
    }

    int operator[](int index) {
        return data[index];
    }
};

MyVector a[100010];
bool st[100010] = { false };
int res = 0;

void Inorder(TreeNode* node) {
    if (node == NULL) return;
    if (node->left != NULL) {
        a[node->val].push_back(node->left->val);
        a[node->left->val].push_back(node->val);
    }
    if (node->right != NULL) {
        a[node->val].push_back(node->right->val);
        a[node->right->val].push_back(node->val);
    }
    Inorder(node->left);
    Inorder(node->right);
}

void dfs(int num, int level) {
    st[num] = true;
    res = max(res, level);
    for (int i = 0; i < a[num].size; i++) {
        int x = a[num][i];
        if (st[x]) continue;
        dfs(x, level + 1);
    }
}

int sumTime(TreeNode* root, int start) {
    Inorder(root);
    dfs(start, 0);
    return res;
}

int main() {
    int n, start;
    cin >> n >> start;
    TreeNode* nodes = new TreeNode[n];
    for (int i = 0; i < n; i++) {
        int left, right;
        cin >> left >> right;
        if (left != -1) nodes[i].left = &nodes[left];
        if (right != -1) nodes[i].right = &nodes[right];
        nodes[i].val = i;
    }
    int mins = sumTime(&nodes[0], start);
    cout << mins << endl;
    delete[] nodes;
    return 0;
}
