#include <bits/stdc++.h>

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
        if (!left)
            return false;
        return !lthread;
    }
    bool hasRightChild()
    {
        if (!right)
            return false;
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
    void addLeftThread(Node *ptr)
    {
        this->lthread = true;
        this->left = ptr;
    }
    void addRightThread(Node *ptr)
    {
        this->rthread = true;
        this->right = ptr;
    }
};

class ThreadedBinarySearchTree
{
  public:
    Node *root;

    ThreadedBinarySearchTree()
    {
        root = NULL;
        int cnt;
        cin >> cnt;
        while (cnt > 0)
        {
            int tmp;
            cin >> tmp;
            insert(tmp);
            cnt -= 1;
        }
    }

    Node *leftmost(Node *ptr)
    {
        for (ptr; ptr->hasLeftChild(); ptr = ptr->left)
            ; // nothing
        return ptr;
    }

    Node *rightmost(Node *ptr)
    {
        for (ptr; ptr->hasRightChild(); ptr = ptr->right)
            ; // nothing
        return ptr;
    }
    Node *inorderSuccessor(Node *ptr)
    {
        if (ptr->rthread)
            return ptr->right;

        return leftmost(ptr->right);
    }

    Node *inorderPredecessor(Node *ptr)
    {
        if (ptr->lthread)
            return ptr->left;

        return rightmost(ptr->left);
    }

    void getParentOf(Node *root, int val, Node **parent, Node **child)
    {
        if (root == NULL)
        {
            *parent = *child = NULL;
            return;
        }

        if (root->left && *root->left == val)
        {
            *parent = root;
            *child = root->left;
            return;
        }
        if (root->right && *root->right == val)
        {
            *parent = root;
            *child = root->right;
            return;
        }

        if (val < root->value && root->hasLeftChild())
            return getParentOf(root->left, val, parent, child);
        if (val < root->value)
        {
            *parent = root;
            *child = NULL;
        }

        if (root->hasRightChild())
            return getParentOf(root->right, val, parent, child);

        *parent = root;
        *child = NULL;
    }

    void insert(int val)
    {
        if (root == NULL)
        {
            root = new Node(val);
            return;
        }

        Node *par, *tmp;
        getParentOf(root, val, &par, &tmp);

        if (tmp)
            assert(0 && "THE VALUE IS ALREADY PRESENT");

        if (val <= (par->value))
            return par->addLeft(val);

        par->addRight(val);
    }

    void inorder()
    {
        assert(root);

        for (Node *ptr = leftmost(root); ptr != NULL; ptr = inorderSuccessor(ptr))
            cout << ptr->value << " ";
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
            if (n->hasRightChild())
                stk.push(n->right);
            if (n->hasLeftChild())
                stk.push(n->left);
        }
        cout << output;
    }

    void delt(int dkey)
    {
        Node *par;
        Node *ptr;
        getParentOf(root, dkey, &par, &ptr);

        if (!par || !ptr)
            return;

        if (ptr->hasLeftChild() && ptr->hasRightChild())
            caseC(par, ptr);

        else if (ptr->hasLeftChild() || ptr->hasRightChild())
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
            par->addLeftThread(ptr->left);
        else
            par->addRightThread(ptr->right);
    }

    void caseB(Node *par, Node *ptr)
    {
        Node *child = ptr->hasLeftChild() ? ptr->left : ptr->right;

        if (par == NULL)
        {
            root = child;
            return;
        }
        else if (ptr == par->left)
            par->left = child;
        else
            par->right = child;

        Node *s = inorderSuccessor(ptr);
        Node *p = inorderPredecessor(ptr);

        if (ptr->hasLeftChild())
            p->right = s;
        else if (ptr->hasRightChild())
            s->left = p;
    }
    void caseC(Node *par, Node *ptr)
    {
        Node *parentOfLeftMost = ptr;

        Node *leftMost;
        for (leftMost = ptr->right; leftMost->left != NULL; leftMost = leftMost->left)
        {
            parentOfLeftMost = leftMost;
        }

        ptr->value = leftMost->value;

        if (leftMost->lthread && leftMost->rthread)
            caseA(parentOfLeftMost, leftMost);
        else
            caseB(parentOfLeftMost, leftMost);
    }

    void printTree(Node *n, string prefix = "       ")
    {
        assert(n);

        cout << prefix;

        if (n != root)
        {
            cout << "|-----> ";
            prefix += "        ";
        }

        cout << n->value << endl;

        if (n->lthread)
            cout << prefix << "|-(T)-> " << (n ? to_string(n->value) : "NULL") << endl;
        else
            printTree(n->left, prefix);

        if (n->rthread)
            cout << prefix << "|-(T)-> " << (n ? to_string(n->value) : "NULL") << endl;
        else
            printTree(n->right, prefix);
    }
};

int main()
{
    ThreadedBinarySearchTree tbst;
    tbst.printTree(tbst.root);
    cout << " \n";
    cout << " \n";
    tbst.inorder();
    cout << endl;
    // tbst.delt(3);
    tbst.preorder();
    cout << endl;
    return 0;
}
