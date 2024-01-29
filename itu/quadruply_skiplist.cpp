/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 07.01.2024 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <ctime>
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

class QuadruplySkipList_Node {

    private:
        Employee* data;
        QuadruplySkipList_Node* next;
        QuadruplySkipList_Node* prev;
        QuadruplySkipList_Node* below;
        QuadruplySkipList_Node* above;
    public:
        QuadruplySkipList_Node(Employee *data);
        ~QuadruplySkipList_Node();
        QuadruplySkipList_Node* get_next();
        QuadruplySkipList_Node* get_prev();
        QuadruplySkipList_Node* get_below();
        QuadruplySkipList_Node* get_above();
        Employee* get_data();
        int get_node_id();
        void set_next(QuadruplySkipList_Node* n);
        void set_prev(QuadruplySkipList_Node* n);
        void set_below(QuadruplySkipList_Node* n);
        void set_above(QuadruplySkipList_Node* n);
        void set_data(Employee* data);
};

class QuadruplySkipList{
    private:
        QuadruplySkipList_Node* head;
        int height;
    public:
        QuadruplySkipList(int height_in);
        ~QuadruplySkipList();
        void insert(Employee* data);
        void remove(int remove_id);
        void update(int id, int salary, int department);
        Employee* search(int search_id);
        void dumpToFile(ofstream& out_file);
        int randomLevel();
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
QuadruplySkipList_Node::QuadruplySkipList_Node(Employee *data)
{
    this->data = data;
    this->above = nullptr;
    this->below = nullptr;
    this->next = nullptr;
    this->prev = nullptr;
}
    // node destructor, memory handled in list class
QuadruplySkipList_Node::~QuadruplySkipList_Node() {}
    // return node's employee
Employee* QuadruplySkipList_Node::get_data()
{
    return this->data;
}
    // return this node's next
QuadruplySkipList_Node* QuadruplySkipList_Node::get_next()
{
    return this->next;
}
    // return this node's prev
QuadruplySkipList_Node* QuadruplySkipList_Node::get_prev()
{
    return this->prev;
}
    // return this node's below
QuadruplySkipList_Node* QuadruplySkipList_Node::get_below()
{
    return this->below;
}   // return this node's above
QuadruplySkipList_Node* QuadruplySkipList_Node::get_above()
{
    return this->above;
}
    // set this node's employee
void QuadruplySkipList_Node::set_data(Employee* data)
{
    this->data = data;
}
    // set this node's next
void QuadruplySkipList_Node::set_next(QuadruplySkipList_Node* n)
{
    this->next = n;
}
    // set this node's prev
void QuadruplySkipList_Node::set_prev(QuadruplySkipList_Node* n)
{
    this->prev = n;
}
    // set this node's below
void QuadruplySkipList_Node::set_below(QuadruplySkipList_Node* n)
{
    this->below = n;
}
    // set this node's above
void QuadruplySkipList_Node::set_above(QuadruplySkipList_Node* n)
{
    this->above = n;
}
    // return the id of employee in this node
int QuadruplySkipList_Node::get_node_id()
{
    return this->data->get_id();
}
    // skip list constructor which creates two sentinels
    // with given heigh input
QuadruplySkipList::QuadruplySkipList(int height_in)
{   
    Employee* headerEmp = new Employee(-1, 0, 0);
    Employee* endEmp = new Employee(MAX_ID, 0, 0);
    QuadruplySkipList_Node* headerNode = new QuadruplySkipList_Node(headerEmp);
    QuadruplySkipList_Node* temp = headerNode;
    QuadruplySkipList_Node* temp2 = new QuadruplySkipList_Node(endEmp);
    temp->set_next(temp2);
    temp2->set_prev(temp);

    // for loop to add nodes mutually
    for (int i = 1; i <= height_in; ++i) {
        
        QuadruplySkipList_Node* aboveNode = new QuadruplySkipList_Node(headerEmp);
        aboveNode->set_below(temp);
        temp->set_above(aboveNode);
        temp = aboveNode;

        QuadruplySkipList_Node* endNode = new QuadruplySkipList_Node(endEmp);
        endNode->set_below(temp2);
        temp2->set_above(endNode);
        temp2 = endNode;
        temp->set_next(temp2);
        temp2->set_prev(temp);
    }
    // set this list's height with height input
    // and head with temp (leftmost top node)
    this->head = temp;
    this->height = height_in;
}
    // destructor to avoid memory leak
QuadruplySkipList::~QuadruplySkipList()
{
    QuadruplySkipList_Node* temp = head;

    // go to the floor
    while (temp->get_below()) {
        temp = temp->get_below();
    }

    // delete every node above and go right and keep going
    while (temp) {

        QuadruplySkipList_Node* temp2 = temp->get_next();
        QuadruplySkipList_Node* aboveNode = temp->get_above();

        while (aboveNode) {

            delete temp;
            temp = aboveNode;
            aboveNode = aboveNode->get_above();
        }
        // delete floor nodes' data also
        delete temp->get_data();
        delete temp;
        temp = temp2;
    }
}
    // random function to be used for insertion
    // the new level can be at most the height of the list
int QuadruplySkipList::randomLevel()
{
    int lvl = 0;
    while (rand() % 2 && lvl < height) {
        lvl++;
    }
    return lvl;
}
    // insert function which uses 0,5 probability
void QuadruplySkipList::insert(Employee* data)
{   
    QuadruplySkipList_Node* temp = head;
    QuadruplySkipList_Node* addedLast = nullptr;
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

            QuadruplySkipList_Node* newNode = new QuadruplySkipList_Node(data);
            newNode->set_next(temp->get_next());
            newNode->set_prev(temp);
            temp->get_next()->set_prev(newNode);
            temp->set_next(newNode);
            
            if (addedLast) {

                addedLast->set_below(newNode);
                newNode->set_above(addedLast);
            }
            addedLast = newNode;
        }

