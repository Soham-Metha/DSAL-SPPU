#include <iostream>
#include <iomanip>
#include <stack>
#define REPEAT_STR(s, lb, ub)   \
    {                           \
        for (lb; lb < ub; lb++) \
            cout << s;          \
    }
#define REPEAT_ST(s, n)             \
    {                               \
        for (int i = 0; i < n; i++) \
            cout << s;              \
    }

using namespace std;

class Node {
public:
    Node *left, *right;
    int value;

    bool lthread;
    bool rthread;
    Node(int val)
        : value(val)
        , lthread(true)
        , rthread(true)
        , left(NULL)
        , right(NULL) { };
    Node(int val, Node* l, Node* r)
        : value(val)
        , lthread(true)
        , rthread(true)
        , left(l)
        , right(r) { };
};

class ThreadedBinarySearchTree {
public:
    Node* root;

    ThreadedBinarySearchTree()
    {
        root = NULL;
    }

    Node* getParentOf(Node* ptr, int val)
    {
        if (ptr == NULL)
            return ptr;

        if (ptr->left && ptr->left->value == val)
            return ptr;

        if (ptr->right && ptr->right->value == val)
            return ptr;

        if (val < ptr->value && ptr->lthread == false)
            return getParentOf(ptr->left, val);

        else if (val < ptr->value)
            return ptr;

        if (ptr->rthread == false)
            return getParentOf(ptr->right, val);
        else
            return ptr;
    }

    void insert(int val)
    {
        if (root == NULL) {
            root = new Node(val);
            return;
        }

        Node* par = getParentOf(root, val);

        if (val <= (par->value)) {
            par->lthread = false;
            par->left = new Node(val, par->left, par);
            return;
        }
        par->rthread = false;
        par->right = new Node(val, par, par->right);
    }

    Node* inorderSuccessor(Node* ptr)
    {
        if (ptr->rthread == true)
            return ptr->right;

        return leftmost(ptr->right);
    }
    Node* inorderPredecessor(Node* ptr)
    {
        if (ptr->lthread == true)
            return ptr->left;

        ptr = ptr->left;
        while (ptr->rthread == false)
            ptr = ptr->right;
        return ptr;
    }

    Node* leftmost(Node* ptr)
    {
        while (ptr->lthread == false)
            ptr = ptr->left;
        return ptr;
    }

    void inorder()
    {
        if (root == NULL) {
            printf("Tree is empty");
            return;
        }

        Node* ptr = leftmost(root);

        while (ptr != NULL) {
            printf("%d ", ptr->value);
            ptr = inorderSuccessor(ptr);
        }
    }

    void preorder()
    {
        string output = "";
        stack<Node*> stk;
        stk.push(root);

        while (!stk.empty()) {
            Node* n = stk.top();
            stk.pop();
            output = output + to_string(n->value) + " ";
            if (n->right && !n->rthread)
                stk.push(n->right);
            if (n->left && !n->lthread)
                stk.push(n->left);
        }
        cout << output;
    }

    void displayThread(Node* n, string prefix, bool isLast = true)
    {
        cout << prefix
             << "\033[37m"
             << (isLast ? "┗━━━━━━ " : "┣━━━━━━ ")
             << (n ? to_string(n->value) : "NULL")
             << "\033[31m"
             << endl;
    }

    void printTree(Node* n, string prefix = "\t", int depth = 0, bool isLast = true)
    {
        if (!n)
            return;

        cout << prefix;
        if (n != root) {
            cout << (isLast ? "┗━━━━━━━┓ " : "┣━━━━━━━┓ ");
            prefix += isLast ? "\t" : "┃\t";
            prefix += "\033[37m";
        }

        cout << n->value << endl;

        if (n->lthread)
            displayThread(n->left, prefix, false);
        else
            printTree(n->left, prefix, depth + 1, n->rthread && n->lthread);

        if (n->rthread)
            displayThread(n->right, prefix);
        else
            printTree(n->right, prefix, depth + 1);
    }

    void delt(int dkey)
    {
        Node* par = getParentOf(root, dkey);
        Node* ptr = NULL;

        if (!par)
            return;

        if (par->left && (par->left->value == dkey))
            ptr = par->left;

        else if (par->right && (par->right->value == dkey))
            ptr = par->right;

        else
            return;

        if (ptr->lthread == false && ptr->rthread == false)
            caseC(par, ptr);

        else if (ptr->lthread == false || ptr->rthread == false)
            caseB(par, ptr);

        else
            caseA(par, ptr);

        free(ptr);
    }

    void caseA(Node* par, Node* ptr)
    {
        if (par == NULL) {
            root = NULL;
            return;
        }

        if (ptr == par->left) {
            par->lthread = true;
            par->left = ptr->left;
            return;
        }
        par->rthread = true;
        par->right = ptr->right;
    }

    void caseB(Node* par, Node* ptr)
    {
        Node* child = (ptr->lthread == false) ? ptr->left : ptr->right;

        if (par == NULL)
            root = child;
        else if (ptr == par->left)
            par->left = child;
        else
            par->right = child;

        Node* s = inorderSuccessor(ptr);
        Node* p = inorderPredecessor(ptr);

        if (ptr->lthread == false)
            p->right = s;

        else if (ptr->rthread == false)
            s->left = p;
    }
    void caseC(Node* par, Node* ptr)
    {
        Node* parentOfLeftMost = ptr;

        Node* leftMost = ptr->right;
        while (leftMost->left != NULL) {
            parentOfLeftMost = leftMost;
            leftMost = leftMost->left;
        }

        ptr->value = leftMost->value;

        if (leftMost->lthread && leftMost->rthread)
            caseA(parentOfLeftMost, leftMost);
        else
            caseB(parentOfLeftMost, leftMost);
    }
};

int main()
{
    ThreadedBinarySearchTree tbst;
    cout << "\033[40;37m\033[2J";
    tbst.insert(10);
    tbst.insert(5);
    tbst.insert(15);
    tbst.insert(13);
    tbst.insert(17);
    tbst.insert(3);
    tbst.insert(7);
    tbst.insert(11);
    tbst.insert(6);
    tbst.insert(16);
    tbst.insert(14);
    tbst.insert(18);
    tbst.insert(2);
    tbst.insert(9);
    tbst.printTree(tbst.root);
    cout << " \n";
    cout << " \n";
    tbst.inorder();
    cout << endl;
    // tbst.delt(3);
    tbst.preorder();
    cout << "\033[0m";
    cout << endl;
    return 0;
}
