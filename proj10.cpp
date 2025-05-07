#include <bits/stdc++.h>
using namespace std;

class Node {
    int val;
    Node *left, *right;

    public:
    Node() {
        val = 0;
        left = right = NULL;
    }

    Node(int d) {
        val = d;
        left = right = NULL;
    }

    friend class Heap;
};

class Heap {
    Node *root;
    int numNodes;

    public:
    Heap() {
        root = NULL;
        numNodes = 0;
    }

    void insert(int keys[], int n) {
        numNodes = n;
        Node *newNode = new Node(keys[0]);
        root = newNode;

        //bfs insert
        queue<Node*> que;
        int i = 0;
        que.push(root);
        while(i < n-1) {   //IMP: as i is incremented twice inside the loop

            Node *poppedNode = que.front();
            que.pop();

            //for the left child
            Node *leftNode = new Node(keys[++i]);
            poppedNode -> left = leftNode;
            que.push(poppedNode -> left);

            //for the right child
            Node *rightNode = new Node(keys[++i]);
            poppedNode -> right = rightNode;
            que.push(poppedNode -> right);
        }
    }

    Node* getLastNode() {
        queue<Node*> que;
        que.push(root);
        Node *poppedNode = NULL;
        while(!que.empty()) {
            poppedNode = que.front();
            que.pop();

            if(poppedNode -> left) que.push(poppedNode -> left);
            if(poppedNode -> right) que.push(poppedNode -> right);

        }
        return poppedNode;
    }
    
    Node* heapify(Node *node) {                     //bit tricky due to recursion
        if(node == NULL) {
            return NULL;
        }

        node -> left = heapify(node -> left);       // Heapify left subtree
        node -> right = heapify(node -> right);     // Heapify right subtree

        if(node -> left != NULL && node -> left -> val > node -> val) {
            int temp = node -> left -> val;
            node -> left -> val = node -> val;
            node -> val = temp;
        }
        if(node -> right != NULL && node -> right -> val > node -> val) {
            int temp = node -> right -> val;
            node -> right -> val = node -> val;
            node -> val = temp;
        }
        return node;
    }

    Node* deleteNode(Node *node, int key) {
        if(node == NULL )
            return NULL;
        
        if(node -> val == key) {
            delete node;
            return NULL;
        }

        node -> left = deleteNode(node -> left, key);
        node -> right = deleteNode(node -> right, key);
        
        return node;
    }

    void sort() {
        cout << "Descending Order: " << endl;
        for(int i=0; i<numNodes; i++) {
            heapify(root);

            Node *lastNode = getLastNode();

            //swap root node's value with the last node's value
            int temp = root -> val;
            root -> val = lastNode -> val;
            lastNode -> val = temp;

            //Print the value
            cout << lastNode -> val << " ";

            //delete the node
            deleteNode(root, lastNode -> val);
        }
        cout << endl;
    }
};


int main() {

    Heap heap;
    int keys[] = {87, 5, 34, 99, 44, 12, 68};
    int n = 7;
    heap.insert(keys, n);
    heap.sort();
    return 0;
}