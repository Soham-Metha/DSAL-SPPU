#include <bits/stdc++.h>
using namespace std;

class Node {
    int data;
    Node *left, *right;
    bool lt,rt;

    Node(int val) {
        data = val;
        left = right = NULL;
        lt = rt = false;
    }

    friend class TBST;
};

class TBST {
    Node *root; //for the actual root of the tree
    Node *head; //for the dummy node

    public:
    TBST() {
        head = new Node(-1);
        root = NULL;
        head -> left = head;
        head -> right = head;
        head -> lt = true;
        head -> rt = false; //remember
    }

    Node* insertBST(Node *node, int val) {
        if(node == NULL) {
            Node *newNode = new Node(val);
            return newNode;
        }

        if(node -> data < val) {
            node -> right = insertBST(node -> right, val);
        }
        else if(node -> data > val) {
            node -> left = insertBST(node -> left, val );
        }

        return node;
    }

    void insert(int val) {
        root = insertBST(root, val);
    }   

    void threadify(Node *curr, Node* &prev) {            //v.v.v.v.v.v. important
        //base case
        if(curr == NULL) return;

        threadify(curr -> left, prev);

        if(curr -> left == NULL) {
            curr -> left = prev;
            curr -> lt = true;
        }

        if(prev -> right == NULL) {
            prev -> right = curr;
            prev -> rt = true;
        }

        prev = curr;
        threadify(curr -> right, prev);
    }

    void createThread() {
        Node *prev = head;
        threadify(root, prev);
        prev -> right = head;
        prev -> rt = true;
        head -> left = root;
        head -> lt = false;
    }

    void inorder() {
        if(root == NULL) {
            cout << "Tree empty" << endl;
            return;
        }

        Node *curr = root;
        while(curr -> lt == false) {
            curr = curr -> left; 
        }

        while(curr != head) {
            cout << curr -> data << " ";

            if(curr -> rt == true) {
                curr = curr -> right;
            }
            else {
                curr = curr -> right;
                while(curr -> lt == false) {
                    curr = curr -> left;
                }
            }
        }
        
    }

    
};

int main() {
    TBST tree;

    // Insert some nodes
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Create threads after building the BST
    tree.createThread();

    // Inorder traversal using threads
    cout << "Inorder traversal: ";
    tree.inorder();

    return 0;
}
