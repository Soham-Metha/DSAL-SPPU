#include <bits/stdc++.h>
using namespace std;

class Node {
    string key, value;
    Node *next;
    friend class Dictionary;

    public:
    Node(string k, string v) {
        key = k;
        value = v;
        next = NULL;
    }
};

class Dictionary {

    Node **table;
    int tablesize;

    int hashfun(string value) {
        int sum = 0;
        for(char ch : value)
            sum += (int)ch;
        return sum % tablesize;
    }

    void insertLL(string key, string value) {
        int hashAdd = hashfun(key);
        if(table[hashAdd] == NULL) {
            Node *newNode = new Node(key, value);
            table[hashAdd] = newNode;
        }
        else {
            insertLL(table[hashAdd], key, value);
        }
    }

    void insertLL(Node *hashAdd, string key, string value) {
        Node *curr = hashAdd;
        Node *newNode = new Node(key, value);
        while(curr -> next != NULL) {
            curr = curr -> next;
        }
        curr -> next = newNode;
    }

    Node* findLL(Node *head, string key) {
        Node *t = head;
        while(t -> next != NULL) {
            if(t -> key == key) {
                return t;
            }
            t = t -> next;
        }
        if(t -> key == key) //For last element
            return t;
        else
            return NULL; 
    }

    //to print each bucket (each slot of nodes) in the hash table
    void printLL(Node *head) {
        Node *t = head;
        while(t != NULL) {
            cout << t -> key << " " << t -> value << ",";
            t = t -> next; 
        }
    }

    void deleteLL(int index, Node *head, string key) {
        if(head == NULL) 
            cout << "Node does not exist" << endl;
        else {
            Node *temp = head, *prev = NULL;
            
            if(head -> key == key) {
                Node *nextNode = head -> next;
                delete head;
                table[index] = nextNode;
                cout << "Node deleted successfully" << endl;
            }
            else {
                temp = head;
                prev = NULL;
                
                while(temp != NULL) {
                    if(temp -> key == key) {
                        prev -> next = temp -> next;
                        delete temp;
                        cout << "Node deleted successfully" << endl;
                        break;
                    }
                    prev = temp;
                    temp = temp -> next;
                }
            }
        }
    }

    public:
    Dictionary(int n) {
        tablesize = n;
        table = new Node*[tablesize];
        for(int i=0; i<tablesize; i++) {
            table[i] = NULL;    
        }
    }

    void insert(string key, string value) {
        int index = hashfun(key);           //index a.k.a hashAddress
        if(table[index] == NULL) {
            Node *newNode = new Node(key, value);
            table[index] = newNode;
        }
        else {
            insertLL(table[index], key, value);
        }
    }

    void print() {
        for(int i=0; i<tablesize; i++) {
            cout << " ";
            printLL(table[i]);
            cout << endl;
        }
    }

    void search(string key) {
        int hashAdd = hashfun(key);
        Node *targetNode = findLL(table[hashAdd], key);
        if(targetNode == NULL) {
            cout << "Node does not exist." << endl;
        }
        else {
            cout << "Node: " << targetNode->key << " " << targetNode->value << endl;
        }
    }

    void del(string key) {
        int hashAdd = hashfun(key);
        deleteLL(hashAdd, table[hashAdd], key);
    }
};


int main() {
    

    return 0;
}