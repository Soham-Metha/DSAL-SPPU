#include <bits/stdc++.h>
#define SWAP(a, b)                                                                                                     \
    {                                                                                                                  \
        int tmp = a;                                                                                                   \
        a = b;                                                                                                         \
        b = tmp;                                                                                                       \
    }

#define LEFT 2 * i + 1
#define RIGHT 2 * i + 2

using namespace std;

class Node
{
    int val;
    Node *left, *right;

  public:
    Node()
    {
        val = 0;
        left = right = NULL;
    }

    Node(int d)
    {
        val = d;
        left = right = NULL;
    }

    Node(int v, Node *l, Node *r) : val(v), left(l), right(r) {};

    friend class Heap;
};

class Heap
{
    Node *root;
    int numNodes;

  public:
    Heap()
    {
        root = NULL;
        numNodes = 0;
    }

    void insert(int keys[], int n)
    {
        numNodes = n;
        Node *tmp[n];
        for (int i = n-1; i >= 0; i--)
            if (RIGHT >= n)
                tmp[i] = new Node(keys[i]);
            else
                tmp[i] = new Node(keys[i], tmp[LEFT], tmp[RIGHT]);

        root = tmp[0];
    }

    Node *getLastNode()
    {
        queue<Node *> que;
        que.push(root);
        Node *poppedNode = NULL;
        while (!que.empty())
        {
            poppedNode = que.front();
            que.pop();

            if (poppedNode->left)
                que.push(poppedNode->left);
            if (poppedNode->right)
                que.push(poppedNode->right);
        }
        return poppedNode;
    }

    Node *heapify(Node *node)
    {
        if (node == NULL)
            return NULL;

        node->left = heapify(node->left);
        node->right = heapify(node->right);

        if (node->left != NULL && node->left->val > node->val)
            SWAP(node->left->val, node->val);
        if (node->right != NULL && node->right->val > node->val)
            SWAP(node->right->val, node->val);

        return node;
    }

    Node *deleteNode(Node *node, int key)
    {
        if (node == NULL)
            return NULL;

        if (node->val == key)
        {
            delete node;
            return NULL;
        }

        node->left = deleteNode(node->left, key);
        node->right = deleteNode(node->right, key);

        return node;
    }

    void sort()
    {
        cout << "Descending Order: " << endl;
        for (int i = 0; i < numNodes; i++)
        {
            heapify(root);

            Node *lastNode = getLastNode();

            SWAP(root->val, lastNode->val);
            cout << lastNode->val << " ";
            deleteNode(root, lastNode->val);
        }
        cout << endl;
    }
};

int main()
{

    Heap heap;
    int keys[] = {87, 5, 34, 99, 44, 12, 68};
    int n = 7;
    heap.insert(keys, n);
    heap.sort();
    return 0;
}