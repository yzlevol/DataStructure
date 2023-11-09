#include <iostream>
#include <string>
using namespace std;
struct Patient {
    string name;
    int department; // 科室编号，0表示第一科室，1表示第二科室，2表示第三科室
    int doctor;     // 医生编号，0表示第一个医生，1表示第二个医生
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
        cout << name << " 已入队，等待就诊。就诊科室：" << department + 1 << "，医生编号：" << selectedDoctor + 1 << endl;
    }

    void treatNextPatients() {
        for (int department = 0; department < 3; ++department) {
            for (int doctor = 0; doctor < 2; ++doctor) {
                string name;
                int dep, doc;
                if (patientQueues[department][doctor].dequeue(name, dep, doc)) {
                    cout << "请 " << name << " 就诊，所在科室：" << dep + 1 << "，医生编号：" << doc + 1 << endl;
                }
            }
        }
        cout << "没有患者等待就诊。\n";
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
                        cout << name << " 在科室 " << department + 1 << "，前面有 " << position << " 人等待。\n";
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
            cout << "未找到患者 " << name << "。\n";
        }
    }
};

int main() {
    HospitalQueue hospital;

    // 示例操作
    hospital.enqueuePatient("患者1", 0);
    hospital.enqueuePatient("患者2", 0);
    hospital.enqueuePatient("患者3", 0);
    hospital.enqueuePatient("患者4", 1);
    hospital.enqueuePatient("患者5", 1);
    hospital.queryPatient(0, "患者3");
    hospital.enqueuePatient("患者6", 1);
    hospital.enqueuePatient("患者7", 2);
    hospital.enqueuePatient("患者8", 2);
    hospital.queryPatient(2, "患者8");

    // 创建更多患者
    hospital.enqueuePatient("患者9", 0);
    hospital.enqueuePatient("患者10", 2);
    hospital.enqueuePatient("患者11", 2);
    hospital.queryPatient(2, "患者10");
    hospital.enqueuePatient("患者12", 1);

    // 自动叫号并患者就诊
    hospital.treatNextPatients();

    return 0;
}
