#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    string name;
    string designation;
    Employee* next;
};


void insert(Employee*& head, string name, string designation) {
    Employee* newNode = new Employee;
    newNode->name = name;
    newNode->designation = designation;
    newNode->next = nullptr;
    
    if (head == nullptr) {
        head = newNode;
    } else {
        Employee* current = head;
        Employee* prev = nullptr;
        while (current != nullptr && current->designation < designation) {
            prev = current;
            current = current->next;
        }
        if (prev == nullptr) {
            newNode->next = head;
            head = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
    }
}


void print(Employee* head) {
    Employee* current = head;
    while (current != nullptr) {
        cout << current->name << " - " << current->designation << endl;
        current = current->next;
    }
}


void saveToFile(Employee* head, string filename) {
    ofstream outFile(filename);
    Employee* current = head;
    while (current != nullptr) {
        outFile << current->name << "," << current->designation << endl;
        current = current->next;
    }
    outFile.close();
}

int main() {
    Employee* head = nullptr;
    ifstream inFile("employees.txt");
    string name, designation;
    while (getline(inFile, name, ',') && getline(inFile, designation)) {
        insert(head, name, designation);
    }
    inFile.close();
    print(head);
    saveToFile(head, "sorted_employees.txt");
    return 0;
}
