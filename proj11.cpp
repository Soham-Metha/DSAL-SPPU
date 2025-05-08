/*

Department maintains a student information file. The file contains roll number, name, division and address.
Allow user to add, delete information of student. Display information of particular student.
If record of student does not exist an appropriate message is displayed.
If it is, then the system displays the student details. Use Sequential File to maintain the data.
*/

#include <fstream>
#include <iostream>
using namespace std;

class Student
{
    int roll, div;
    char name[256], address[256];

    Student()
    {
        roll = div = 0;
    }

    void display()
    {
        cout << name << " " << roll << " " << div << " " << address << endl;
    }

    void getData()
    {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter div: ";
        cin >> div;
        cout << "Enter address: ";
        cin >> address;
    }

    friend class MyFile;
};

class MyFile
{
    char filename[20];
    FILE* file;
    Student S;

  public:
    MyFile()
    {
        cin >> filename;
    }

    void addRecord()
    {
        file = fopen(filename,"a");
        S.getData();
        fprintf(file,"%d %s %d %s",S.roll,S.name,S.div,S.address);
        fclose(file);
    }

    void displayRecords()
    {
        fopen(filename, "r");
        fscanf(file,"%d %s %d %s", &S.roll, &S.name, &S.div, &S.address);
        while (file)
        {
            S.display();
            fscanf(file,"%d %s %d %s", &S.roll, &S.name, &S.div, &S.address);
        }
        fclose(file);
    }
/*
    void deleteRecord(int roll)
    {
        file.open(filename, ios::in);
        fstream temp;
        temp.open("temp", ios::out);
        bool found = false;
        file.read(reinterpret_cast<char *>(&S), sizeof(S));
        while (!file.eof())
        {
            if (roll == S.roll)
            {
                cout << "Deleting: ";
                S.display();
                found = true;
            }
            else
                temp.write(reinterpret_cast<char *>(&S), sizeof(S));
            file.read(reinterpret_cast<char *>(&S), sizeof(S));
        }

        if (!found)
            cout << "No such data exists." << endl;

        file.close();
        temp.close();
        remove(filename);
        rename("temp", filename);
    }*/
};

int main()
{
    MyFile File;
    int Choice;
    int R;
    do
    {
        cout << "\n1: Add a record\n2: Display Database\n3: Delete a record\nEnter your choice: ";
        cin >> Choice;

        switch (Choice)
        {
        case 1:
            File.addRecord();
            break;

        case 2:
            File.displayRecords();
            break;

        case 3:
            cout << "Enter the record you want to delete: ";
            cin >> R;
            File.deleteRecord(R);
            break;
        }
    } while (Choice < 4);
    cout << endl;
    return 0;
}
