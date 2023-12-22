/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 16.12.2023 */

#include <iostream>
#include <string>
#include <sstream>
#include <map>
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
};

Employee::Employee(int id, int salary, int department)
{
    this->id = id;
    this->salary = salary;
    this->department = department;
}

Employee::~Employee() {}

    // set this employee's id with given number
void Employee::set_id(int id) {this->id = id;}

    // set this employee's salary with given number
void Employee::set_salary(int salary) {this->salary = salary;}

    // set this employee's department with given number
void Employee::set_department(int department) {this->department = department;}

    // get this employee's id
int Employee::get_id() {return this->id;}

    // get this employee's salary
int Employee::get_salary() {return this->salary;}

    // get this employee's department
int Employee::get_department() {return this->department;}

void printToFile(ofstream& output_file, map<int, Employee*>& employeeMap) 
{   
    output_file << "Employee_ID;Salary;Department\n";
    for (auto pair : employeeMap) {
        output_file << pair.second->get_id() << ';' 
                    << pair.second->get_salary() << ';' 
                    << pair.second->get_department() << '\n';
    }
}

void deleteAll(map<int, Employee*> employeeMap)
{   
    // delete employees to avoid memory leak
    for (auto pair : employeeMap) {
        delete pair.second;
    }
}

int main (int argc, char** argv)
{
    fstream read_file;
    string line, id, salary, department, operation;
    int maxEmployeeID = 0;
    map<int, Employee*> employeeMap;

    // Open and read data from the first input file
    read_file.open(argv[1]);
    getline(read_file, line);

    while (getline(read_file, line)) {

        istringstream ss(line);
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department,'\r');
        Employee* new_emp = new Employee(stoi(id), stoi(salary), stoi(department));
        employeeMap[stoi(id)] = new_emp;
        maxEmployeeID = max(stoi(id), maxEmployeeID);
    }
    maxEmployeeID++;
    read_file.close();
    read_file.open(argv[2]);
    // read operation file and call functions related to it
    while(getline(read_file, line)){

        istringstream ss_2(line);
        getline(ss_2, operation, ';');
        // call add function if the operation is ADD
        if (operation == "ADD") {
            
            getline(ss_2, salary, ';');
            getline(ss_2, department,'\r');
            Employee* new_emp = new Employee(maxEmployeeID, stoi(salary), stoi(department));
            // clock_t start = clock();
            employeeMap[maxEmployeeID] = new_emp;
            maxEmployeeID++;
            // clock_t end = clock();
            // cout << "ADD: map_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n"
        }
        // call delete function if the operation is DELETE
        if (operation == "DELETE") {

            getline(ss_2, id, '\r');
            // clock_t start = clock();

            // iterator traverses the map and trys to find
            // given id, if not found, iterator reaches the end
            auto it = employeeMap.find(stoi(id));

            // Check if the employee with the given ID exists in the map
            if (it != employeeMap.end()) {
                // Erase the employee with the given ID
                delete it->second;
                employeeMap.erase(it);

            } else if (employeeMap.empty()) {
                cout << "ERROR: There is no Employee\n";
            } else {
                cout << "ERROR: An invalid ID to delete\n";
            }
            // clock_t end = clock();
            // cout << "DELETE: map_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
        // call update function if the operation is UPDATE
        if (operation == "UPDATE") {

            getline(ss_2, id, ';');
            getline(ss_2, salary, ';');
            getline(ss_2, department, '\r');
            // clock_t start = clock();

            // iterator traverses the map and trys to find
            // given id, if not found, iterator reaches the end
            auto it = employeeMap.find(stoi(id));

            // Check if the employee with the given ID exists in the map
            if (it != employeeMap.end()) {

                it->second->set_salary(stoi(salary));
                it->second->set_department(stoi(department));

            } else {
                cout << "ERROR: An invalid ID to update\n";
            }
            // clock_t end = clock();
            // cout << "UPDATE: map_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
    }
    read_file.close();
    // print the data to file
    ofstream output_file("output.csv");
    printToFile(output_file, employeeMap);
    output_file.close();
    // delete all data
    deleteAll(employeeMap);
    
    return 0;
}