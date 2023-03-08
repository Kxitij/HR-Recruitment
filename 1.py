class Employee:
    def __init__(self, name, designation):
        self.name = name
        self.designation = designation
        self.next_employee = None

class HRSystem:
    def __init__(self):
        self.head = None
    
    def insert(self, name, designation):
        new_employee = Employee(name, designation)
        
        # If the list is empty, set the new employee as the head
        if self.head is None:
            self.head = new_employee
            return
        
        # Find the last employee in the list
        last_employee = self.head
        while last_employee.next_employee:
            last_employee = last_employee.next_employee
        
        # Add the new employee to the end of the list
        last_employee.next_employee = new_employee
        
    def display(self):
        current_employee = self.head
        
        while current_employee:
            print(f"{current_employee.name} ({current_employee.designation})")
            current_employee = current_employee.next_employee


hr_system = HRSystem()
print("enter name and designation:")

hr_system.insert("John Doe", "Manager")
hr_system.insert("Jane Smith", "Assistant Manager")
hr_system.insert("Bob Johnson", "Intern")

hr_system.display()


