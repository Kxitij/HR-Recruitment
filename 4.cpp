#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Employee {
    string name;
    string designation;
    Employee* next;
};

int RankDesignation(string desi){
    if (desi=="CEO"||desi=="ceo") return 5;
    if (desi=="COO"||desi=="coo") return 4;
    if (desi=="Manager"||desi=="manager") return 3;
    if (desi=="Assistant Manager"||desi=="assistant manager") return 2;
    if (desi=="Intern"||desi=="intern") return 1;
     
    
}
Employee*sort_list(Employee* head)
{
Employee *ptr1, *ptr2, *temp;
ptr1 = head;
while(ptr1 -> next != NULL)
{
 ptr2 = ptr1 -> next;
 int des1 = RankDesignation(ptr1->designation);
 int des2 = RankDesignation(ptr2->designation);
 while(ptr2 != NULL)
 {
 if(des1> des2)
 { temp->designation=ptr1->designation;
   temp->name=ptr1->name;
   ptr1->designation=ptr2->designation;
   ptr1->name=ptr2->name;
   ptr2->designation=temp->designation;
   ptr2->name=temp->name;
 
 }
 ptr2 = ptr2 -> next;
 }
 ptr1 = ptr1 -> next;

 }
return head; // Had to be added 
}

Employee* sortLinkedList(Employee* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    bool swapped;
    Employee* ptr1;
    Employee* lptr = NULL;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (RankDesignation(ptr1->designation) < RankDesignation(ptr1->next->designation)) {
    //             string temp_name = a->name;
    // string temp_desig = a->designation;
    // a->name = b->name;
    // a->designation = b->designation;
    // b->name = temp_name;
    // b->designation = temp_desig;
                string temp_name = ptr1->name;
                string temp_desig = ptr1->designation;
                ptr1->designation = ptr1->next->designation;
                ptr1->name = ptr1->next->name;
                ptr1->next->designation = temp_desig;
                ptr1->next->name = temp_name;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return head;
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
    head2 = sortLinkedList(head);
    print(head2);
    saveToFile(head2, "sorted_employees.txt");
    
    return 0;
}
