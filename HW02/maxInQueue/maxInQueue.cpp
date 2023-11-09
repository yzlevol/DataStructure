#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node* prev;
    Node(int val) : value(val), next(NULL), prev(NULL) {}
};

class MaxQueue {
private:
    int n;
    int count;
    Node* front;
    Node* rear;
    Node* maxNode;

public:
    MaxQueue(int capacity) : n(capacity), count(0), front(NULL), rear(NULL), maxNode(NULL) {}
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is Full" << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!front) {
            front = rear = maxNode = newNode;
        }
        else {
            rear->next = newNode;
            newNode->prev = rear;
            rear = newNode;
            if (value >= maxNode->value) {
                maxNode = newNode;
            }
        }
        count++;
    }
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        Node* removed = front;
        int value = removed->value;
        front = front->next;
        if (removed == maxNode) {
            maxNode = front;
            Node* current = front;
            while (current) {
                if (current->value >= maxNode->value) {
                    maxNode = current;
                }
                current = current->next;
            }
        }
        delete removed;
        count--; 
        return value;
    }
    int getMax() {
        if (isEmpty()) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        return maxNode->value;
    }
    bool isFull() {
        return count == n; 
    }
    bool isEmpty() {
        return front == NULL;
    }
};

int main() {
    int n;
    cin >> n;
    MaxQueue maxQueue(n);
    string cmd;
    while (cin >> cmd) {
        if (cmd == "dequeue") {
            int value = maxQueue.dequeue();
            if (value != -1) {
                cout << value << endl;
            }
        }
        else if (cmd == "enqueue") {
            int value;
            cin >> value;
            maxQueue.enqueue(value);
        }
        else if (cmd == "max") {
            int value = maxQueue.getMax();
            if (value != -1) {
                cout << value << endl;
            }
        }
        else if (cmd == "quit") {
            break;
        }
    }
    while (!maxQueue.isEmpty()) {
        int value = maxQueue.dequeue();
        cout << value << " ";
    }
    return 0;
}
