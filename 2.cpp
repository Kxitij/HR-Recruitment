#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Emp {
public:
    string name;
    string desig;
    Emp* nextEmp;
};

class HRSystem {
private:
    Emp* head;
    
public:
    HRSystem() {
        head = NULL;
    }
    
    void insert(string name, string designation) {
        Emp* newEmp = new Emp;
        newEmp->name = name;
        newEmp->desig = designation;
        newEmp->nextEmp = NULL;
        
        // If the list is empty, set the new employee as the head
        if (head == NULL) {
            head = newEmp;
            return;
        }
        
        // Find the last employee in the list
        Emp* last_employee = head;
        while (last_employee->nextEmp != NULL) {
            last_employee = last_employee->nextEmp;
        }
        
        // Add the new employee to the end of the list
        last_employee->nextEmp = newEmp;
    }
    
    void display() {
        Emp* current_employee = head;
        
        while (current_employee != NULL) {
            cout << current_employee->name << " (" << current_employee->desig << ")" << endl;
            current_employee = current_employee->nextEmp;
        }
    }
    
    void sort_by_designation() {
        // Create a new list for each designation
        Emp* managers = NULL;
        Emp* assistants = NULL;
        Emp* interns = NULL;
        
        // Traverse the original list and add each employee to the appropriate list
        Emp* current_employee = head;
        while (current_employee != NULL) {
            if (current_employee->desig == "Manager") {
                if (managers == NULL) {
                    managers = current_employee;
                } else {
                    Emp* last_manager = managers;
                    while (last_manager->nextEmp != NULL) {
                        last_manager = last_manager->nextEmp;
                    }
                    last_manager->nextEmp = current_employee;
                }
            } else if (current_employee->desig == "Assistant Manager") {
                if (assistants == NULL) {
                    assistants = current_employee;
                } else {
                    Emp* last_assistant = assistants;
                    while (last_assistant->nextEmp != NULL) {
                        last_assistant = last_assistant->nextEmp;
                    }
                    last_assistant->nextEmp = current_employee;
                }
            } else if (current_employee->desig == "Intern") {
                if (interns == NULL) {
                    interns = current_employee;
                } else {
                    Emp* last_intern = interns;
                    while (last_intern->nextEmp != NULL) {
                        last_intern = last_intern->nextEmp;
                    }
                    last_intern->nextEmp = current_employee;
                }
            }
            
            current_employee = current_employee->nextEmp;
        }
        
        // Combine the sorted lists
        Emp* sorted_head = NULL;
        if (managers != NULL) {
            sorted_head = managers;
            while (managers->nextEmp != NULL) {
                managers = managers->nextEmp;
            }
            managers->nextEmp = assistants;
        } else if (assistants != NULL) {
            sorted_head = assistants;
        } else if (interns != NULL) {
            sorted_head = interns;
        }
        
        if (assistants != NULL && interns != NULL) {
            while (assistants->nextEmp != NULL)
            assistants = assistants->nextEmp;
        }
        
        if (interns != NULL) {
            if (sorted_head == NULL) {
                sorted_head = interns;
            } else {
                Emp* last_employee = sorted_head;
                while (last_employee->nextEmp != NULL) {
                    last_employee = last_employee->nextEmp;
                }
                last_employee->nextEmp = interns;
            }
        }
        
        // Set the sorted list as the new head
        head = sorted_head;
    }
    
    void read_file(string file_name) {
        ifstream input_file;
        input_file.open(file_name.c_str());
        
        if (!input_file) {
            cerr << "Unable to open file " << file_name << endl;
            exit(1);
        }
        
        string name;
        string designation;
        while (input_file) {
            getline(input_file, name, ',');
            getline(input_file, designation, ','); 
            insert(name, designation);
        }
        
        input_file.close();
    }
    
    void write_file(string file_name) {
        ofstream output_file;
        output_file.open(file_name.c_str());
        
        if (!output_file) {
            cerr << "Unable to open file " << file_name << endl;
            exit(1);
        }
        
        Emp* current_employee = head;
        while (current_employee != NULL) {
            output_file << current_employee->name << " " << current_employee->desig << endl;
            current_employee = current_employee->nextEmp;
        }
        
        output_file.close();
    }
};

int main() {
    HRSystem hr_system;
    
    // Read data from the input file
    hr_system.read_file("input.txt");
    
    // Sort the employees by designation
    hr_system.sort_by_designation();
    
    // Display the sorted list
    hr_system.display();
    
    // Write the sorted data back to the file
    hr_system.write_file("output.txt");
    
    return 0;
}
