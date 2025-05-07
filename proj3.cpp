#include <iomanip>
#include <iostream>
#include <stack>
#define REPEAT_STR(s, lb, ub)                                                                                          \
    {                                                                                                                  \
        for (lb; lb < ub; lb++)                                                                                        \
            cout << s;                                                                                                 \
    }
#define REPEAT_ST(s, n)                                                                                                \
    {                                                                                                                  \
        for (int i = 0; i < n; i++)                                                                                    \
            cout << s;                                                                                                 \
    }

using namespace std;

class Node
{
  public:
    Node *left, *right;
    int value;

    bool lthread;
    bool rthread;
    Node(int val) : value(val), lthread(true), rthread(true), left(NULL), right(NULL) {};
    Node(int val, Node *l, Node *r) : value(val), lthread(true), rthread(true), left(l), right(r) {};

    bool operator==(int val)
    {
        return value == val;
    }
    bool hasLeftChild()
    {
        return !lthread;
    }
    bool hasrightChild()
    {
        return !rthread;
    }
    void addLeft(int val)
    {
        this->lthread = false;
        this->left = new Node(val, this->left, this);
    }
    void addRight(int val)
    {
        this->rthread = false;
        this->right = new Node(val, this, this->right);
    }
};

class ThreadedBinarySearchTree
{
  public:
    Node *root;

    ThreadedBinarySearchTree()
    {
        root = NULL;
    }

    Node *getParentOf(Node *root, int val)
    {
        if (root == NULL)
            return root;

        if (root->left && *root->left == val)
            return root;

        if (root->right && *root->right == val)
            return root;

        if (val < root->value && root->hasLeftChild())
            return getParentOf(root->left, val);

        if (val < root->value)
            return root;

        if (root->hasrightChild())
            return getParentOf(root->right, val);

        return root;
    }

    void insert(int val)
    {
        if (root == NULL)
        {
            root = new Node(val);
            return;
        }

        Node *par = getParentOf(root, val);

        if (val <= (par->value))
        {
            return par->addLeft(val);
        }
        par->addRight(val);
    }

    Node *inorderSuccessor(Node *ptr)
    {
        if (ptr->rthread == true)
            return ptr->right;

        return leftmost(ptr->right);
    }

    Node *inorderPredecessor(Node *ptr)
    {
        if (ptr->lthread == true)
            return ptr->left;

        for (ptr = ptr->left; ptr->hasrightChild(); ptr = ptr->right)
            ; // nothing

        return ptr; // rightmost of ptr->left
    }

    Node *leftmost(Node *ptr)
    {
        for (; ptr->hasLeftChild(); ptr = ptr->left)
            ; // nothing
        return ptr;
    }

    void inorder()
    {
        if (root == NULL)
        {
            return;
        }

        for (Node *ptr = leftmost(root); ptr != NULL; ptr = inorderSuccessor(ptr))
        {
            cout << ptr->value << " ";
        }
    }

    void preorder()
    {
        string output = "";
        stack<Node *> stk;
        stk.push(root);

        while (!stk.empty())
        {
            Node *n = stk.top();
            stk.pop();
            output = output + to_string(n->value) + " ";
            if (n->right && !n->rthread)
                stk.push(n->right);
            if (n->left && !n->lthread)
                stk.push(n->left);
        }
        cout << output;
    }

    void displayThread(Node *n, string prefix)
    {
        cout << prefix << "|-----> " << (n ? to_string(n->value) : "NULL") << endl;
    }

    void printTree(Node *n, string prefix = "        ", int depth = 0)
    {
        if (!n)
            return;

        cout << prefix;

        if (n != root)
        {
            cout << "|-----> ";
            prefix += "        ";
        }

        cout << n->value << endl;

        if (n->lthread)
            displayThread(n->left, prefix);
        else
            printTree(n->left, prefix, depth + 1);

        if (n->rthread)
            displayThread(n->right, prefix);
        else
            printTree(n->right, prefix, depth + 1);
    }

    void delt(int dkey)
    {
        Node *par = getParentOf(root, dkey);
        Node *ptr = NULL;

        if (!par)
            return;

        if (par->left && *par->left == dkey)
            ptr = par->left;
        else if (par->right && *par->right == dkey)
            ptr = par->right;
        else
            return;

        if (ptr->hasLeftChild() && ptr->hasrightChild())
            caseC(par, ptr);

        else if (ptr->hasLeftChild() || ptr->hasrightChild())
            caseB(par, ptr);

        else
            caseA(par, ptr);

        free(ptr);
    }

    void caseA(Node *par, Node *ptr)
    {
        if (par == NULL)
        {
            root = NULL;
            return;
        }

        if (ptr == par->left)
        {
            par->lthread = true;
            par->left = ptr->left;
            return;
        }
        par->rthread = true;
        par->right = ptr->right;
    }

    void caseB(Node *par, Node *ptr)
    {
        Node *child = (ptr->hasLeftChild()) ? ptr->left : ptr->right;

        if (par == NULL)
            root = child;
        else if (ptr == par->left)
            par->left = child;
        else
            par->right = child;

        Node *s = inorderSuccessor(ptr);
        Node *p = inorderPredecessor(ptr);

        if (ptr->hasLeftChild())
            p->right = s;

        else if (ptr->hasrightChild())
            s->left = p;
    }
    void caseC(Node *par, Node *ptr)
    {
        Node *parentOfLeftMost = ptr;

        Node *leftMost = ptr->right;
        while (leftMost->left != NULL)
        {
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
