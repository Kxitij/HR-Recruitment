#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    string name;
    string designation;
    Employee* next;
};

int get_priority(string designation) {
    if (designation == "CEO") {
        return 1;
    } else if (designation == "Manager") {
        return 2;
    } else if (designation == "Assistant Manager") {
        return 3;
    } else if (designation == "Intern") {
        return 4;
    } else {
        return 5; // unrecognized designation
    }
}

Employee* merge(Employee* left, Employee* right) {
    Employee* dummy = new Employee{"", "", nullptr};
    Employee* tail = dummy;
    
    while (left != nullptr && right != nullptr) {
        if (get_priority(left->designation) <= get_priority(right->designation)) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    
    if (left != nullptr) {
        tail->next = left;
    } else {
        tail->next = right;
    }
    
    Employee* result = dummy->next;
    delete dummy;
    return result;
}

Employee* merge_sort(Employee* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    
    // split list in half
    Employee* slow = head;
    Employee* fast = head->next;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Employee* right = slow->next;
    slow->next = nullptr;
    
    // sort left and right halves
    Employee* left_sorted = merge_sort(head);
    Employee* right_sorted = merge_sort(right);
    
    // merge sorted halves
    return merge(left_sorted, right_sorted);
}







void insert(Employee*& head, string name, string designation) {
    Employee* newEmp = new Employee;
    newEmp->name = name;
    newEmp->designation = designation;
    newEmp->next = nullptr;
    
    if (head == nullptr) {
        head = newEmp;
    } else {
        Employee* last_employee = head;
        while (last_employee->next != NULL) {
            last_employee = last_employee->next;
        }
        
        
        last_employee->next = newEmp;
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
    Employee* head = nullptr, *head2 = nullptr;
    ifstream inFile("employees.txt");
    string name, designation;
    while (getline(inFile, name, ',') && getline(inFile, designation)) {
        insert(head, name, designation);
    }
    inFile.close();
    print(head);
    head2 = merge_sort(head);
    print(head2);
    saveToFile(head2, "sorted_employees.txt");
    
    return 0;
}
