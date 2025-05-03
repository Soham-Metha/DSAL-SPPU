#include <iostream>

using namespace std;

class Node
{
  public:
    int val;
    Node *left;
    Node *right;
    Node(int v) : val(v), left(NULL), right(NULL) {};
    Node(int v, Node *l, Node *r) : val(v), left(l), right(r) {};
};

class BinaryTree
{
  public:
    Node *root;
    int ln;
    Node *tmp[1000];

    BinaryTree(int arr[], int len);

    BinaryTree(const BinaryTree &bt);

    void preRecur(Node *n);

    void inRecur(Node *n);

    void postRecur(Node *n);

    int getHeight();

    int findHeight(Node *n, int v = 0);

    void findInt();

    void findExt();

    void swap(Node *n);

    BinaryTree operator=(BinaryTree bt);

    int printTree(Node *n, int v = 0);
};
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    BinaryTree bt(arr, sizeof(arr) / sizeof(arr[0]));
    cout << "\033[44m\033[2J";
    cout << "\n\n------------------------------------------------------------------------------------------------------"
            "\n\n";
    bt.printTree(bt.root);
    cout << "\n\n------------------------------------------------------------------------------------------------------"
            "\n";
    cout << "\n $\t\t 1. PreOrder Traversal \t: ";
    bt.preRecur(bt.root);
    cout << "\n $\t\t 2. InOrder Traversal \t: ";
    bt.inRecur(bt.root);
    cout << "\n $\t\t 3. PostOrder Traversal : ";
    bt.postRecur(bt.root);
    cout << "\n $\t\t 4. Height of Tree \t: " << bt.getHeight();
    cout << "\n $\t\t 5. Internal Nodes \t: ";
    bt.findInt();
    cout << "\n $\t\t 6. External Nodes \t: ";
    bt.findExt();
    cout << "\n\n------------------------------------------------------------------------------------------------------"
            "\n";
    BinaryTree btcpy = bt;
    btcpy.swap(btcpy.root);
    cout << "\n $\t\t 7. Copy created and content swapped!";
    cout << "\n\n------------------------------------------------------------------------------------------------------"
            "\n";
    cout << "\n $\t\t 8. Copy PreOrder Traversal \t: ";
    btcpy.preRecur(btcpy.root);
    cout << "\n $\t\t 9. Copy InOrder Traversal \t: ";
    btcpy.inRecur(btcpy.root);
    cout << "\n $\t\t10. Copy PostOrder Traversal \t: ";
    btcpy.postRecur(btcpy.root);
    delete btcpy.root;
    cout << "\n $\t\t11. Copy deleted\n";
    cout << "\n------------------------------------------------------------------------------------------------------"
            "\n\n";
    cout << "\033[0m";

    return 0;
}

/*

------------------------------------------------------------------------------------------------------

1
|-----> 2
        |-----> 4
                |-----> 8
                |-----> 9
        |-----> 5
                |-----> 10
                |-----> 11
|-----> 3
        |-----> 6
                |-----> 12
                |-----> 13
        |-----> 7
                |-----> 14
                |-----> 15


------------------------------------------------------------------------------------------------------

 $               1. PreOrder Traversal  : 1 2 4 8 9 5 10 11 3 6 12 13 7 14 15
 $               2. InOrder Traversal   : 8 4 9 2 10 5 11 1 12 6 13 3 14 7 15
 $               3. PostOrder Traversal : 8 9 4 10 11 5 2 12 13 6 14 15 7 3 1
 $               4. Height of Tree      : 3
 $               5. Internal Nodes      : 1 2 3 4 5 6 7
 $               6. External Nodes      : 8 9 10 11 12 13 14 15

------------------------------------------------------------------------------------------------------

 $               7. Copy created and content swapped!

------------------------------------------------------------------------------------------------------

 $               8. Copy PreOrder Traversal     : 1 3 7 15 14 6 13 12 2 5 11 10 4 9 8
 $               9. Copy InOrder Traversal      : 15 7 14 3 13 6 12 1 11 5 10 2 9 4 8
 $              10. Copy PostOrder Traversal    : 15 14 7 13 12 6 3 11 10 5 9 8 4 2 1
 $              11. Copy deleted

------------------------------------------------------------------------------------------------------

pict@pict-OptiPlex-SFF-Plus-7010:~/21448_DSAL/proj1/src$
 */

BinaryTree::BinaryTree(int arr[], int len)
{
    if (!arr[0])
        return;

    ln = len;

    for (int i = len - 1; i >= 0; i--)
    {
        if (2 * i + 2 >= len)
            tmp[i] = new Node(arr[i]);
        else
            tmp[i] = new Node(arr[i], tmp[2 * i + 1], tmp[2 * i + 2]);
    }

    root = tmp[0];
}

BinaryTree::BinaryTree(const BinaryTree &bt)
{
    if (!bt.tmp[0])
        return;

    ln = bt.ln;

    for (int i = ln - 1; i >= 0; i--)
    {
        if (2 * i + 2 >= ln)
            tmp[i] = new Node(bt.tmp[i]->val);
        else
            tmp[i] = new Node(bt.tmp[i]->val, tmp[2 * i + 1], tmp[2 * i + 2]);
    }

    root = tmp[0];
}

void BinaryTree::preRecur(Node *n)
{
    if (n == NULL)
        return;
    cout << n->val << " ";
    preRecur(n->left);
    preRecur(n->right);
}

void BinaryTree::inRecur(Node *n)
{
    if (n == NULL)
        return;
    inRecur(n->left);
    cout << n->val << " ";
    inRecur(n->right);
}

void BinaryTree::postRecur(Node *n)
{
    if (n == NULL)
        return;
    postRecur(n->left);
    postRecur(n->right);
    cout << n->val << " ";
}

int BinaryTree::getHeight()
{
    return findHeight(root) - 1;
}

int BinaryTree::findHeight(Node *n, int v = 0)
{
    if (n == NULL)
        return v;
    int a = findHeight(n->left, v + 1);
    int b = findHeight(n->right, v + 1);
    return max(a, b);
}

void BinaryTree::findInt()
{
    for (int i = 0; i < ln; i++)
    {
        Node *n = tmp[i];
        if ((n->left) || (n->right))
            cout << n->val << " ";
    }
}

void BinaryTree::findExt()
{
    for (int i = 0; i < ln; i++)
    {
        Node *n = tmp[i];
        if ((n->left) || (n->right))
            continue;
        cout << n->val << " ";
    }
}

void BinaryTree::swap(Node *n)
{
    if (n != NULL)
    {
        Node *tmp = n->left;
        n->left = n->right;
        n->right = tmp;
        swap(n->left);
        swap(n->right);
    }
}

BinaryTree BinaryTree::operator=(BinaryTree bt)
{
    return BinaryTree(bt);
}

int BinaryTree::printTree(Node *n, int v = 0)
{
    if (n != NULL)
    {
        int i;
        for (i = 1; i < v; i++)
            cout << "        ";
        for (int j = 0; j < (v - i + 1); j++)
            cout << "|-----> ";
        cout << n->val << "\n";
        int a = printTree(n->left, v + 1);
        int b = printTree(n->right, v + 1);
        return max(a, b);
    }
    return v;
}