#include <bits/stdc++.h>
using namespace std;

class Employee {
    string address, name;
    int empid, loc;

    public:
    Employee() {
        address = name = "";
        empid = loc = 0;
    }

    bool isEmpty() {
        return empid == 0;
    }

    void display() {
        cout << empid << " " << name << " " << address << " " << loc << endl;
    }

    friend class HashTable;
    friend class MyFile;
};

class HashTable {
    int tablesize;
    Employee *employee;

    int hashfun(int id) {
        return id % tablesize;
    }

    public:
    HashTable(int size) {
        tablesize = size;
        employee = new Employee[tablesize];

        //Initialize the array
        for(int i=0; i<tablesize; i++) {
            employee[i] = Employee();
        }
    }

    HashTable() {
        cout<<"Enter max number of employees: ";
        cin>>tablesize;
        employee = new Employee[tablesize];
        for(int i=0;i<tablesize;i++) {
            employee[i] = Employee();
        }
    }

    void insertHT(Employee emp) {
        int index = hashfun(emp.empid);

        if(employee[index].isEmpty()) {
            employee[index] = emp;
        }
        else {
            int currIndex = index;
            while(!employee[currIndex].isEmpty()) 
                currIndex = (currIndex + 1) % tablesize;
            employee[currIndex] = emp;
        }
    }

    void showHT() {
        for(int i=0; i<tablesize; i++) {
            cout.width(7);
            cout << employee[i].empid << "\t";
            cout.width(5);
            cout << employee[i].loc << endl;
        }
    }
    
    void deleteHT(int empId) {
        int index = hashfun(empId);
        if(employee[index].empid == empId) {
            employee[index] = Employee();
        }
        else {
            int curr = index;
            while(employee[curr].empid != empId) {
                curr = (curr + 1) % tablesize;
            }
            employee[curr] = Employee();
        }
    }

    void clearHT() {
        for(int i=0; i<tablesize; i++) {
            employee[i] = Employee();
        }
    }

    int searchHT(int empID) {
        int index = hashfun(empID);

        if(employee[index].empid == empID) {
            return employee[index].loc;
        }
        else {
            int curr = index;
            int i = 0;
            while(employee[curr].empid != empID && i < tablesize) {
                curr = (curr + 1) % tablesize;
                i++;
            }
            if(i >= tablesize) 
                return -1;
            else 
                return employee[curr].loc;
        }
    }

    void updateEntry(int empId, int newloc) {
        int index = hashfun(empId);
        if(employee[index].empid == empId) {
            employee[index].loc = newloc;
        }
        else {
            int curr = index;
            while(employee[curr].empid != empId) 
                curr = (curr + 1) % tablesize;
            employee[curr].loc = newloc;
        }
    }
};

class MyFile {
    char filename[20];
    HashTable table;
    fstream file;
    Employee E;

    public:
    MyFile() {
        cout << "Enter name of the file: " << endl;
        cin >> filename;
        file.open(filename, ios::out);
        if(file)
            cout << "File opened successfully" << endl;
        else 
            cout << "Error opening file" << endl;
        file.close();
    }

    void addRecord(string n, string a, int id) {
        file.open(filename, ios::app);
        if(file) {
            E.name = n;
            E.address = a;
            E.empid = id;
            E.loc = file.tellp();
            table.insertHT(E);
            file.write(reinterpret_cast<char*>(&E), sizeof(E));
        }
        else {
            cout << "Error" << endl;
        }
        file.close();
    }

    void readRecord(int empId) {
        file.open(filename, ios::in);
        if(!file)
            cout << "Error opening file" << endl;
        else {
            int lo = table.searchHT(empId);
            if(lo == -1)
                cout << "No such record exists" << endl;
            else {
                file.seekg(lo, ios::beg);
                file.read(reinterpret_cast<char*>(&E), sizeof(E));
                E.display();
            }
        }
        file.close();
    }

    void deleteRecord(int empId) {
        int loc = table.searchHT(empId);
        if(loc == -1)
            cout << "Does not exist" << endl;
        else {
            fstream temp;
            temp.open("temp.txt", ios::out);
            file.open(filename, ios::in);

            while(!file.eof()) {
                file.read(reinterpret_cast<char*>(&E), sizeof(E));
                if(E.empid == empId) {
                    cout << "Deleting Record" << endl;
                }
                else {
                   E.loc = temp.tellp();
                   table.updateEntry(E.empid, E.loc);
                   temp.write(reinterpret_cast<char*>(&E), sizeof(E));
                }
            }
            file.close(); temp.close();
            remove(filename);
            rename("temp.txt", filename);            
            table.deleteHT(empId);
            cout << "\nRecord deleted" << endl;
        }
    }
};



int main() {
    MyFile mf;
    int choice;
    string name, address;
    int empId;

    while (true) {
        cout << "\n--- Employee Management Menu ---\n";
        cout << "1. Add Employee Record\n";
        cout << "2. Read Employee Record\n";
        cout << "3. Delete Employee Record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Employee Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Address: ";
                getline(cin, address);
                cout << "Enter Employee ID: ";
                cin >> empId;
                mf.addRecord(name, address, empId);
                break;

            case 2:
                cout << "Enter Employee ID to read: ";
                cin >> empId;
                mf.readRecord(empId);
                break;

            case 3:
                cout << "Enter Employee ID to delete: ";
                cin >> empId;
        }
    }
}