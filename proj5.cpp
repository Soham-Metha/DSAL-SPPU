#include <assert.h>
#include <iostream>
#include <string.h>
#define TABLE_SIZE 5

using namespace std;

class Node
{
  public:
    int key;
    string value;
    Node *next;
    Node(int k, string v, Node *n) : key(k), value(v), next(n) {};
    void display()
    {
        cout << " |━| " << key << " ━━━ " << value;
    }
};

class HashTable
{
  public:
    Node *table[TABLE_SIZE];

    HashTable()
    {
        for (size_t i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    void insert(int key, string val)
    {
        int index = key % TABLE_SIZE;
        Node *node = new Node(key, val, table[index]);
        table[index] = node;
    }

    void search(int key)
    {
        int index = key % TABLE_SIZE;

        cout << "\n----------------------------SEARCHING--------------------------\n";
        for (Node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
            if (tmp->key == key)
            {
                cout << "\nFound " << tmp->key << " : " << tmp->value << "\n";
                return;
            }

        cout << "\n\nKeyError : " << key << endl;
        exit(1);
    }
    void remove(int key)
    {
        int index = key % TABLE_SIZE;

        Node *tmp = table[index];

        cout << "\n----------------------------DELETION---------------------------\n";
        if (tmp->key == key)
        {
            table[index] = tmp->next;
            table[index]->display();
            return;
        }
        for (; tmp->next; tmp = tmp->next)
            if (tmp->next->key == key)
            {
                tmp->next = tmp->next->next;
                table[index]->display();
                return;
            }

        cout << "\n\nKeyError : " << key << endl;
        exit(1);
    }

    void disp(int i = 0)
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << "\n[     " << i << "     ]";

            for (Node *tmp = table[i]; tmp; tmp = tmp->next)
                tmp->display();

            cout << endl;
        }
    }
};

int main(int argc, char **argv)
{
    HashTable tab;
    tab.insert(11, "eleven");
    tab.insert(12, "twelve");
    tab.insert(13, "thirteen");
    tab.insert(14, "fourteen");
    tab.insert(15, "fifteen");
    tab.insert(16, "sixteen");
    tab.insert(21, "twenty one");
    tab.insert(26, "twenty six");

    tab.disp();
    tab.search(11);
    // tab.search(25);
    tab.remove(26);
    tab.remove(11);
    // tab.remove(26);
    cout << "\n";
    return 0;
}