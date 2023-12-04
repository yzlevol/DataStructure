#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    int count;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), count(1), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* root, int val) {
        if (!root) {
            return new TreeNode(val);
        }

        if (val == root->val) {
            root->count++;
        }
        else if (val < root->val) {
            root->left = insert(root->left, val);
        }
        else {
            root->right = insert(root->right, val);
        }

        return root;
    }

    TreeNode* findMin(TreeNode* root) {
        while (root && root->left) {
            root = root->left;
        }
        return root;
    }

    TreeNode* remove(TreeNode* root, int val) {
        if (!root) {
            cout << "None" << endl;
            return nullptr;
        }

        if (val < root->val) {
            root->left = remove(root->left, val);
        }
        else if (val > root->val) {
            root->right = remove(root->right, val);
        }
        else {
            if (root->count > 1) {
                root->count--;
            }
            else {
                if (!root->left) {
                    TreeNode* temp = root->right;
                    delete root;
                    return temp;
                }
                else if (!root->right) {
                    TreeNode* temp = root->left;
                    delete root;
                    return temp;
                }

                TreeNode* temp = findMin(root->right);
                root->val = temp->val;
                root->count = temp->count;
                root->right = remove(root->right, temp->val);
            }
        }

        return root;
    }

    int count(TreeNode* root, int val) {
        if (!root) {
            return 0;
        }

        if (val == root->val) {
            return root->count;
        }
        else if (val < root->val) {
            return count(root->left, val);
        }
        else {
            return count(root->right, val);
        }
    }

    int predecessor(TreeNode* root, int val) {
        int pred = -1;

        while (root) {
            if (val <= root->val) {
                root = root->left;
            }
            else {
                pred = root->val;
                root = root->right;
            }
        }

        return pred;
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    void remove(int val) {
        root = remove(root, val);
    }

    int count(int val) {
        return count(root, val);
    }

    int findMin() {
        TreeNode* minNode = findMin(root);
        return minNode ? minNode->val : -1;
    }

    int predecessor(int val) {
        int pred = predecessor(root, val);

        if (pred == -1) {
            cout << "None" << endl;
        }
        else {
            cout << pred << endl;
        }

        return pred;
    }
};

int main() {
    int n;
    int find, res;
    cin >> n;

    BST bst;

    for (int i = 0; i < n; ++i) {
        int op, x;
        cin >> op;

        switch (op) {
            case 1:
                cin >> x;
                bst.insert(x);
                break;
            case 2:
                cin >> x;
                bst.remove(x);
                break;
            case 3:
                cin >> x;
                cout << bst.count(x) << endl;
                break;
            case 4:
                find = bst.findMin();
                if (find != -1)
                    cout << find << endl;
                else
                    cout << "None" << endl;
                break;
            case 5:
                cin >> x;
                res = bst.predecessor(x);
                /*if (res == -1)
                    cout << "None" << endl;*/
                break;
            default:
                break;
        }
    }

    return 0;
}
