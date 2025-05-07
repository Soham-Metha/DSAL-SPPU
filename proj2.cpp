#include <bits/stdc++.h>
using namespace std;

class Node {
    int data;
    Node *left;
    Node *right;

    public:
    Node(int d) {
        data = d;
        left = right = NULL;
    }

    Node() {
        data = 0;
        left = right = NULL;
    }
    friend class BST;
};

class BST {
    Node *root = NULL;

    public:
    void insert(int d) {
        if(root == NULL) {
            root = new Node(d);
        }
        else {
            //find the insert location
            Node *curr = root, *prev;
            while(curr != NULL) {
                if(d > curr -> data) {
                    prev = curr;
                    curr = curr -> right;
                }
                else if(d < curr -> data) {
                    prev = curr; 
                    curr = curr -> left;
                }
                else {
                    cout << d << " is already present in the BST";
                    return;
                }
            }

            Node *newNode = new Node(d);
            if(d > prev -> data) {
                prev -> right = newNode;
            }
            else {
                prev -> left = newNode;
            }
        }
    }

    bool search(int d) {
        if(root == NULL) {
            return false;
        }
        Node *curr = root;

        while(curr != NULL) {
            if(d > curr -> data) {
                curr = curr -> right;
            }
            else if(d < curr -> data) {
                curr = curr -> left;
            }
            else {
                return true;
            }
        }
        return false;
        }

        void preorder() {
            cout << "Preorder Traversal: "; 
            stack<Node*> st1;
            Node *temp = root;
            while(!st1.empty() || temp != NULL) {
                if(temp != NULL) {
                    st1.push(temp);
                    cout << temp -> data << " ";
                    temp = temp -> left;
                }
                else {
                    temp = st1.top(); st1.pop();
                    temp = temp -> right;
                }
            }
        }

        void inorder() {
            cout << "Inorder Traversal: "; 
            stack<Node*> st1;
            Node *temp = root;
            while(!st1.empty() || temp != NULL) {
                if(temp != NULL) {
                    st1.push(temp);
                    temp = temp -> left;
                }
                else {
                    temp = st1.top(); st1.pop();
                    cout << temp -> data << " ";
                    temp = temp -> right;
                }
            }
        }

        void postorder() {
            stack<Node*> st1, st2;
            st1.push(root);
            while(!st1.empty()) {
                Node *temp = st1.top(); st1.pop();
                st2.push(temp);

                if(temp -> left) st1.push(temp -> left);
                if(temp -> right) st1.push(temp -> right);
            }

            while(!st2.empty()) {
                cout << st2.top() -> data << " ";
                st2.pop();                                                                  
            }
        }

        Node* swapNodesRoot() {
            return swapNodes(root);
        }

        Node* swapNodes(Node *node) {
            if(node == NULL) return NULL;
            if(node -> left && node -> right) {
                int temp = node -> left -> data;
                node -> left -> data = node -> right -> data;
                node -> right -> data = temp;
            }
            swapNodes(node -> left);
            swapNodes(node -> right);
        }

        int getMinimum() {
            Node *curr = root;

            while(curr -> left != NULL) {
                curr = curr -> left;
            }
            return curr -> data;
        }

        int getMaximum() {
            Node *curr = root;

            while(curr -> right != NULL) {
                curr = curr -> right;
            }
            return curr -> data;
        }

        int height(Node *node) {
            if(node == NULL) return 0;

            int lh = height(node -> left);
            int rh = height(node -> right);
            return max(lh,rh) + 1;
        }
    };

int main() {
    
    BST tree;
    tree.insert(4);
    tree.insert(8);
    tree.insert(2);
    tree.insert(9);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    cout << "Tree : " << endl;
    tree.inorder();
    cout << endl;
    cout << "Search 15 : " << (tree.search(15) ? "true" : "false") << endl;
    cout << "Minimum : " << tree.getMinimum() << endl;
    cout << "Maximum : " << tree.getMaximum() << endl;
    tree.swapNodesRoot();
    cout << "After swapping nodes: " << endl;
    tree.inorder();
    return 0;
}