/* @Author
Student Name : Enes Saçak
StudentID : 150210014
Date : 21.10.2023 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

    // search for employee with given id
bool search_employee(string argv_s, string id) {  

    string line, id_f;
    fstream file_read(argv_s);

    // traverse the file, if exists, return true
    while(getline(file_read, line)) {  

        istringstream ss(line);
        getline(ss, id_f, ';');
        if(id_f == id) {
            return true;
        }
    }
    return false;
}

    // add employee with given salary and department
void add_employee(string argv_s, int& id_holder, string salary, string department) {  

    ofstream append(argv_s, ios::app);
    append << id_holder << ";" << salary << ";" << department << '\n';
    id_holder++;
    append.close();
}

    // update an employee's salary and department
void update_employee(string argv_s, string id, string salary, string department) {  

    if(!search_employee(argv_s, id)) {
    // if no employee with this id, exit
        cout << "ERROR: An invalid ID to update";  
        return;
    }

    stringstream buffer;  
    fstream read_file(argv_s);
    string line;
    string id_s;

    // read the file and store data into buffer
    while(getline(read_file, line)) {  

        istringstream ss(line);
        getline(ss, id_s, ';');

    // find employee and set new salary and new department
        if(id_s == id) {  
            line = id + ';' + salary + ';' + department;
        }

        buffer << line << '\n';
    }
    read_file.clear();
    read_file.seekp(0);
    // write the whole new data
    read_file << buffer.rdbuf();  
    read_file.close();
}

void delete_employee(string argv_s, string id, int& size) {

    // if there is no employee
    if(size < 1){
        cout << "ERROR: There is no Employee";  
        return;
    }
    // if no employee with this id, exit
    if(!search_employee(argv_s, id)) {
        cout << "ERROR: An invalid ID to delete";  
        return;
    }
    
    stringstream buffer;
    fstream read_file(argv_s);
    string line;
    string id_s;

    // read the file and store data into buffer
    while(getline(read_file, line)) {  

        istringstream ss(line);
        getline(ss, id_s, ';');

    // for this employee, skip
        if(id_s == id) {  
            continue;
        }
        buffer << line << '\n';
    }
    // clear the file with trunc
    fstream clear_file(argv_s, fstream::out | fstream::trunc);  

    // write stored actual data
    clear_file << buffer.rdbuf();  
    read_file.close();
    clear_file.close();
    size--;
}

int main(int argc, char** argv) {

    ifstream read_file;
    string line, id, salary, department, operation, id_holders;
    int id_holder = 0;
    int size = 0;
    string argv_s = argv[1];

    // open employee data file
    read_file.open(argv[1]);  
    // skip the header line
    getline(read_file, line);  
    
    // read employee data and find last id
    while(getline(read_file, line)) {  

        istringstream ss(line);
    // get last employee's id
        getline(ss, id_holders, ';');
        size++;  
    }
    
    // add 1 to last employee's id
    id_holder = stoi(id_holders) + 1;  
    read_file.close();
    read_file.open(argv[2]);

    // read operations file and take action
    while(getline(read_file, line)) {  

    // break actual line into pieces
        istringstream ss(line);  
        getline(ss, operation, ';');

    // if the operation is add, call add_employee
        if(operation == "ADD") {  

            getline(ss, salary, ';');
            getline(ss, department);
            add_employee(argv_s, id_holder, salary, department);
            size++;

    // if the operation is delete, call delete_employee
        }else if(operation == "DELETE") {  

            getline(ss, id, '\r');
            delete_employee(argv_s, id, size);

    // if the operation is update, call update_employee
        }else if(operation == "UPDATE") {  
            
            getline(ss, id, ';');
            getline(ss, salary, ';');
            getline(ss, department);
            update_employee(argv_s, id, salary, department);
        }
    }

    read_file.close();
    return 0;
}