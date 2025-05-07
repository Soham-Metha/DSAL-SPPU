#include <bits/stdc++.h>
using namespace std;

class Node
{
    int data;
    Node *left;
    Node *right;

  public:
    Node(int d)
    {
        data = d;
        left = right = NULL;
    }

    friend class BST;
};

class BST
{
  public:
    Node *root = NULL;
    void insert(Node **n, int v)
    {
        // think of (*n) as the nodePtr(left/right, whichever is passed)

        if ((*n) == NULL)
        {
            *n = new Node(v);
            return;
        }

        if (v <= (*n)->data)
            return insert(&((*n)->left), v);

        return insert(&((*n)->right), v);
    }

    int search(Node *n, int target, int v = 0)
    {
        if (!n)
            return 0;

        if (n->data == target)
            return v + 1;

        if (target < n->data)
            return search(n->left, target, v + 1);

        return search(n->right, target, v + 1);
    }

    void iinorder()
    {
        cout << "\nIterative Inorder Traversal : ";

        string output = "";
        stack<Node *> stk;
        Node *tmp = root;
        while (!stk.empty() || tmp != NULL)
        {
            while (tmp != NULL)
            {
                stk.push(tmp);
                tmp = tmp->left;
            }
            tmp = stk.top();
            stk.pop();
            output = output + to_string(tmp->data) + " ";
            tmp = tmp->right;
        }
        cout << output;
    }

    void ipreorder()
    {
        cout << "\nIterative Preorder Traversal : ";
        string output = "";
        stack<Node *> stk;
        stk.push(root);

        while (!stk.empty())
        {
            Node *n = stk.top();
            stk.pop();
            output = output + to_string(n->data) + " ";
            if (n->right)
                stk.push(n->right);
            if (n->left)
                stk.push(n->left);
        }
        cout << output;
    }

    void ipostorder()
    {
        cout << "\nIterative Postorder Traversal : ";
        string output = "";
        stack<Node *> stk;
        stk.push(root);

        while (!stk.empty())
        {
            Node *n = stk.top();
            stk.pop();
            output = to_string(n->data) + " " + output;
            if (n->left)
                stk.push(n->left);
            if (n->right)
                stk.push(n->right);
        }
        cout << output;
    }

    int printTreeAndFindHeight(Node *n, int v = 0)
    {
        if (n == NULL)
            return v;

        int i;

        for (i = 1; i < v; i++)
            cout << "        ";

        if (v > i - 1)
            cout << "|-----> ";

        cout << n->data << "\n";

        int a = printTreeAndFindHeight(n->left, v + 1);
        int b = printTreeAndFindHeight(n->right, v + 1);

        return max(a, b);
    }

    void swap(Node *n)
    {
        if (n == NULL)
            return;

        Node *tmp = n->left;
        n->left = n->right;
        n->right = tmp;

        swap(n->left);
        swap(n->right);
    }

    int getMinimum()
    {
        Node *curr;
        for (curr = root; curr->left != NULL; curr = curr->left)
        {
            // nothing
        }
        return curr->data;
    }

    int getMaximum()
    {

        Node *curr;
        for (curr = root; curr->right != NULL; curr = curr->right)
        {
            // nothing
        }
        return curr->data;
    }
};

int main()
{

    BST tree;
    int cnt;
    cin >> cnt;
    while (cnt > 0)
    {
        int tmp;
        cin >> tmp;
        tree.insert(&tree.root, tmp);
        cnt-=1;
    }
    cout << "Tree : " << endl;
    tree.printTreeAndFindHeight(tree.root);
    cout << endl;
    cout << "Search 15 : " << (tree.search(tree.root, 15) ? "true" : "false") << endl;
    cout << "Minimum : " << tree.getMinimum() << endl;
    cout << "Maximum : " << tree.getMaximum() << endl;
    tree.swap(tree.root);
    cout << "After swapping nodes: " << endl;
    tree.printTreeAndFindHeight(tree.root);
    return 0;
}