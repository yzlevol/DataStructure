#include <iostream>
using namespace std;
string option;
char val;

class Tree {
public:
    Tree(char d, Tree* l = NULL, Tree* r = NULL) {
        data = d;
        left = l;
        right = r;
    }
    char data;
    Tree* left;
    Tree* right;
};

class MyStack {
private:
    static const int MAX_SIZE = 100;
    Tree* data[MAX_SIZE];
    int top;

public:
    MyStack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    void push(Tree* item) {
        if (!isFull()) {
            data[++top] = item;
        }
    }

    void pop() {
        if (!isEmpty()) {
            top--;
        }
    }

    Tree* peek() {
        if (!isEmpty()) {
            return data[top];
        }
        return NULL;
    }
};

void builvalree(int n, Tree* root) {
    Tree* ptr = root;
    bool leftExist = true;
    MyStack st;

    while (n) {
        cin >> option;
        if (option == "pop") {
            if (leftExist)
                leftExist = false;
            else {
                if (st.isEmpty()) continue;
                ptr = st.peek();
                st.pop();
            }
        }
        else {
            cin >> val;
            st.push(ptr);
            if (leftExist) {
                ptr->left = new Tree(val);
                ptr = ptr->left;
            }
            else {
                ptr->right = new Tree(val);
                ptr = ptr->right;
                st.pop();
            }
            leftExist = true;
            n--;
        }
    }
}

void postOrder(Tree* root) {
    if (root == NULL) {
        return;
    }

    MyStack st;
    Tree* curr = root;
    Tree* last = NULL;

    while (curr || !st.isEmpty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.peek();
        if (curr->right == NULL || curr->right == last) {
            cout << curr->data; 
            st.pop();
            last = curr;
            curr = NULL; 
        }
        else {
            curr = curr->right;
        }
    }
}

int main() {
    int n;
    cin >> n;
    cin >> option >> val;
    Tree* root = new Tree(val);
    builvalree(n - 1, root);
    postOrder(root);
    return 0;
}
