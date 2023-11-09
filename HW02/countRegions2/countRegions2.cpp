#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

class Queue {
private:
    Node* front;
    Node* rear;
public:
    Queue() : front(NULL), rear(NULL) {}

    void enqueue(int value) {
        Node* newNode = new Node;
        newNode->data = value;
        newNode->next = NULL;
        if (rear == NULL) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    int dequeue() {
        if (front == NULL) {
            cout << "Queue is Empty" << endl;
            return -1;
        }
        Node* tmp = front;
        int value = tmp->data;
        front = front->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        delete tmp;
        return value;
    }

    bool isEmpty() {
        return front == NULL;
    }
};

void dfs(int i, int j, int m, int n, bool **visited, int** matrix) {
    if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || matrix[i][j] == 0) {
        return;
    }
    visited[i][j] = true;
    dfs(i - 1, j, m, n, visited, matrix);
    dfs(i + 1, j, m, n, visited, matrix);
    dfs(i, j - 1, m, n, visited, matrix);
    dfs(i, j + 1, m, n, visited, matrix);
}

int countRegions(int** matrix, int m, int n) {
    bool **visited = new bool*[m];
    int count = 0;
    Queue queue;
    for (int i = 0; i < m; ++i)
    {
        visited[i] = new bool[n];
        for (int j = 0; j < n; ++j)
        {
            visited[i][j] = false;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1 && !visited[i][j]) {
                if (i == 0 || i == m - 1 || j == 0 || j == n - 1) {
                    continue;
                }
                dfs(i, j, m, n, visited, matrix);
                count++;
            }
        }
    }
    for (int i = 0; i < m; ++i)
    {
        delete[] visited[i];
    }
    delete[] visited;
    return count;
}

int main() {
    int m, n;
    cin >> m >> n;
    int** matrix = new int* [m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }
    int regions = countRegions(matrix, m, n);
    cout << regions << endl;
    for (int i = 0; i < m; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}
