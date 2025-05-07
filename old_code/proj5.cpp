#include <assert.h>
#include <string.h>
#include <iostream>
#define TABLE_SIZE 5

#define HASH_FUNC(n, out)     \
    {                         \
        out = n % TABLE_SIZE; \
    }

using namespace std;

template <typename int, typename string>
class Node
{
public:
    int key;
    string value;
    Node *next;
    Node(int k, string v, Node *n) : key(k), value(v), next(n) {};
};

template <typename int, typename string>
class HashTable
{
public:
    Node<int, string> *table[TABLE_SIZE];

    HashTable()
    {
        for (size_t i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    void insert(int key, string val)
    {
        int index;
        HASH_FUNC(key, index);
        Node<int, string> *node = new Node(key, val, table[index]);
        table[index] = node;
    }

    void search(int key)
    {
        int index;
        HASH_FUNC(key, index);
        Node<int, string> *tmp = table[index];

        cout << "\n----------------------------SEARCHING--------------------------\n";
        while (tmp)
        {
            if (tmp->key == key)
            {
                cout << "\nFound " << tmp->key << " : " << tmp->value << "\n";
                return;
            }
            tmp = tmp->next;
        }
        cout << "\n\nKeyError : " << key << endl;
        exit(1);
    }
    void remove(int key)
    {
        int index;
        HASH_FUNC(key, index);

        Node<int, string> *tmp = table[index];

        cout << "\n----------------------------DELETION---------------------------\n";
        if (tmp->key == key)
        {
            table[index] = tmp->next;
            disp(index, false);
            return;
        }

        while (tmp->next)
        {
            if (tmp->next->key == key)
            {
                tmp->next = tmp->next->next;
                disp(index, false);
                return;
            }
            tmp = tmp->next;
        }

        cout << "\n\nKeyError : " << key << endl;
        exit(1);
    }

    void disp(int i = 0, bool recursive = true)
    {
        if (i == TABLE_SIZE)
            return;

        cout << "\n[     " << i << "     ]";
        Node<int, string> *tmp = table[i];
        while (tmp)
        {
            cout << " |━| " << tmp->key << " ━━━ " << tmp->value;
            tmp = tmp->next;
        }
        cout << endl;

        if (recursive)
            disp(i + 1);
    }
};

int main(int argc, char **argv)
{
    HashTable<int, string> tab;
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