#include <iostream>
#include <string>
using namespace std;
struct Patient {
    string name;
    int department; // ���ұ�ţ�0��ʾ��һ���ң�1��ʾ�ڶ����ң�2��ʾ��������
    int doctor;     // ҽ����ţ�0��ʾ��һ��ҽ����1��ʾ�ڶ���ҽ��
    Patient* next;

    Patient(const string& n, int d, int doc) : name(n), department(d), doctor(doc), next(NULL) {}
};

class LinkedListQueue {
private:
    Patient* front;
    Patient* rear;
public:
    LinkedListQueue() : front(NULL), rear(NULL) {}
    void enqueue(const string& name, int department, int doctor) {
        Patient* patient = new Patient(name, department, doctor);
        if (rear == NULL) {
            front = patient;
            rear = patient;
        }
        else {
            rear->next = patient;
            rear = patient;
        }
    }

    bool dequeue(string& name, int& department, int& doctor) {
        if (isEmpty()) {
            return false;
        }

        Patient* patient = front;
        name = patient->name;
        department = patient->department;
        doctor = patient->doctor;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }
        delete patient;
        return true;
    }

    bool isEmpty() const {
        return front == NULL;
    }

    ~LinkedListQueue() {
        while (!isEmpty()) {
            Patient* patient = front;
            front = front->next;
            delete patient;
        }
    }
};

class HospitalQueue {
private:
    LinkedListQueue patientQueues[3][2];

    int selectDoctor(int department) {
        int doctor0Size = patientQueues[department][0].isEmpty() ? 0 : 1;
        int doctor1Size = patientQueues[department][1].isEmpty() ? 0 : 1;
        return (doctor0Size <= doctor1Size) ? 0 : 1;
    }

public:
    HospitalQueue() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 2; ++j) {
                patientQueues[i][j] = LinkedListQueue();
            }
        }
    }

    void enqueuePatient(const string& name, int department) {
        int selectedDoctor = selectDoctor(department);
        patientQueues[department][selectedDoctor].enqueue(name, department, selectedDoctor);
        cout << name << " ����ӣ��ȴ����������ң�" << department + 1 << "��ҽ����ţ�" << selectedDoctor + 1 << endl;
    }

    void treatNextPatients() {
        for (int department = 0; department < 3; ++department) {
            for (int doctor = 0; doctor < 2; ++doctor) {
                string name;
                int dep, doc;
                if (patientQueues[department][doctor].dequeue(name, dep, doc)) {
                    cout << "�� " << name << " ������ڿ��ң�" << dep + 1 << "��ҽ����ţ�" << doc + 1 << endl;
                }
            }
        }
        cout << "û�л��ߵȴ����\n";
    }

    void queryPatient(int department, const string& name) {
        int position = 0;
        bool found = false;
        for (int doc = 0; doc < 2; ++doc) {
            LinkedListQueue& queue = patientQueues[department][doc];
            LinkedListQueue tempQueue;

            while (!queue.isEmpty()) {
                string patientName;
                int patientDepartment, patientDoctor;
                if (queue.dequeue(patientName, patientDepartment, patientDoctor)) {
                    tempQueue.enqueue(patientName, patientDepartment, patientDoctor);
                    if (patientName == name) {
                        cout << name << " �ڿ��� " << department + 1 << "��ǰ���� " << position << " �˵ȴ���\n";
                        found = true;
                        break;
                    }
                    position++;
                }
            }

            while (!tempQueue.isEmpty()) {
                string patientName;
                int patientDepartment, patientDoctor;
                if (tempQueue.dequeue(patientName, patientDepartment, patientDoctor)) {
                    queue.enqueue(patientName, patientDepartment, patientDoctor);
                }
            }
        }
        if (!found) {
            cout << "δ�ҵ����� " << name << "��\n";
        }
    }
};

int main() {
    HospitalQueue hospital;

    // ʾ������
    hospital.enqueuePatient("����1", 0);
    hospital.enqueuePatient("����2", 0);
    hospital.enqueuePatient("����3", 0);
    hospital.enqueuePatient("����4", 1);
    hospital.enqueuePatient("����5", 1);
    hospital.queryPatient(0, "����3");
    hospital.enqueuePatient("����6", 1);
    hospital.enqueuePatient("����7", 2);
    hospital.enqueuePatient("����8", 2);
    hospital.queryPatient(2, "����8");

    // �������໼��
    hospital.enqueuePatient("����9", 0);
    hospital.enqueuePatient("����10", 2);
    hospital.enqueuePatient("����11", 2);
    hospital.queryPatient(2, "����10");
    hospital.enqueuePatient("����12", 1);

    // �Զ��кŲ����߾���
    hospital.treatNextPatients();

    return 0;
}
