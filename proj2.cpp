#include <iostream>
#include <stack>
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

class BinarySearchTree
{
public:
	Node *root;

	BinarySearchTree(int arr[], int len)
	{
		if (arr == NULL)
			return;

		root = NULL;

		for (int i = 0; i < len; i++)
			insertNode(&root, arr[i]);
	}

	void insertNode(Node **n, int v)
	{
		if ((*n) == NULL)
		{
			*n = new Node(v);
			return;
		}

		if (v <= (*n)->val)
			return insertNode(&((*n)->left), v);

		return insertNode(&((*n)->right), v);
	}

	int printTree(Node *n, int v = 0)
	{
		if (n == NULL)
			return v;

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

	int getMax(Node *n)
	{
		if (n == NULL)
			return -1;
		if (n->right == NULL)
			return n->val;

		return getMax(n->right);
	}

	int getMin(Node *n)
	{
		if (n == NULL)
			return -1;
		if (n->left == NULL)
			return n->val;

		return getMin(n->left);
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

	void search(Node *n, int target, int v = 0)
	{
		if (!n){
			cout << "TARGET NOT FOUND";
		}
		if (n->val == target)
		{
			cout << target << " FOUND AFTER " << v+1 << " COMPARISONS, DEPTH IS " << v << "\n";
		}

		if (target < n->val )
		{
			search(n->left, target, v + 1);
			return;
		}
		else if (n->right)
		search(n->right, target, v + 1);
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
			output = output + to_string(n->val) + " ";
			if (n->right)
				stk.push(n->right);
			if (n->left)
				stk.push(n->left);
		}
		cout << output;
	}

	void inorder()
	{
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
			output = output + to_string(tmp->val) + " ";
			tmp = tmp->right;
		}
		cout << output;
	}
	void postorder()
	{
		string output = "";
		stack<Node *> stk;
		stk.push(root);

		while (!stk.empty())
		{
			Node *n = stk.top();
			stk.pop();
			output = to_string(n->val) + " " + output;
			if (n->left)
				stk.push(n->left);
			if (n->right)
				stk.push(n->right);
		}
		cout << output;
	}
};

int main()
{
	int arr[100];
	int n;
	cout << "\033[44m\033[2J";
	cout << "How many nodes do you want to insert? : ";
	cin >> n;
	cout << "Enter data :";
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
	}
	int lenPath;
	BinarySearchTree bst(arr, n);
	cout << "\n\n------------------------------------------------------------------------------------------------------\n\n";
	lenPath = bst.printTree(bst.root);
	cout << "\n\n------------------------------------------------------------------------------------------------------\n";

	cout << "\n $\t\t 1. Max value \t\t\t: " << bst.getMax(bst.root);
	cout << "\n $\t\t 2. Min value \t\t\t: " << bst.getMin(bst.root);
	cout << "\n $\t\t 3. Length of longest path \t: " << lenPath;
	cout << "\n $\t\t 4. Preorder \t\t\t: ";
	bst.preorder();
	cout << "\n $\t\t 5. Inorder \t\t\t: ";
	bst.inorder();
	cout << "\n $\t\t 6. Postorder \t\t\t: ";
	bst.postorder();
	cout << "\n\n------------------------------------------------------------------------------------------------------\n\n";
	cout << "\n $\t\t 7. Tree after swap \t\t: \n\n";
	bst.swap(bst.root);
	bst.printTree(bst.root);
	cout << "\n\n------------------------------------------------------------------------------------------------------\n";
	cout << "\n $\t\t 8. Preorder \t\t\t: ";
	bst.preorder();
	cout << "\n $\t\t 9. Inorder \t\t\t: ";
	bst.inorder();
	cout << "\n $\t\t10. Postorder \t\t\t: ";
	bst.postorder();
	cout << "\n\n------------------------------------------------------------------------------------------------------\n";
	int m;
	cout << "Enter search target :";
	cin >> m;
	bst.swap(bst.root);
	bst.search(bst.root,m,0);
	cout << "\033[0m";

	return 0;
}
