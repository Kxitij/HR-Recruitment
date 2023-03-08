#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    string name;
    string designation;
    Employee* next;
};

void insertEmployee(Employee*& head, string name, string designation) {
    Employee* newEmployee = new Employee;
    newEmployee->name = name;
    newEmployee->designation = designation;
    newEmployee->next = NULL;

    if (head == NULL) {
        head = newEmployee;
    } else {
        Employee* current = head;
        Employee* prev = NULL;

        while (current != NULL && current->designation <= designation) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            newEmployee->next = head;
            head = newEmployee;
        } else {
            newEmployee->next = current;
            prev->next = newEmployee;
        }
    }
}

void readFile(Employee*& head, string filename) {
    ifstream infile(filename);

    if (!infile) {
        cout << "Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        size_t pos = line.find(",");
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            string designation = line.substr(pos + 1);
            insertEmployee(head, name, designation);
        }
    }

    infile.close();
}

void writeFile(Employee* head, string filename) {
    ofstream outfile(filename);

    if (!outfile) {
        cout << "Unable to create file " << filename << endl;
        return;
    }

    Employee* current = head;
    while (current != NULL) {
        outfile << current->name << "," << current->designation << endl;
        current = current->next;
    }

    outfile.close();
}

int main() {
    Employee* head = NULL;
    readFile(head, "employees.txt");

    if (head == NULL) {
        cout << "No employees found" << endl;
        return 0;
    }

    writeFile(head, "employees_sorted.txt");

    cout << "Employees sorted and saved to file employees_sorted.txt" << endl;

    return 0;
}
