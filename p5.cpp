#include <assert.h>
#include <string.h>
#include <iostream>
#define TABLE_SIZE 5

#define HASH_FUNC(n, out)     \
    {                         \
        out = n % TABLE_SIZE; \
    }

using namespace std;

template <typename T, typename U>
class Node
{
public:
    T key;
    U value;
    Node *next;
    Node(T k, U v, Node *n) : key(k), value(v), next(n) {};
};

template <typename T, typename U>
class HashTable
{
public:
    Node<T, U> *table[TABLE_SIZE];

    HashTable()
    {
        for (size_t i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    void insert(T key, U val)
    {
        int index;
        HASH_FUNC(key, index);
        Node<T, U> *node = new Node(key, val, table[index]);
        table[index] = node;
    }

    void search(T key)
    {
        int index;
        HASH_FUNC(key, index);
        Node<T, U> *tmp = table[index];

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
    void remove(T key)
    {
        int index;
        HASH_FUNC(key, index);

        Node<T, U> *tmp = table[index];

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
        Node<T, U> *tmp = table[i];
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