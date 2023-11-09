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

node* generate() {
    node* root = nullptr;
    node** curr = &root;
    int l0 = 0;
    int r0 = preOrder.size() - 1;
    int l1 = 0;
    int r1 = inOrder.size() - 1;
    bool error = false;
    
    while (l0 <= r0) {
        char data = preOrder[l0];
        if (map_inorder[data] < l1 || map_inorder[data] > r1) {
            cout << "Error" << endl;
            error = true;
            break;
        }

        node* p = new node;
        p->data = data;
        if (*curr) {
            if (map_inorder[data] < map_inorder[(*curr)->data]) {
                (*curr)->ls = p;
            } else {
                (*curr)->rs = p;
            }
        }
        *curr = p;

        l0++;
        l1 = map_inorder[data] + 1;

        if (error) {
            break;
        }

        if (l1 > r1) {
            while (*curr && (*curr)->rs) {
                curr = &(*curr)->rs;
            }
        }
    }

    if (error) {
        while (root) {
            node* temp = root;
            root = root->ls;
            delete temp;
        }
        preOrder.clear();
        inOrder.clear();
        return nullptr;
    }

    return root;
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

        node* root = generate();
        if (!error && root) {
            backTraversal(root);
            cout << endl;
        }
        else {
            preOrder.clear();
            inOrder.clear();
        }
    }

    return 0;
}

