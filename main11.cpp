/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 21.10.2023 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;

class Employee {
private:
    int id;
    int salary;
    int department;
public:
    Employee();
    ~Employee();
    int get_id();
    int get_salary();
    int get_department();
    void set_salary(int);
    void set_id(int);
    void set_department(int);
    Employee* add_emp(Employee*&, int, int, int&, int&);
    void update_emp(Employee*, int, int, int, int);
    Employee* delete_emp(Employee*&, int, int&);
    int search_emp(Employee*, int, int);
};

Employee::Employee() {}

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

    // search an employee with given id and return it's actual index
int Employee::search_emp(Employee* array, int id, int size) {  

    int index = 0;
    while (index < size) {
        if (array[index].get_id() == id) {
            return index;
        }
        index++;
    }
    // if not found, return -1
    return -1;
}

    // add one employee with given salary and department
Employee* Employee::add_emp(Employee*& array, int salary, int department, int& size, int& id_holder) {

    // new array with one size larger
    Employee* new_array = new Employee[size+1];  

    // transfer old array's data to new array
    for(int i = 0; i < size; i++){  
        new_array[i] = array[i];
    }

    // set id, salary, department of the employee just added
    new_array[size].set_id(id_holder);  
    new_array[size].set_salary(salary);
    new_array[size].set_department(department);
    size++;  
    id_holder++;
    // delete old array to avoid memory leak
    delete[] array;
    return new_array;
}

    // update requested employee's salary and department
void Employee::update_emp(Employee* array, int id, int salary, int department, int size) {  

    // search for the requested employee's index
    int x = search_emp(array, id, size);  

        // if there is no employee with given id
    if(x == -1){  
        cout << "ERROR: An invalid ID to update";
        return;
    }
    array[x].set_salary(salary);
    array[x].set_department(department);
}

    // delete an employee with given id
Employee* Employee::delete_emp(Employee*& array, int id, int& size) {  

    int a = search_emp(array, id, size);
    int j = 0;
    // if no employee in the array 
    if(size == 0){  
        cout << "ERROR: There is no Employee";
        return array;
    }
    // if there is no employee with given id
    if(a == -1){  
        cout << "ERROR: An invalid ID to delete";
        return array;
    }
    // new array with one size smaller
    Employee* new_array = new Employee[size-1];  

    // for the employee to be deleted, i++ and j = j
    for(int i = 0; i < size; i++){  
        if(array[i].get_id() != id){
            new_array[j] = array[i];
            j++;
        }
    }
    // delete old array to avoid memory leak
    delete[] array;
    size--;
    return new_array;
}

int main(int argc, char** argv) {

    ifstream employee_data;
    ofstream new_file;
    string line, id, salary, department, operation, id_holder_s;
    int id_holder = 0;  
    int size = 0;
    int x = 0;

    // open employee data file
    employee_data.open(argv[1]);  
    // skip the header line
    getline(employee_data, line);  

    // read employee data and find last id
    while(getline(employee_data, line)){  

        istringstream ss(line);
    // get last employee's id
        getline(ss, id_holder_s, ';');  
        size++;
    }

    employee_data.close();
    // add 1 to last employee's id
    id_holder = stoi(id_holder_s) + 1;  
    // create an employee array
    Employee* array = new Employee[size];  

    // open the file again to set each employee's information
    employee_data.open(argv[1]);  
    // escape header line
    getline(employee_data, line);  

    while(getline(employee_data, line)){
    // break actual line into pieces and set id, department and salary

        istringstream ss(line);  
        getline(ss, id, ';');
        array[x].set_id(stoi(id));
        getline(ss, salary, ';');
        array[x].set_salary(stoi(salary));
        getline(ss, department, ';');
        array[x].set_department(stoi(department));
        x++;
    }

    employee_data.close();
    // open operations file
    employee_data.open(argv[2]);  

    // read operations file and take action
    while(getline(employee_data, line)){  

        istringstream ss(line);
        getline(ss, operation, ';');

    // if the operation is add, call add_employee
        if(operation == "ADD"){  

            getline(ss, salary, ';');
            getline(ss, department);
            array = array->add_emp(array, stoi(salary), stoi(department), size, id_holder);

    // if the operation is update, call update_employee
        }else if(operation == "UPDATE"){  

            getline(ss, id, ';');
            getline(ss, salary, ';');
            getline(ss, department);
            array->update_emp(array, stoi(id), stoi(salary), stoi(department), size);

    // if the operation is delete, call delete_employee
        }else if(operation == "DELETE"){  
            
            getline(ss, id);
            array = array->delete_emp(array, stoi(id), size);
        }
    }
    // close opened file
    employee_data.close();  

    // print actual data to array_solution.csv file
    ofstream output("array_solution.csv");  
    // print header line
    output << "Employee_ID;Salary;Department\n";  

    for (int i = 0; i < size; i++) {
        output << array[i].get_id() << ';' << array[i].get_salary() << ';' << array[i].get_department() << '\n';
    }
    delete[] array;
    return 0;
}