/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 16.12.2023 */

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>
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

class Node {

    private:    
        Employee* employee;
        Node* left;
        Node* right;
    public:
        Node(Employee*);
        ~Node();
        Employee* get_employee();
        void set_employee(Employee*);
        Node* get_left();
        Node* get_right();
        void set_left(Node*);
        void set_right(Node*);
};

class BinaryTree {
    
    private:
        Node* root;
        int getHeight(Node* root);
        void printToConsole(Node* root);
    public:
        int size = 0;
        BinaryTree();
        ~BinaryTree();
        void insert(Employee*);
        void remove(int id);
        void update(int id, int salary, int department);
        Employee *search(int id);
        int getHeight();
        void printToFile(ofstream &output_file);
        void printToConsole();
        Node* getRoot();

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

Node::Node(Employee* employee) 
{
    this->employee = employee;
    this->left = nullptr;
    this->right = nullptr;
}

Node::~Node() 
{
    if (employee) {
        delete employee;
        employee = nullptr;
    }
}

// get the Employee object stored in the node
Employee* Node::get_employee() {return this->employee;}

// set the Employee object for the node
void Node::set_employee(Employee* employee) {this->employee = employee;}

// get the left child node
Node* Node::get_left() {return this->left;}

// get the right child node
Node* Node::get_right() {return this->right;}

// set the left child node
void Node::set_left(Node* left) {this->left = left;}

// set the right child node
void Node::set_right(Node* right) {this->right = right;}

BinaryTree::BinaryTree() 
{
    this->root = nullptr;
    this->size = 0;
}
// using stack and inorder traversal
// delete all contents of the binary tree
BinaryTree::~BinaryTree()
{
    if (!root)
        return;

    Node* current = root;
    stack<Node*> nodeStack;

    while (current || !nodeStack.empty()) {

        while (current) {
            nodeStack.push(current);
            current = current->get_left();
        }

        current = nodeStack.top();
        nodeStack.pop();

        Node* rightChild = current->get_right();
        delete current;
        current = rightChild;
    }
}

Node* BinaryTree::getRoot()
{
    return this->root;
}

void BinaryTree::insert(Employee* new_emp)
{   
    // create new node with given employee
    Node* new_node = new Node(new_emp);
    // if there is empty, set it's root to new node
    if (!root) {
        root = new_node;
        return;
    }

    Node* current = root;
    Node* parent = nullptr;
    // find new node's place and it's parent 
    while (current) {
        parent = current;

        if (new_emp->get_id() < current->get_employee()->get_id()) {
            current = current->get_left();
        } else {
            current = current->get_right();
        }
    }
    // if smaller than parent, set left and vice versa
    if (new_emp->get_id() < parent->get_employee()->get_id()) {
        parent->set_left(new_node);
    } else {
        parent->set_right(new_node);
    }
}

void BinaryTree::remove(int id) {

    Node* current = root;
    Node* parent = nullptr;

    // Find the node to be removed and it's parent node
    while (current && current->get_employee()->get_id() != id) {
        parent = current;

        if (id < current->get_employee()->get_id()) {
            current = current->get_left();
        } else {
            current = current->get_right();
        }
    }

    // check if the node with the given id was found
    if (!current) {
        cout << "ERROR: An invalid ID to delete\n";
        return;
    }

    // if current node has at most one child
    // this if block handle if it has no child
    if (!current->get_left() || !current->get_right()) {
        // if current has left child, temp is left, else temp is right (can be nullptr)
        Node* temp = (current->get_left()) ? current->get_left() : current->get_right();

        // if parent is nullptr, first while loop never worked
        // means that the node to be deleted is the root
        if (!parent) {
            root = temp;

        // if node to be deleted is the left child of the parent
        // set parent's left as temp (can be nullptr)
        } else if (parent->get_left() == current) {
            parent->set_left(temp);

        // if node to be deleted is the right child of the parent
        // set parent's right as temp (can be nullptr)
        } else {
            parent->set_right(temp);
        }
        // delete current node
        delete current;
    // if current node has two children
    } else {
        // set successor to root of the right subtree of current node
        Node* successorParent = current;
        Node* successor = current->get_right();
        // if it is already the leftmost node of right subtree,
        // set current node's right as successor's right child
        // this block is different from else block since
        // successorParent is current and we need to set it's right
        if (!successor->get_left()) {
            // delete current node's employee to avoid memory leak
            delete current->get_employee();
            // replace current node with successor
            current->set_employee(successor->get_employee());
            // successor can have it's right subtree
            successorParent->set_right(successor->get_right());
        // for else block successorParent's left child is going to be deleted
        // so set it's left as successor's right
        } else {
        // if not, find the leftmost node by going only left
            while (successor->get_left()) {
                successorParent = successor;
                successor = successor->get_left();
            }
            // delete current node's employee to avoid memory leak
            delete current->get_employee();
            // replace current node with successor
            current->set_employee(successor->get_employee());
            // successor can have it's right subtree
            successorParent->set_left(successor->get_right());
        }
        // since node's destructor deletes employee
        // avoid unintended behaviour by setting employee to nullptr
        successor->set_employee(nullptr);
        delete successor;   
    }
}

void BinaryTree::update(int id, int salary, int department)
{   
    // search function returns the employee's address with given id
    Employee* toUpdate = search(id);
    // if search function returns null, there is no employee with given id
    if (!toUpdate) {
        cout << "ERROR: An invalid ID to update\n";
        return;
    }
    // change salary and department of the employee
    toUpdate->set_salary(salary);
    toUpdate->set_department(department);
}
// search and return the address of given employee
Employee* BinaryTree::search(int id)
{
    // if the tree is empty, return nullptr
    if (!root)
        return nullptr;

    Node* temp = root;
    // search the employee with given id using bst logic
    while (temp && temp->get_employee()->get_id() != id) {

        if (id < temp->get_employee()->get_id()) {
            temp = temp->get_left();
        } else {
            temp = temp->get_right();
        }
    }
    // if found return temp, if not return nullptr
    return temp ? temp->get_employee() : nullptr;
}

// print all content
void printAll(ofstream& output_file, vector<BinaryTree*>& jungle) 
{
    output_file << "Employee_ID;Salary;Department\n";
    for (auto tree : jungle) {
        tree->printToFile(output_file);
    }    
}
// delete all data
void deleteAll(vector<BinaryTree*>& jungle)
{
    for (auto tree : jungle) {
        delete tree;
    }   
}

void BinaryTree::printToFile(ofstream& output_file)
{   
    if (!root)
        return;

    Node* current = root;
    stack<Node*> nodeStack;

    // traverse the tree using stack
    while (current || !nodeStack.empty()) {
        
        // go leftmost node and push every node to the stack
        while (current) {
            nodeStack.push(current);
            current = current->get_left();
        }
        // set current to top of the stack
        current = nodeStack.top();
        nodeStack.pop();
        // directly write to the output file
        output_file << current->get_employee()->get_id() << ';'
                    << current->get_employee()->get_salary() << ';'
                    << current->get_employee()->get_department() << '\n';
        // get right of the current node and push its left in the while loop if it exists
        current = current->get_right();
    }
}

int main (int argc, char** argv)
{
    fstream read_file;
    string line, id, salary, department, operation;
    int maxEmployeeID = 0;
    const int CAPACITY = 5000;
    vector<BinaryTree*> jungle;

    read_file.open(argv[1]);
    getline(read_file, line);
    while (getline(read_file, line)) {

        istringstream ss(line);
        getline(ss, id, ';');
        getline(ss, salary, ';');
        getline(ss, department, '\r');
        Employee* new_emp = new Employee(stoi(id), stoi(salary), stoi(department));
        
        // numbers (id % CAPACITY) are edge cases, so - 1
        int treeIndex = (stoi(id) - 1) / CAPACITY;
        int vecSize = jungle.size();
        
        // create this way to avoid unordered vector for shuffled data
        if (vecSize - 1 < treeIndex) {
            
            while (vecSize - 1 < treeIndex) {
                jungle.push_back(new BinaryTree());
                vecSize++;
            }
            jungle[treeIndex]->insert(new_emp);
        } else {
            jungle[treeIndex]->insert(new_emp);
        }   
    }

    maxEmployeeID = jungle.size() * CAPACITY + 1;
    read_file.close();
    read_file.open(argv[2]);
    // read operation file and call functions related to it
    while(getline(read_file, line)){

        istringstream ss_2(line);
        getline(ss_2, operation, ';');
        // call add function if the operations is ADD
        if (operation == "ADD") {
            
            getline(ss_2, salary, ';');
            getline(ss_2, department, '\r');
            // clock_t start = clock();
            int treeIndex = (maxEmployeeID - 1) / CAPACITY;
            Employee* new_emp = new Employee(maxEmployeeID++, stoi(salary), stoi(department));
            int vecSize = jungle.size();
            if (vecSize - 1 < treeIndex) {

                BinaryTree* bt = new BinaryTree();
                bt->insert(new_emp);
                jungle.push_back(bt);

            } else {
                jungle[treeIndex]->insert(new_emp);
            }
            // clock_t end = clock();
            // cout << "ADD: binary_tree_solution: " (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n"
        }
        // call delete function if the operations is DELETE
        else if (operation == "DELETE") {

            getline(ss_2, id, '\r');
            // clock_t start = clock();
            int treeIndex = (stoi(id) - 1)  / CAPACITY;
            int size = jungle.size();
            bool empty = true;
            for (auto tree : jungle) {
                if (tree->getRoot())
                    empty = false;
            }
            if (empty) {
                cout << "ERROR: There is no employee\n";
                continue;
            }
            if (treeIndex >= size) {
                cout << "ERROR: An invalid ID to delete\n";
                continue;
            }
            jungle[treeIndex]->remove(stoi(id));
            // clock_t end = clock();
            // cout << "DELETE: binary_tree_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
        // call update function if the operations is UPDATE
        else if (operation == "UPDATE") {

            getline(ss_2, id, ';');
            getline(ss_2, salary, ';');
            getline(ss_2, department, '\r');

            // clock_t start = clock();
            int treeIndex = (stoi(id) - 1) / CAPACITY;
            int size = jungle.size();
            if (treeIndex >= size) {

                cout << "ERROR: An invalid ID to update\n";
                continue;
                
            } else {
                jungle[treeIndex]->update(stoi(id), stoi(salary), stoi(department));
            }

            // clock_t end = clock();
            // cout << "UPDATE: binary_tree_solution: " << (double)(end - start) * 1000 / CLOCKS_PER_SEC << "milliseconds\n";
        }
    }
    read_file.close();

    // print all content
    ofstream output_file("output.csv");
    printAll(output_file, jungle);
    output_file.close();
    // delete all binarytrees
    deleteAll(jungle);
    return 0;
}
