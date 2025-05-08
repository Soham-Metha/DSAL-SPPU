/*
 * ROLL NUMBER 48, (48%5)+1 = 4, Problem statement 4 :
 * Consider telephone book database of N clients. Make use of a hash table implementation
 * to quickly look up client‘s telephone number. Make use of two collision handling
 * techniques and compare them using number of comparisons required to find a set of
 * telephone numbers (Note: Use linear probing with replacement and without replace-ment)
 */

#include <iostream>
#define TABLE_SIZE 10
using namespace std;

class UserData
{
    string name;
    long num;

public:
    UserData() : name(""),
                 num(0.0) {};

    UserData(string nm, long no) : name(nm),
                                   num(no) {};

    string getName()
    {
        return name;
    }

    void displayData()
    {
        cout << "\n"
             << name
             << "\t : "
             << num * 10
             << "\n";
    }

    void setData(string nm, long no)
    {
        name = nm;
        num = no;
    }
};

int hash_func(string s)
{
    int tmp = 0;
    for (char c : s)
        tmp += c;
    return tmp % TABLE_SIZE;
}

class HT
{
    UserData data[TABLE_SIZE];

public:
    int insertWithoutReplacement(string nm, long ph)
    {
        int index = hash_func(nm);
        int strt = index;

        do
        {
            index = (index + 1) % TABLE_SIZE;
        } while (
            index != strt &&
            data[index].getName() != "");

        if (data[index].getName() != "")
        {
            return -1;
        }

        cout << "Inserting " << nm
             << " at " << index
             << "\n";
        data[index].setData(nm, ph);

        return index;
    }

    int insertWithReplacement(string nm, long ph)
    {
        int index = hash_func(nm);
        UserData dataAtIndex = data[index];

        // If there isn't any existing data at index
        // then insert data and exit function
        if (dataAtIndex.getName() == "")
        {
            data[index].setData(nm, ph);
            return index;
        }

        // Find the next empty entry in the series
        int nextEmptyIndex = index;
        do
        {
            nextEmptyIndex = (nextEmptyIndex + 1) % TABLE_SIZE;

        } while (
            nextEmptyIndex != index &&
            data[nextEmptyIndex].getName() != "");

        // if the entire table is filled, then exit
        if (data[nextEmptyIndex].getName() != "")
            return -1;

        // check if the data at the index is in it's correct location
        // i.e. if the hash value of previous data is equal to the index
        // if so, insert the new data at the empty space
        // otherwise swap out the previos data
        cout << "\nInserting " << nm << " at ";
        if (hash_func(dataAtIndex.getName()) == index)
        {
            data[nextEmptyIndex].setData(nm, ph);
            cout << nextEmptyIndex << "\n";
            return nextEmptyIndex;
        }
        data[nextEmptyIndex] = dataAtIndex;
        data[index].setData(nm, ph);
        cout << index << "\n";
        cout << "\nSwapped data at index to " << nextEmptyIndex << "\n";

        return index;
    }
    void lookup(string name)
    {
        int index = hash_func(name);
        int strt = index;

        do
        {
            index = (index + 1) % TABLE_SIZE;
        } while (
            index != strt &&
            data[index].getName() != name);

        cout << "\nAT\t :  " << index;
        if (data[index].getName() == name)
            data[index].displayData();
    }
};

int main()
{
    HT table;
    table.insertWithoutReplacement("Soham", 9);
    table.insertWithoutReplacement("Ab", 1);
    table.insertWithoutReplacement("Ba", 2);
    table.lookup("Soham");
    table.lookup("Ab");
    table.lookup("Ba");
    table.insertWithReplacement("Ae", 3);
    table.lookup("Ae");
    table.lookup("Soham");
    table.lookup("Ab");
    table.lookup("Ba");
    cout << "\n";
    return 0;
}

/*

State after inserting first 3 :

    4: Ab
    5: Soham
    6: Ba                   // actual position +2

State after insert with replacement :

    4: Ab
    5: Soham
    6: Ae
    7: Ba                   // actual position +3

*/