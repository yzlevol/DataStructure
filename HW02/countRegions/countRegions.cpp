#include <iostream>
using namespace std;

class Queue {
private:
    int* data; 
    int front; 
    int rear;  
    int capacity; 

public:
    Queue(int size) {
        capacity = size;
        data = new int[size];
        front = rear = -1;
    }
    ~Queue() {
        delete[] data;
    }
    bool isEmpty() {
        return front == -1;
    }
    bool isFull() {
        return (rear + 1) % capacity == front;
    }
    void enqueue(int value) {
        if (isFull()) {
            cout << "full." << value << endl;
        }
        else {
            if (isEmpty()) {
                front = rear = 0;
            }
            else {
                rear = (rear + 1) % capacity;
            }
            data[rear] = value;
        }
    }
    int dequeue() {
        if (isEmpty()) {
            return -1;
        }
        else {
            int value = data[front];
            if (front == rear) {
                front = rear = -1;
            }
            else {
                front = (front + 1) % capacity;
            }
            return value;
        }
    }
};

int countRegions(int** matrix, int n, int m) {
    int regionCount = 0;
    Queue queue(n * m);

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 1) {
                regionCount++;
                queue.enqueue(i * m + j); 

                while (!queue.isEmpty()) {
                    int current = queue.dequeue();
                    int x = current / m;
                    int y = current % m;

                    for (int k = 0; k < 4; k++) {
                        int newX = x + dx[k];
                        int newY = y + dy[k];

                        if (newX >= 0 && newX < n && newY >= 0 && newY < m && matrix[newX][newY] == 1) {
                            queue.enqueue(newX * m + newY);
                            matrix[newX][newY] = 0; 
                        }
                    }
                }
            }
        }
    }

    return regionCount;
}

int main() {
    int n, m;
    cin >> n >> m;
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }
    int regionCount = countRegions(matrix, n, m);
    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << regionCount<< endl;
    return 0;
}
