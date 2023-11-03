/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 21.10.2023 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

class Node {

    private:
        int id;
        int salary;
        int department;
        Node* next;
    public:
        Node(int, int, int);
        ~Node();
        int get_id();
        int get_salary();
        int get_department();
        Node* get_next();
        void set_id(int);
        void set_salary(int);
        void set_department(int);
        void set_next(Node*);
        Node* search_emp(Node*, int);
        void add_emp(Node*&, int, int, int&);
        void delete_emp(Node*&, int);
        void update_emp(Node*&, int, int, int);
        void delete_data(Node*&);
};

Node::Node(int id, int salary, int department) {
    this->id = id;
    this->salary = salary;
    this->department = department;
    this->next = NULL;
}

Node::~Node() {

}

int Node::get_id() {

    return this->id;
}

int Node::get_salary() {

    return this->salary;
}

int Node::get_department() {

    return this->department;
}

Node* Node::get_next() {

    return this->next;
}

void Node::set_id(int id) {

    this->id = id;
}

void Node::set_salary(int salary) {

    this->salary = salary;
}

void Node::set_department(int department) {

    this->department = department;
}

void Node::set_next(Node* next) {

    this->next = next;
}

void Node::add_emp(Node*& head, int salary, int department, int& id_holder) {

    Node* new_node = new Node(id_holder, salary, department);
    if (head == NULL) {
        head = new_node;
    } else {
        Node* current = head;
        while(current->get_next() != NULL) {
            current = current->get_next();
        }
        current->set_next(new_node);
    }
    id_holder++;
}

void Node::update_emp(Node*& head, int id, int salary, int department) {

    Node* prev = search_emp(head, id);
    if (prev == NULL) {

        cout << "ERROR: An invalid ID to update";
        return;
    }
    if (id == 1) {

        prev->set_salary(salary);
        prev->set_department(department);
    } else {

        Node* current = prev->get_next();
        current->set_salary(salary);
        current->set_department(department);
    }
}

void Node::delete_emp(Node*& head, int id) {

    Node* prev = search_emp(head, id);

    if (head == NULL) {

        cout << "ERROR: There is no Employee";
        return;
    }

    if (prev == NULL) {

        cout << "ERROR: An invalid ID to delete";
        return;
    }

    if (head->get_id() == id) {

        Node* temp = head;
        head = head->get_next();
        delete temp;
        return;
    }

    Node* to_be_deleted = prev->get_next();
    prev->set_next(to_be_deleted->get_next());
    delete to_be_deleted;
}

Node* Node::search_emp(Node* head, int id) {

    if (!head) {

        return NULL;
    }

    if (head->get_id() == id) {

        return head;
    }

    Node* current = head;
    Node* previous = NULL;

    while(current != NULL) {
        
        if (current->get_id() == id) {

            return previous;
        }
        previous = current;
        current = current->get_next();
    }

    return NULL;
}

void Node::delete_data(Node*& head) {

    Node* temp;

    while (head) {

        temp = head;
        head = head->get_next();

        delete temp;
    }
}

int main(int argc, char** argv) {

    string line, id_holder_s, id, salary, department, operation;
    int id_holder = 0;

    ifstream read_file(argv[1]);
    while(getline(read_file, line)) {

        istringstream ss(line);
        getline(ss, id_holder_s, ';');
    }

    id_holder = stoi(id_holder_s) + 1;
    read_file.close();

    Node* head = NULL;
    Node* current = NULL;

    read_file.open(argv[1]);
    getline(read_file, line);

    while(getline(read_file, line)) {

        istringstream ss_1(line);

        getline(ss_1, id, ';');
        getline(ss_1, salary, ';');
        getline(ss_1, department);

        Node* new_node = new Node(stoi(id), stoi(salary), stoi(department));
        if (head == NULL){
            head = new_node;
            current = head;
        } else {
            current->set_next(new_node);
            current = new_node;
        } 
    }

    read_file.close();
    read_file.open(argv[2]);
    while(getline(read_file, line)){

        istringstream ss_2(line);
        getline(ss_2, operation, ';');
        
        if (operation == "ADD") {
            
            getline(ss_2, salary, ';');
            getline(ss_2, department);
            head->add_emp(head, stoi(salary), stoi(department), id_holder);
        }

        if (operation == "DELETE") {

            getline(ss_2, id, '\r');
            head->delete_emp(head, stoi(id));
        }

        if (operation == "UPDATE") {

            getline(ss_2, id, ';');
            getline(ss_2, salary, ';');
            getline(ss_2, department);
            head->update_emp(head, stoi(id), stoi(salary), stoi(department));
        }
    }
    
    ofstream output("linked_list_solution.csv");  
    output << "Employee_ID;Salary;Department\n";  
    Node* temp = head;
    while(temp != NULL) {
        output << temp->get_id() << ';' << temp->get_salary() << ';' << temp->get_department() << '\n';
        temp = temp->get_next();
    }

    head->delete_data(head);

    return 0;
}