/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 21.10.2023 */

#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Employee {

    private:

        int id;
        int salary;
        int department;

    public:

        Employee(int, int, int);
        ~Employee();
        int get_id();
        int get_salary();
        int get_department();
        void set_salary(int);
        void set_id(int);
        void set_department(int);
        void add_emp(list<Employee>&, int, int, int&, int&);
        void update_emp(list<Employee>&, int, int, int);
        void delete_emp(list<Employee>&, int, int&);
};

Employee::Employee(int id, int salary, int department) {

    this->id = id;
    this->salary = salary;
    this->department = department;
}

Employee::~Employee() {}

    // set this employee's id with given number
void Employee::set_id(int id) {

    this->id = id;
}

    // set this employee's salary with given number
void Employee::set_salary(int salary) {

    this->salary = salary;
}

    // set this employee's department with given number
void Employee::set_department(int department) {

    this->department = department;
}

    // get this employee's id
int Employee::get_id() {

    return this->id;
}

    // get this employee's salary
int Employee::get_salary() {

    return this->salary;
}

    // get this employee's department
int Employee::get_department() {

    return this->department;
}

void Employee::add_emp (list<Employee>& emp_list, int salary, int department, int& id_holder, int& size) {
    
    emp_list.push_back(Employee(id_holder, salary, department));
    size++;
    id_holder++;
}

void Employee::delete_emp (list<Employee>& emp_list, int id, int& size) {

    if(emp_list.empty()) {

        cout << "ERROR: There is no Employee";
        return;
    }

    for(auto it = emp_list.begin(); it != emp_list.end(); ++it){

        if(it->get_id() == id) {
        
            it = emp_list.erase(it);  
            size--;
            return;   
        }
    }

    cout << "ERROR: An invalid ID to delete";

}

void Employee::update_emp (list<Employee>& emp_list, int id, int salary, int department) {

    for(auto it = emp_list.begin(); it != emp_list.end(); ++it){

        if(it->get_id() == id) {
        
            it->set_salary(salary);
            it->set_department(department); 
            return;   
        }
    }

    cout << "ERROR: An invalid ID to update";
}

int main(int argc, char** argv) {

    string line, id, salary, department, operation;
    int size;
    int id_holder = 500001;
    list<Employee> emp_list;
    ifstream read_file(argv[1]);

    getline(read_file, line);
    while(getline(read_file, line)) {

        istringstream ss(line);
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department);

        emp_list.push_back(Employee(stoi(id), stoi(salary), stoi(department)));

    }

    read_file.close();
    read_file.open(argv[2]);

    while(getline(read_file, line)) {
        
        istringstream ss_1(line);
        getline(ss_1, operation, ';');
        
        if(operation == "ADD") {

            getline(ss_1, salary, ';');
            getline(ss_1, department);
            emp_list.begin()->add_emp(emp_list, stoi(salary), stoi(department), id_holder, size);
        }

        if(operation == "DELETE") {

            getline(ss_1, id, '\r');
            emp_list.begin()->delete_emp(emp_list, stoi(id), size);
        }

        if(operation == "UPDATE") {
            
            getline(ss_1, id, ';');
            getline(ss_1, salary, ';');
            getline(ss_1, department);
            emp_list.begin()->update_emp(emp_list, stoi(id), stoi(salary), stoi(department));
        }
    }

    read_file.close();
    ofstream output("list_solution.csv");
    output << "Employee_ID;Salary;Department\n";

    for(auto it = emp_list.begin(); it != emp_list.end(); ++it) {
        output << it->get_id() << ';' << it->get_salary() << ';' << it->get_department() << '\n';
    }
    output.close();

    emp_list.clear();

    return 0;
}