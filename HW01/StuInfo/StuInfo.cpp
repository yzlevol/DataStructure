#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string no;   
    string name; 
};

int main() {
    int n;
    cin >> n;
    vector<Student> studentList(n);

    for (int i = 0; i < n; ++i) {
        cin >> studentList[i].no >> studentList[i].name;
    }
    string operation;
    while (cin >> operation) {
        if (operation == "insert") {
            int i;
            string stuNo, stuName;
            cin >> i >> stuNo >> stuName;
            if (i < 1 || i > n + 1) {
                cout << -1 << endl;
            }
            else {
                Student newStudent = { stuNo, stuName };
                studentList.insert(studentList.begin() + i - 1, newStudent);
                n++;
                cout << 0 << endl;
            }
        }
        else if (operation == "remove") {
            int j;
            cin >> j;
            if (j < 1 || j > n) {
                cout << -1 << endl;
            }
            else {
                studentList.erase(studentList.begin() + j - 1);
                n--;
                cout << 0 << endl;
            }
        }
        else if (operation == "check") {
            string searchType, searchValue;
            cin >> searchType >> searchValue;
            int foundIndex = -1;
            for (int i = 0; i < n; ++i) {
                if ((searchType == "name" && studentList[i].name == searchValue) ||
                    (searchType == "no" && studentList[i].no == searchValue)) {
                    foundIndex = i + 1;
                    cout << foundIndex << " " << studentList[i].no << " " << studentList[i].name << endl;
                    break;
                }
            }
            if (foundIndex == -1 && searchType == "no") {
                cout << -1 << " " << " " << endl;
            }
            else if (foundIndex == -1) {
                cout << -1 << endl;
            }
        }
        else if (operation == "end") {
            cout << n << endl;
            break;
        }
    }
    return 0;
}
