#include <iostream>
#include <string>

using namespace std;

// ����һ����Ϊ Student �Ľṹ�壬���ڴ洢ѧ����Ϣ
struct Student {
    string no;    // ѧ��
    string name;  // ����
};

int main() {
    int n;
    cin >> n;
    // ����һ����̬���� studentList ���洢ѧ����Ϣ����ʼ��СΪ n
    Student* studentList = new Student[n];
    int currentSize = 0;  // ��ǰ�����е�ѧ������

    // ����ѧ����Ϣ��������ѧ������
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

            // ������������λ���Ƿ�Ϸ�
            if (i < 1 || i > currentSize + 1) {
                cout << -1 << endl;
            }
            else {
                // ���������� newStudentList����ԭ�����һ��Ԫ��
                Student* newStudentList = new Student[currentSize + 1];

                // ���Ʋ���λ��ǰ��Ԫ��
                for (int j = 0; j < i - 1; j++) {
                    newStudentList[j] = studentList[j];
                }

                // ������ѧ����Ϣ
                newStudentList[i - 1] = { stuNo, stuName };

                // ���Ʋ���λ�ú��Ԫ��
                for (int j = i - 1; j < currentSize; j++) {
                    newStudentList[j + 1] = studentList[j];
                }

                // ���µ�ǰѧ���������ͷ�ԭ���飬ָ��������
                currentSize++;
                delete[] studentList;
                studentList = newStudentList;

                cout << 0 << endl;  // ����ɹ�
            }
        }
        else if (operation == "remove") {
            int j;
            cin >> j;

            // ɾ�����������λ���Ƿ�Ϸ�
            if (j < 1 || j > currentSize) {
                cout << -1 << endl;
            }
            else {
                // ���������� newStudentList����ԭ������һ��Ԫ��
                Student* newStudentList = new Student[currentSize - 1];

                // ����ɾ��λ��ǰ��Ԫ��
                for (int k = 0; k < j - 1; k++) {
                    newStudentList[k] = studentList[k];
                }

                // ����ɾ��λ�ú��Ԫ��
                for (int k = j; k < currentSize; k++) {
                    newStudentList[k - 1] = studentList[k];
                }

                // ���µ�ǰѧ���������ͷ�ԭ���飬ָ��������
                currentSize--;
                delete[] studentList;
                studentList = newStudentList;

                cout << 0 << endl;  // ɾ���ɹ�
            }
        }
        else if (operation == "check") {
            string searchType, searchValue;
            cin >> searchType >> searchValue;
            int foundIndex = -1;

            // ����ѧ�����飬�����������ͺ�ֵ����ѧ����Ϣ
            for (int i = 0; i < currentSize; ++i) {
                if ((searchType == "name" && studentList[i].name == searchValue) ||
                    (searchType == "no" && studentList[i].no == searchValue)) {
                    foundIndex = i + 1;
                    cout << foundIndex << " " << studentList[i].no << " " << studentList[i].name << endl;
                    break;
                }
            }

            // �������������Ϣ
            if (foundIndex == -1 && searchType == "no") {
                cout << -1 << " " << " " << endl;
            }
            else if (foundIndex == -1) {
                cout << -1 << endl;
            }
        }
        else if (operation == "end") {
            // �����ǰѧ����������������
            cout << currentSize << endl;
            break;
        }
    }

    // �ͷŶ�̬�����ڴ�
    delete[] studentList;

    return 0;
}
