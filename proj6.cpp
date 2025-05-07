#include <bits/stdc++.h>
using namespace std;

class Node {
    string name;
    Node *next;
    Node *down;

    public: 
    Node(string str) {
        name = str;
        next = down = NULL;
    }

    friend class Graph;
}; 




class Graph {
    Node *head = NULL;

    void addNode(string nodeA, string nodeB) {
        add(nodeA, nodeB);
        add(nodeB, nodeA);
    }

    public:
    void add(string nodeA, string nodeB) {
        //If adjacency list is empty
        if(head == NULL) {
            Node *node1 = new Node(nodeA);
            Node *node2 = new Node(nodeB);
            node1 -> next = node2;
            head = node1;
            return;
        }
        
        Node *currNode = head;
        Node *prev = NULL;
        bool found = false;
        while(currNode != NULL) {
            //If nodeA is found
            if(currNode -> name == nodeA) {
                found = true;
                Node *currListNode = currNode;
                while(currListNode -> next != NULL) {
                    currListNode = currListNode -> next;
                }
                Node *node2 = new Node(nodeB);
                currListNode -> next = node2;
                break;
            }
            prev = currNode;
            currNode = currNode -> down;
        }
        //If nodeA is not found
        if(!found) {
            Node *node1 = new Node(nodeA);
            Node *node2 = new Node(nodeB);
            prev -> down = node1;
            node1 -> next = node2;
        }
    }

    void print() {
        Node *currArrayNode = head;
        while(currArrayNode != NULL) {
            Node *currListNode = currArrayNode;
            while(currListNode != NULL) {
                cout << currListNode -> name << " -> ";
                currListNode = currListNode -> next;
            }
            cout << " NULL ";
            currArrayNode = currArrayNode -> down;
            cout << endl;
        }
    }

    void bfs(string startNode) {
        vector<string> visited;
        queue<string> Queue;
        string poppedNode;
        visited.push_back(startNode);
        Queue.push(startNode);
        while(true) {
            if(!Queue.empty()) {
                poppedNode = Queue.front();
                Queue.pop();
                cout << poppedNode << " ";
            }
            else {
                cout << endl;
                break;
            }

            Node *currNode = head;
            bool found = false;
            while(currNode != NULL) {
                if(currNode -> name == poppedNode) {
                    found = true;
                    Node *currListNode = currNode -> next;
                    while(currListNode != NULL) {
                        if( find(visited.begin(), visited.end(), currListNode -> name) == visited.end() ) {
                            visited.push_back(currListNode -> name);
                            Queue.push(currListNode -> name);
                        }
                        currListNode = currListNode -> next;
                    }
                    break;
                }
                currNode = currNode -> down; 
            }
            if(!found) {
                cout << "Node is not present in the graph" << endl;
                return;
            }
        }
    }

    void dfs(string start) {
        vector<string> visited;
        stack<string> Stack;
        string poppedNode;
        visited.push_back(start);
        Stack.push(start);
        while(true) {
            
            if(!Stack.empty()) {
                poppedNode = Stack.top();
                Stack.pop();
                cout << poppedNode << " ";
            }
            else {
                cout << endl;
                break;
            }
            
            bool found = false;
            Node *currNode = head;
            while(currNode != NULL) {
                if(currNode -> name == poppedNode) {
                    found = true;
                    Node *currListNode = currNode -> next;
                    while(currListNode != NULL) {
                        if( find(visited.begin(), visited.end(), currListNode -> name) == visited.end() ){
                           visited.push_back(currListNode -> name);
                           Stack.push(currListNode -> name);  
                        }
                        currListNode = currListNode -> next;
                    }
                    break;
                }
                currNode -> down;
            }
            if(!found) {
                cout << "Node does not exist" << endl;
                break;
            }
        }
    }
};


int main() {
    Graph g;
    g.add("A", "B");
    g.add("A", "C");
    g.add("B", "C");
    g.add("C", "A");
    g.print();
    g.bfs("A");
    g.dfs("A");
    return 0;
}