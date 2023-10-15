#include <iostream>
#include <string>

using namespace std;

// 定义一个名为 Student 的结构体，用于存储学生信息
struct Student {
    string no;    // 学号
    string name;  // 姓名
};

int main() {
    int n;
    cin >> n;
    // 创建一个动态数组 studentList 来存储学生信息，初始大小为 n
    Student* studentList = new Student[n];
    int currentSize = 0;  // 当前数组中的学生数量

    // 输入学生信息，并递增学生数量
    for (int i = 0; i < n; ++i) {
        cin >> studentList[i].no >> studentList[i].name;
        currentSize++;
    }

    string operation;
    while (cin >> operation) {
        if (operation == "insert") {
            int i;
            string stuNo, stuName;
            cin >> i >> stuNo >> stuName;

            // 插入操作，检查位置是否合法
            if (i < 1 || i > currentSize + 1) {
                cout << -1 << endl;
            }
            else {
                // 创建新数组 newStudentList，比原数组多一个元素
                Student* newStudentList = new Student[currentSize + 1];

                // 复制插入位置前的元素
                for (int j = 0; j < i - 1; j++) {
                    newStudentList[j] = studentList[j];
                }

                // 插入新学生信息
                newStudentList[i - 1] = { stuNo, stuName };

                // 复制插入位置后的元素
                for (int j = i - 1; j < currentSize; j++) {
                    newStudentList[j + 1] = studentList[j];
                }

                // 更新当前学生数量，释放原数组，指向新数组
                currentSize++;
                delete[] studentList;
                studentList = newStudentList;

                cout << 0 << endl;  // 插入成功
            }
        }
        else if (operation == "remove") {
            int j;
            cin >> j;

            // 删除操作，检查位置是否合法
            if (j < 1 || j > currentSize) {
                cout << -1 << endl;
            }
            else {
                // 创建新数组 newStudentList，比原数组少一个元素
                Student* newStudentList = new Student[currentSize - 1];

                // 复制删除位置前的元素
                for (int k = 0; k < j - 1; k++) {
                    newStudentList[k] = studentList[k];
                }

                // 复制删除位置后的元素
                for (int k = j; k < currentSize; k++) {
                    newStudentList[k - 1] = studentList[k];
                }

                // 更新当前学生数量，释放原数组，指向新数组
                currentSize--;
                delete[] studentList;
                studentList = newStudentList;

                cout << 0 << endl;  // 删除成功
            }
        }
        else if (operation == "check") {
            string searchType, searchValue;
            cin >> searchType >> searchValue;
            int foundIndex = -1;

            // 遍历学生数组，根据搜索类型和值查找学生信息
            for (int i = 0; i < currentSize; ++i) {
                if ((searchType == "name" && studentList[i].name == searchValue) ||
                    (searchType == "no" && studentList[i].no == searchValue)) {
                    foundIndex = i + 1;
                    cout << foundIndex << " " << studentList[i].no << " " << studentList[i].name << endl;
                    break;
                }
            }

            // 输出结果或错误信息
            if (foundIndex == -1 && searchType == "no") {
                cout << -1 << " " << " " << endl;
            }
            else if (foundIndex == -1) {
                cout << -1 << endl;
            }
        }
        else if (operation == "end") {
            // 输出当前学生数量，结束程序
            cout << currentSize << endl;
            break;
        }
    }

    // 释放动态数组内存
    delete[] studentList;

    return 0;
}
