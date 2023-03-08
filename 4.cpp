#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct emp
{
    string name;
    string desig;
    emp* next;
};
class HR{
    private: 
        emp* head;
    public: 
        HR(){
            head = NULL;
        }
        void insertEMP(string name, string designation){
            emp* temp = new emp();
            temp->name = name;
            temp->desig = designation;
            temp->next = head;
            if (head == NULL){ head = temp; return; }
            emp* ptr = head;
            while (ptr->next!= NULL){
                ptr = ptr->next;
            }
            ptr->next = temp;
        }

        void display(){
            emp* current = head;
            while (current!= NULL){
                cout<<"Name: "<<current->name<<"\tDesignation:"<<current->desig<<endl;
                current = current->next;
            }
            cout<<endl;
        }
        
        void swap(emp* a, emp* b) {
            string temp_name = a->name;
            string temp_desig = a->desig;
            a->name = b->name;
            a->desig = b->desig;
            b->name = temp_name;
            b->desig = temp_desig;
        }
        void sort() {
            emp* curr;
            emp* last = NULL;
            bool swapped;

            
            if (head == NULL) {
                return;
            }

            do {
                swapped = false;
                curr = head;

                while (curr->next != last) {
                    // compare the lengths of the designations first
                    if (curr->desig.compare(curr->next->desig) > 0) {
                        swap(curr, curr->next);
                        swapped = true;
                    }
                    curr = curr->next;
                }
                last = curr;
            } while (swapped);
        }
        void readFile(string filename){
    string line;
    ifstream in(filename);
    if (!in){
        cout<<"File not found"<<endl;
        return;
    }
    while (getline(in, line)){
        size_t pos = 0;
        pos = line.find(',');
        if (pos != string::npos){
            string name = line.substr(0,pos);
            string designation = line.substr(pos+1);
            insertEMP(name, designation);
        }
    }
}

        void writeIntoFile(string filename){
            ofstream out(filename);
            if (!out){
                cout<<"File not found"<<endl;
                return;
            }
            for (emp* curr = head; curr!= NULL; curr = curr->next) {
                out << curr->name << " " << curr->desig << endl;
            }
            cout<<"Data entered to the file."<<endl;
            out.close();
        } 
};

int main(){
    HR h;
    h.readFile("employee.txt");
    h.sort();
    h.writeIntoFile("output.txt");
    return 0;
}