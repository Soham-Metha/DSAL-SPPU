/*
 * Consider telephone book database of N clients. Make use of a hash table implementation
 * to quickly look up client‘s telephone number. Make use of two collision handling
 * techniques and compare them using number of comparisons required to find a set of
 * telephone numbers (Note: Use linear probing with replacement and without replace-ment)
 */

#include <iostream>
#define TABLE_SIZE 10
#define NAME(INDEX) data[INDEX].getName()
#define EXISTS(INDEX) data[INDEX].exists()
#define SET(INDEX,NM,PH) data[INDEX].setData(NM,PH)
using namespace std;

class UserData
{
    string name;
    long num;

  public:
    UserData() : name(""), num(0.0) {};

    UserData(string nm, long no) : name(nm), num(no) {};

    string getName()
    {
        return name;
    }

    bool exists()
    {
        return name == "";
    }

    void displayData()
    {
        cout << "\n" << name << "\t : " << num * 10 << "\n";
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
            index = (index + 1) % TABLE_SIZE;
        while (index != strt && EXISTS(index));

        if (EXISTS(index))
            return -1;

        cout << "Inserting " << nm << " at " << index << "\n";
        SET(index,nm,ph);

        return index;
    }

    int insertWithReplacement(string nm, long ph)
    {
        int index = hash_func(nm);
        UserData dataAtIndex = data[index];

        if (!EXISTS(index))
        {
            SET(index,nm,ph);
            return index;
        }

        int nextEmptyIndex = index;
        do
            nextEmptyIndex = (nextEmptyIndex + 1) % TABLE_SIZE;
        while (nextEmptyIndex != index && EXISTS(nextEmptyIndex));

        if (EXISTS(nextEmptyIndex))
            return -1;

        // check if the data at the index is in it's correct location
        // i.e. if the hash value of previous data is equal to the index
        // if so, insert the new data at the empty space
        // otherwise swap out the previos data
        cout << "\nInserting " << nm << " at ";
        if (hash_func(NAME(index)) == index)
        {
            SET(nextEmptyIndex,nm,ph);
            cout << nextEmptyIndex << "\n";
            return nextEmptyIndex;
        }

        data[nextEmptyIndex] = dataAtIndex;
        SET(index,nm,ph);
        cout << index << "\n";
        cout << "\nSwapped data at index to " << nextEmptyIndex << "\n";

        return index;
    }
    void lookup(string name)
    {
        int index = hash_func(name);
        int strt = index;

        do
            index = (index + 1) % TABLE_SIZE;
        while (index != strt && data[index].getName() != name);

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