        temp = temp->get_below();
        count--;
    }
}
    // remove a node with given employee id
void QuadruplySkipList::remove(int remove_id)
{   
    QuadruplySkipList_Node* temp = head;
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
            QuadruplySkipList_Node* toDelete = temp->get_next();
            toDelete->get_next()->set_prev(temp);
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
Employee* QuadruplySkipList::search(int search_id)
{
    QuadruplySkipList_Node* temp = head;

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
void QuadruplySkipList::update(int id, int salary, int department)
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
void QuadruplySkipList::dumpToFile(ofstream& out_file)
{
    QuadruplySkipList_Node* temp = head;

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
    // experimentally the height of 50 seems like the best
    QuadruplySkipList* qsl = new QuadruplySkipList(20);

    read_file.open(argv[1]);
    getline(read_file, line);

    // create skip list with given dataset
    while (getline(read_file, line)) {
        
        istringstream iss(line);
        getline(iss, id, ';');
        getline(iss, salary, ';');
        getline(iss, department, '\r');
        Employee* new_emp = new Employee(stoi(id), stoi(salary), stoi(department));
        qsl->insert(new_emp);
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
            qsl->insert(newEmployee);
            // clock_t end = clock();
            // cout << "ADD: quadruply_skiplist_solution: " (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n"
        }
        // call delete function if the operation is DELETE
        else if (operation == "DELETE") {

            getline(ss_2, id, '\r');
            // clock_t start = clock();
            qsl->remove(stoi(id));
            // clock_t end = clock();
            // cout << "DELETE: quadruply_skiplist_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
        // call update function if the operation is UPDATE
        else if (operation == "UPDATE") {

            getline(ss_2, id, ';');
            getline(ss_2, salary, ';');
            getline(ss_2, department, '\r');
            // clock_t start = clock();
            qsl->update(stoi(id), stoi(salary), stoi(department));
            // clock_t end = clock();
            // cout << "UPDATE: quadruply_skiplist_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
    }
    read_file.close();
    out_file.open("quadruply_output.csv");
    qsl->dumpToFile(out_file);
    out_file.close();

    delete qsl;
    return 0;
}