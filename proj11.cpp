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
  public:
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
        cin >> name;
        cin >> roll;
        cin >> div;
        cin >> address;
    }

    friend class MyFile;
};

class MyFile
{
  public:
    char filename[20];
    FILE *file;
    Student S;

    MyFile()
    {
        cin >> filename;
    }

    void addRecord()
    {
        S.getData();
        file = fopen(filename, "a");
        fprintf(file, "%d %s %d %s\n", S.roll, S.name, S.div, S.address);
        fclose(file);
    }

    void displayRecords()
    {
        file = fopen(filename, "r");
        while (fscanf(file, "%d %s %d %s\n", &S.roll, S.name, &S.div, S.address) == 4) // '4' because we read 4 items
            S.display();
        fclose(file);
    }

    void deleteRecord(int roll)
    {
        file = fopen(filename, "r");
        FILE *temp = fopen("temp.txt", "w");
        bool found = false;
        while (fscanf(file, "%d %s %d %s\n", &S.roll, S.name, &S.div, S.address) == 4)
        {
            if (roll == S.roll)
            {
                cout << "Deleting: ";
                S.display();
                found = true;
            }
            else
                fprintf(temp, "%d %s %d %s\n", S.roll, S.name, S.div, S.address);
        }

        if (!found)
            cout << "No such data exists." << endl;

        fclose(file);
        fclose(temp);
        remove(filename);
        rename("temp.txt", filename);
    }
};

int main()
{
    MyFile File;
    int Choice;
    int R;
    do
    {
        // cout << "\n1: Add a record\n2: Display Database\n3: Delete a record\nEnter your choice: ";
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
/*
A much easier way to do this is to simply work with cin & cout.
we can redirect these using freopen
Syntax : 
    freopen("filename", "r", stdin); // similarly stdout
If you are too lazy to do even that,
use the '>' and'<' symbols when running the executable from cmdline
refer the build.sh file

*/