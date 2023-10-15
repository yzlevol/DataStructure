#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

int getLength(ListNode* head) {
    int length = 0;
    while (head != nullptr) {
        ++length;
        head = head->next;
    }
    return length;
}

ListNode* rotateRight(ListNode* head, int k) {
    if (head == nullptr || k == 0) {
        return head;
    }
    int length = getLength(head);
    k = k % length; 

    if (k == 0) {
        return head;
    }
    ListNode* fast = head;
    ListNode* slow = head;
    for (int i = 0; i < k; ++i) {
        fast = fast->next;
    }
    while (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* newHead = slow->next;
    slow->next = nullptr;
    fast->next = head;

    return newHead;
}
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    int n, k;
    cin >> n >> k;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        if (head == nullptr) {
            head = new ListNode(val);
            tail = head;
        }
        else {
            tail->next = new ListNode(val);
            tail = tail->next;
        }
    }
    head = rotateRight(head, k);
    printList(head);
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
