#include <iostream>
using namespace std;

class SequenceList {
private:
    int* data;    
    int size;     
    int capacity; 
public:
    SequenceList(int initialCapacity = 10) {
        size = 0;
        capacity = initialCapacity;
        data = new int[capacity];
    }
    ~SequenceList() {
        delete[] data;
    }
    void push_back(int value) {
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }
    void rotate(int k) {
        k = k % size; 
        if (k == 0) {
            return;
        }
        int* temp = new int[size];
        for (int i = 0; i < k; ++i) {
            temp[i] = data[size - k + i];
        }
        for (int i = size - 1; i >= k; --i) {
            data[i] = data[i - k];
        }
        for (int i = 0; i < k; ++i) {
            data[i] = temp[i];
        }
        delete[] temp;
    }
    void print() {
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << std::endl;
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    SequenceList sequenceList;
    for (int i = 0; i < n; ++i) {
        int value;
        cin >> value;
        sequenceList.push_back(value);
    }
    sequenceList.rotate(k);
    sequenceList.print();
    return 0;
}
