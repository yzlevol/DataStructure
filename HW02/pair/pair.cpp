#include <iostream>
#include <string>
using namespace std;

class Stack { //使用链表实现栈
private:
    struct Node { 
        int index;
        Node* next;
        Node(int i) : index(i), next(NULL) {}
    };
    Node* top;
public:
    Stack() : top(NULL) {}

    void push(int index) {
        Node* newNode = new Node(index);
        if (top == NULL) {
            top = newNode;
        }
        else {
            newNode->next = top;
            top = newNode;
        }
    }

    void pop() {
        if (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool empty() {
        return top == NULL;
    }

    int getTopIndex() {
        if (top != NULL) {
            return top->index;
        }
        return -1;
    }
};

pair<int, int> longestValidParentheses(string s) {
    Stack stk;
    int maxLen = 0, maxStart = 0, lastRight = -1;
    int start = -1;  
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            if (start == -1) {  
                start = i;
            }
            stk.push(i);
        }
        else {
            if (stk.empty()) {
                lastRight = i;
                start = -1;  
            }
            else {
                stk.pop();
                if (stk.empty()) { 
                    int currentLen = i - lastRight;
                    if (currentLen > maxLen) {
                        maxLen = currentLen;
                        maxStart = lastRight + 1;
                    }
                }
                else {
                    int currentLen = i - stk.getTopIndex();
                    if (currentLen > maxLen) {
                        maxLen = currentLen;
                        maxStart = stk.getTopIndex() + 1;
                    }
                }
            }
        }
    }
    return { maxLen, maxStart };
}

int main() {
    string s;
    getline(cin, s);
    pair<int, int> result = longestValidParentheses(s);
    cout << result.first << " " << result.second << endl;
    return 0;
}
