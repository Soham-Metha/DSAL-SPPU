#include <bits/stdc++.h>
using namespace std;

class Node
{
    int key;
    string value;
    Node *left, *right;

  public:
    Node()
    {
        left = right = NULL;
    }
    friend class AVL;
};

class AVL
{
    Node *root = NULL;

    int getHeight(Node *node)
    {
        if (node == NULL)
            return 0;

        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalanceFactor(Node *node)
    {
        if (node == NULL)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    Node *L_Rotation(Node *node)
    {
        Node *newRoot = node->left;
        newRoot->right = node;
        node->left = NULL;

        return newRoot;
    }

    Node *R_Rotation(Node *node)
    {
        Node *newRoot = node->right;
        newRoot->left = node;
        node->right = NULL;

        return newRoot;
    }

    Node *RL_Rotation(Node *node)
    {
        node->right = L_Rotation(node->right);
        return R_Rotation(node);
    }

    Node *LR_Rotation(Node *node)
    {
        node->left = R_Rotation(node->left);
        return L_Rotation(node);
    }

    Node *balance(Node *node)
    {
        if (getBalanceFactor(node) == 2)
        {
            if (getBalanceFactor(node->left) < 0)
                node->left = R_Rotation(node->left);
            node = L_Rotation(node);
            return node;
        }

        if (getBalanceFactor(node) == -2)
            if (getBalanceFactor(node->right) < 0)
                node = R_Rotation(node);
            else
                node = RL_Rotation(node);

        return node;
    }

    Node *insertNodeAndBalance(Node *node, int key, string value)
    {
        if (node == NULL)
        {
            Node *newNode = new Node();
            newNode->key = key;
            newNode->value = value;
            return newNode;
        }

        if (key < node->key)
            node->left = insertNodeAndBalance(node->left, key, value);
        else if (key > node->key)
            node->right = insertNodeAndBalance(node->right, key, value);
        else
        {
            node->value = value;
            return node;
        }
        return balance(node);
    }

    Node *getMin(Node *root)
    {
        while (root->left != NULL)
            root = root->left;
        return root;
    }

    Node *deleteNodeAndBalance(Node *root, int key)
    {
        if (root == NULL)
        {
            cout << "Key does not exist" << endl;
            return NULL;
        }

        if (key < root->key)
        {
            root->left = deleteNodeAndBalance(root->left, key);
            return balance(root);
        }
        if (key > root->key)
        {
            root->right = deleteNodeAndBalance(root->right, key);
            return balance(root);
        }

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }

        if (root->left == NULL)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }

        Node *succ = getMin(root->right);
        root->key = succ->key;
        root->right = deleteNodeAndBalance(root->right, succ->key);
        return root;
    }

    void inorder(Node *root)
    {
        if (root == NULL)
            return;

        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }

  public:
    void insert(int key, string value)
    {
        root = insertNodeAndBalance(root, key, value);
    }

    void deleteNode(int key)
    {
        root = deleteNodeAndBalance(root, key);
    }

    Node *search(int key, int &compCount)
    {
        Node *curr = root;
        while (curr != NULL)
        {
            compCount++;
            if (key > curr->key)
                curr = curr->right;
            else if (key < curr->key)
                curr = curr->left;
            else
                return curr;
        }
        return NULL;
    }

    void bfs()
    {
        cout << "bfs: ";
        queue<Node *> que;
        que.push(root);

        while (!que.empty())
        {
            Node *temp = que.front();
            que.pop();
            cout << temp->key << " : " << temp->value << " ";
            if (temp->left)
                que.push(temp->left);
            if (temp->right)
                que.push(temp->right);
        }
        cout << endl;
    }

    void iinorder()
    {
        inorder(root);
        cout << endl;
    }
};

int main()
{
    AVL tree;

    tree.insert(100, "1");
    tree.insert(50, "2");
    tree.insert(150, "3");
    tree.insert(25, "4");
    tree.insert(75, "5");
    tree.insert(125, "6");

    tree.bfs();
    cout << "Inorder Traversal: ";
    tree.iinorder();

    tree.insert(175, "7");
    tree.insert(65, "8");
    tree.insert(85, "9");

    tree.deleteNode(100);

    tree.bfs();
    tree.iinorder();

    return 0;
}
