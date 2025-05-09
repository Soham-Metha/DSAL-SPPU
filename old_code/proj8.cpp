
#include <bits/stdc++.h>
using namespace std;
#define MAX 20

class Node
{
    int key;
    Node *left, *right;
    friend class OBST;

  public:
    Node()
    {
        key = 0;
        left = NULL;
        right = NULL;
    }
    Node(int k)
    {
        key = k;
        left = NULL;
        right = NULL;
    }
};

class OBST
{
    int keys[MAX]; // Array to store the actual keys
    int keyCount;

    double WEIGHT[MAX][MAX]; // Weight of subree spanning from [i] to [j]
    double COST[MAX][MAX];   // The minimum cost for keys between [i+1] and [j].
    int ROOT[MAX][MAX];      // ROOT key that gives min cost for keys between [i+1] and [j].
                             // ROOT key is index of 'keys' array

    double unsuccessfulProbablity[MAX];
    double successfulProbablity[MAX];

  public:
    Node *root;

    OBST()
    {
        root = NULL;
    }

    void Calculate_W_C_R()
    {
        double x;
        double min;
        int i, j, possibleNewMid, gap, mid;

        for (i = 0; i <= keyCount; i++)
        {
            WEIGHT[i][i] =
                unsuccessfulProbablity[i]; // the weight from 'i' to 'i' itself is just the unsuccessful probablity

            for (j = i + 1; j <= keyCount; j++)
                WEIGHT[i][j] =         // weight from i to j
                    WEIGHT[i][j - 1] + // weight from i to j-1, NOTE: Base case 'j=i+1' is handled in previous statement
                    successfulProbablity[j] +  // chances that node 'j' is the value we were searching for
                    unsuccessfulProbablity[j]; // chances that the value we were searching for lies between 'i' and 'j'
        }

        for (i = 0; i <= keyCount; i++)
            COST[i][i] = WEIGHT[i][i]; // the cost from 'i' to 'i' itself is just the weight

        // Calc cost for every possible combination of nodes possible
        for (i = 0; i <= keyCount - 1; i++)
        {
            j = i + 1;
            COST[i][j] =
                COST[i][i] + COST[j][j] +
                WEIGHT[i][j]; // Cost of a subtree with two nodes is the sum of the nodes' weights and the root weight
            ROOT[i][j] = j;
        }

        for (gap = 2; gap <= keyCount; gap++)
            for (i = 0; i <= keyCount - gap; i++)
            {
                j = i + gap;
                mid = ROOT[i][j - 1]; // Mid is the root node connecting i and j

                min = COST[i][mid - 1] + COST[mid][j];

                for (possibleNewMid = mid + 1; possibleNewMid <= ROOT[i + 1][j]; possibleNewMid++)
                {
                    x = COST[i][possibleNewMid - 1] + COST[possibleNewMid][j];
                    if (x < min)
                    {
                        mid = possibleNewMid;
                        min = x;
                    }
                }
                COST[i][j] = WEIGHT[i][j] + min; // Cost of the subtree is the sum of its weight and the minimum cost of
                                                 // its left and right subtrees
                ROOT[i][j] = mid;                // Root of the subtree is the node that gives the minimum cost
            }
    }

    Node *Construct_OBST(int lb, int ub)
    {
        Node *p;

        if (lb == ub)
        {
            p = NULL;
            return p;
        }
        p = new Node();
        p->key = keys[ROOT[lb][ub]]; // Root node key is determined by the optimal root index stored in ROOT[i][j]
        p->left = Construct_OBST(lb, ROOT[lb][ub] - 1); // Construct left subtree recursively
        p->right = Construct_OBST(ROOT[lb][ub], ub);    // Construct right subtree recursively
        return p;
    }

    void printTree(Node *n, string prefix = "\t", int depth = 0, bool isLast = true)
    {
        if (!n)
            return;

        cout << prefix;
        if (n != root)
        {
            cout << (isLast ? "┗━━━━━━━┓ " : "┣━━━━━━━┓ ");
            prefix += isLast ? "\t" : "┃\t";
        }

        cout << n->key << endl;

        printTree(n->left, prefix, depth + 1, false);

        printTree(n->right, prefix, depth + 1);
    }

    void obst()
    {
        Calculate_W_C_R();
        int i, j;

        cout << "\nThe weight matrix WEIGHT:\n";
        for (i = 0; i <= keyCount; i++)
        {
            for (j = 0; j < i; j++)
                cout << "X" << "\t";
            for (j = i; j <= keyCount; j++)
                cout << WEIGHT[i][j] << "\t";
            cout << "\n";
        }

        cout << "\nThe cost matrix COST:\n";
        for (i = 0; i <= keyCount; i++)
        {
            for (j = 0; j < i; j++)
                cout << "X" << "\t";
            for (j = i; j <= keyCount; j++)
                cout << COST[i][j] << "\t";
            cout << "\n";
        }

        cout << ("\nThe root matrix ROOT:\n");
        for (i = 0; i <= keyCount; i++)
        {
            for (j = 0; j <= i; j++)
                cout << "X" << "\t";
            for (j = i + 1; j <= keyCount; j++)
                cout << ROOT[i][j] << "\t";
            cout << "\n";
        }

        cout << "\n COST = " << COST[0][keyCount] << endl << "WEIGHT = " << WEIGHT[0][keyCount] <<"\n"<< endl;

        root = Construct_OBST(0, keyCount);
    }

    void inp()
    {
        // cout << "Enter number of keys:";
        cin >> keyCount;
        // cout << " Enter keys" << endl;
        for (int i = 1; i <= keyCount; i++)
        {

            cin >> keys[i];
            // cout << " probability = ";
            cin >> successfulProbablity[i];
        }
        for (int i = 0; i <= keyCount; i++)
        {
            // cout << "unsuccessfulProbablity " << i << "= ";
            cin >> unsuccessfulProbablity[i];
        }
    }
};

int main()
{
    int k;
    freopen("p8_i.txt", "r", stdin);

    OBST tree;

    while (true)
    {
        // cout << "1.Construct tree\n2.Display tree\n3.Exit\n";
        cin >> k;
        switch (k)
        {
        case 1:
            tree.inp();  // Input the number of keys, their access probabilities, and dummy key access probabilities
            tree.obst(); // Calculate the optimal binary search tree and construct it
            break;
        case 2:
            tree.printTree(tree.root);
            break;
        default:
            exit(0);
        }
    }
    return 0;
}