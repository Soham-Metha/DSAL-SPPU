#include <bits/stdc++.h>
using namespace std;

class Node
{
    int data;
    Node *left, *right;

  public:
    Node(int d)
    {
        data = d;
        left = right = NULL;
    }

    friend class BT;
};

class BT
{

  public:
    Node *root;
    BT()
    {
        root = buildTree();
    }

    Node *buildTree()
    {
        // cout << "\nData (-1:NULL) : ";
        int d;
        cin >> d;

        if (d == -1)
        {
            return nullptr;
        }

        Node *node = new Node(d);
        // cout << "Enter the value of node to the left of " << d << ":";
        node->left = buildTree();
        // cout << "Enter the value of node to the right of " << d << ":";
        node->right = buildTree();

        return node;
    }

    void preorder(Node *node)
    {
        if (node == NULL)
            return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(Node *node)
    {
        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
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

    int countLeaf(Node *root)
    {
        if (root == NULL)
            return 0;

        if (root->left == NULL && root->right == NULL)
            return 1;

        return countLeaf(root->left) + countLeaf(root->right);
    }

    void deleteTree(Node *root)
    {
        if (root == NULL)
            return;

        deleteTree(root->left);
        deleteTree(root->right);

        cout << "Deleting Node: " << root->data;
        delete root;
    }

    Node *cloneTree(Node *root)
    {
        if (root == NULL)
            return NULL;

        Node *newRoot = new Node(root->data);
        newRoot->left = cloneTree(root->left);
        newRoot->right = cloneTree(root->right);

        return newRoot;
    }

    BT &operator=(const BT &other)
    {
        assert(this != &other);
        deleteTree(this->root);
        this->root = cloneTree(other.root);
        return *this;
    }
};

int main()
{
    BT tree;
    cout << "Tree 1\n Inorder : ";
    tree.inorder(tree.root);
    cout << "\n Preorder : ";
    tree.preorder(tree.root);
    tree.ipreorder();
    tree.ipostorder();
    tree.iinorder();
    int tmp;
    cout << endl;
    tmp = tree.printTreeAndFindHeight(tree.root);

    BT tree2 = tree;
    cout << "Tree 2\n Inorder : ";
    tree2.inorder(tree2.root);
    cout << "\n Preorder : ";
    tree2.preorder(tree2.root);
    tree2.ipreorder();
    tree2.ipostorder();
    tree2.iinorder();
    cout << endl;
    tmp = tree2.printTreeAndFindHeight(tree2.root);

    return 0;
}
