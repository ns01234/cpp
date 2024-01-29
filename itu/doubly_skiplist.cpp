/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 07.01.2024 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;

const int MAX_ID = 1000000007;

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

class DoublySkipList_Node {

    private:
        Employee* data;
        DoublySkipList_Node* next;
        DoublySkipList_Node* below;
    public:
        DoublySkipList_Node(Employee *data);
        ~DoublySkipList_Node();
        DoublySkipList_Node* get_next();
        DoublySkipList_Node* get_below();
        Employee* get_data();
        int get_node_id();
        void set_next(DoublySkipList_Node* n);
        void set_below(DoublySkipList_Node* n);
        void set_data(Employee* data);
};

class DoublySkipList{
    private:
        DoublySkipList_Node* head;
        int height;
    public:
        DoublySkipList(int height_in);
        ~DoublySkipList();
        void insert(Employee* data);
        void remove(int remove_id);
        Employee* search(int search_id);
        void dumpToFile(ofstream& out_file);
        int randomLevel();
        void update(int id, int salary, int depatment);
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
    // node constructor
DoublySkipList_Node::DoublySkipList_Node(Employee *data)
{
    this->data = data;
    this->below = nullptr;
    this->next = nullptr;
}
    // node destructor, memory handled in list class
DoublySkipList_Node::~DoublySkipList_Node() {}
    // return node's employee
Employee* DoublySkipList_Node::get_data()
{
    return this->data;
}
    // return this node's next
DoublySkipList_Node* DoublySkipList_Node::get_next()
{
    return this->next;
}
    // return this node's below
DoublySkipList_Node* DoublySkipList_Node::get_below()
{
    return this->below;
}
    // set this node's employee
void DoublySkipList_Node::set_data(Employee* data)
{
    this->data = data;
}
    // set this node's next
void DoublySkipList_Node::set_next(DoublySkipList_Node* n)
{
    this->next = n;
}
    // set this node's below
void DoublySkipList_Node::set_below(DoublySkipList_Node* n)
{
    this->below = n;
}
    // return the id of employee in this node
int DoublySkipList_Node::get_node_id()
{
    return this->data->get_id();
}
    // skip list constructor which creates two sentinels
    // with given heigh input
DoublySkipList::DoublySkipList(int height_in)
{   
    Employee* headerEmp = new Employee(-1, 0, 0);
    Employee* endEmp = new Employee(MAX_ID, 0, 0);
    this->head = new DoublySkipList_Node(headerEmp);
    DoublySkipList_Node* temp = head;
    DoublySkipList_Node* temp2 = new DoublySkipList_Node(endEmp);
    temp->set_next(temp2);

    // for loop to add nodes mutually
    for (int i = 1; i <= height_in; ++i) {
        
        DoublySkipList_Node* belowNode = new DoublySkipList_Node(headerEmp);
        temp->set_below(belowNode);
        temp = belowNode;

        DoublySkipList_Node* endNode = new DoublySkipList_Node(endEmp);
        temp2->set_below(endNode);
        temp2 = endNode;
        temp->set_next(temp2);
    }
    // set this list's height with height input
    this->height = height_in;
}
    // destructor to avoid memory leak
DoublySkipList::~DoublySkipList()
{
    DoublySkipList_Node* temp = head;
    DoublySkipList_Node* belowNode = head->get_below();
    DoublySkipList_Node* temp2 = temp->get_next();

    // this loop deletes nodes level by level
    // and exits when it reaches the floor
    while (temp->get_below()) {

        temp2 = temp->get_next();
        belowNode = temp->get_below();

        while (temp2) {

            delete temp;
            temp = temp2;
            temp2 = temp2->get_next();
        }

        delete temp;
        temp = belowNode;
    }
    temp2 = temp->get_next();
    
    // since temp is at the floor
    // delete nodes and employee datas
    while (temp2) {

        delete temp->get_data();
        delete temp;
        temp = temp2;
        temp2 = temp2->get_next();
    }
    delete temp->get_data();
    delete temp;
}
    // random function to be used for insertion
    // the new level can be at most the height of the list
int DoublySkipList::randomLevel()
{
    int lvl = 0;
    while (rand() % 2 && lvl < height) {
        lvl++;
    }
    return lvl;
}
    // insert function which uses 0,5 probability
void DoublySkipList::insert(Employee* data)
{   
    DoublySkipList_Node* temp = head;
    DoublySkipList_Node* addedLast = nullptr;
    int count = height;
    int newLevel = randomLevel();
    while (temp) {
        
        // while next node is smaller than data's id
        // go further and when not, go down and try to find correct plase
        while (temp->get_next()->get_node_id() < data->get_id()) {
            temp = temp->get_next();
        }

        // counter started at height and after reaching
        // newLevel, it starts insertion
        if (count <= newLevel) {
            
            DoublySkipList_Node* newNode = new DoublySkipList_Node(data);
            newNode->set_next(temp->get_next());
            temp->set_next(newNode);
            if (addedLast)
                addedLast->set_below(newNode);
            addedLast = newNode;
        }

        temp = temp->get_below();
        count--;
    }
}
    // remove a node with given employee id
void DoublySkipList::remove(int remove_id)
{   
    DoublySkipList_Node* temp = head;

    // this loop is only for checking "no employee" error
    while (temp->get_below())
        temp = temp->get_below();

    if (temp->get_next()->get_node_id() == MAX_ID) {

        cout << "ERROR: There is no employee\n";
        return;
    }
    
    temp = head;
    bool isDeleted = false;

    // the same traverse logic, when it finds the node
    // (always the top node), delete it and below nodes 
    while (temp) {

        while (temp->get_next()->get_node_id() < remove_id) {
            temp = temp->get_next();
        }
        
        if (temp->get_next()->get_node_id() == remove_id) {
            DoublySkipList_Node* toDelete = temp->get_next();
            temp->set_next(toDelete->get_next());
            
            // if we are at the floor, delete this node's data too
            if (!toDelete->get_below())
                delete toDelete->get_data();
            delete toDelete;
            isDeleted = true;
        }

        if (temp->get_below()) {
            temp = temp->get_below();

        } else {
            break;   
        }
    }
    // if anything is deleted, throw an error
    if (!isDeleted) {

        cout << "ERROR: An invalid ID to delete\n";
        return;
    }
}
    // search function which uses the same traverse logic
Employee* DoublySkipList::search(int search_id)
{
    DoublySkipList_Node* temp = head;

    while (temp) {

        while (temp->get_next()->get_node_id() < search_id) {
            temp = temp->get_next();
        }

        if (temp->get_below()) {
            temp = temp->get_below();

        } else {
            break;   
        }
    }

    // after the loop, if temp's next is not required node
    // return nullptr
    if (temp->get_next()->get_node_id() != search_id) {
        return nullptr;
    }
    // else return required employee
    return temp->get_next()->get_data();
}
    // update an employee with given information using search function
void DoublySkipList::update(int id, int salary, int department)
{   
    Employee* emp = search(id);
    if (emp == nullptr) {
        
        cout << "ERROR: An invalid ID to update\n";
        return;
    }

    emp->set_salary(salary);
    emp->set_department(department);
}
    // print all content by going floor and traversing
    // each node except sentinels
void DoublySkipList::dumpToFile(ofstream& out_file)
{
    DoublySkipList_Node* temp = head;

    while (temp->get_below()) {
        temp = temp->get_below();
    }
    
    out_file << "Employee_ID;Salary;Department\n";

    while (temp->get_next()->get_node_id() != MAX_ID) {

        out_file << to_string(temp->get_next()->get_data()->get_id()) + ';' + 
                    to_string(temp->get_next()->get_data()->get_salary()) + ';' +
                    to_string(temp->get_next()->get_data()->get_department()) + '\n';

        temp = temp->get_next();
    }
}

int main (int argc, char** argv)
{
    ifstream read_file;
    ofstream out_file;
    string line, id, salary, department, operation;
    int maxEmployeeID = 0;
    // experimentally the height of 20 seems like the best
    DoublySkipList* dsl = new DoublySkipList(20);

    read_file.open(argv[1]);
    getline(read_file, line);

    // create skip list with given dataset
    while (getline(read_file, line)) {
        
        istringstream iss(line);
        getline(iss, id, ';');
        getline(iss, salary, ';');
        getline(iss, department, '\r');
        Employee* new_emp = new Employee(stoi(id), stoi(salary), stoi(department));
        dsl->insert(new_emp);
        maxEmployeeID = max(maxEmployeeID, stoi(id));
    }

    read_file.close();
    read_file.open(argv[2]);
    while(getline(read_file, line)) {

        istringstream ss_2(line);
        getline(ss_2, operation, ';');
        // call add function if the operation is ADD
        if (operation == "ADD") {
            
            getline(ss_2, salary, ';'); 
            getline(ss_2, department, '\r');
            // clock_t start = clock();
            Employee* newEmployee = new Employee(++maxEmployeeID, stoi(salary), stoi(department));
            dsl->insert(newEmployee);
            // clock_t end = clock();
            // cout << "ADD: doubly_skiplist_solution: " (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n"
        }
        // call delete function if the operation is DELETE
        else if (operation == "DELETE") {

            getline(ss_2, id, '\r');
            // clock_t start = clock();
            dsl->remove(stoi(id));
            // clock_t end = clock();
            // cout << "DELETE: doubly_skiplist_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
        // call update function if the operation is UPDATE
        else if (operation == "UPDATE") {

            getline(ss_2, id, ';');
            getline(ss_2, salary, ';');
            getline(ss_2, department, '\r');
            // clock_t start = clock();
            dsl->update(stoi(id), stoi(salary), stoi(department));
            // clock_t end = clock();
            // cout << "UPDATE: doubly_skiplist_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
    }
    read_file.close();
    out_file.open("doubly_output.csv");
    dsl->dumpToFile(out_file);
    out_file.close();
    delete dsl;
    return 0;
}