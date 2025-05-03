#include<iostream>
#include<limits>
#include<queue>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    int i;
    int j;
    Node(int d, int i, int j){
        data = d;
        left = nullptr;
        right = nullptr;
        this->i = i;
        this->j = j;
    }
};

class TNode{
    public:
    int root;
    int cost;
    int weight;

    TNode(){
        cost = weight = root = numeric_limits<int>::max();
    }
};

class OBST{
    Node *root; // Root of binary Tree
    int *keys;  // Keys k1, k2, k3, ..., kn
    int *p;     // Successful probability p1, p2, p3, ..., pn
    int *q;     // Unsuccessful probability q0, q1, q2, q3, ..., qn
    int n;      // No. of nodes in binary tree

    TNode **table;


    public:
    OBST(){
        cout<<"\nEnter no. of nodes in tree: ";
        cin>>n;
        
        keys = new int[n];
        p = new int[n];
        q = new int[n+1];

        cout<<"\nEnter Keys:\n";
        for(int i=0; i<n; i++){
            cout<<"Key K"<<i<<": ";
            cin>>keys[i];
        }

        cout<<"\nEnter Successful Probabilities:\n";
        for(int i=0; i<n; i++){
            cout<<"P"<<i<<": ";
            cin>>p[i];
        }

        cout<<"\nEnter Unsuccessful Probabilities:\n";
        for(int i=0; i<=n; i++){
            cout<<"Q"<<i<<": ";
            cin>>q[i];
        }

        root = nullptr;

        table = new TNode*[n+1];
        for(int i=0; i<=n; i++)
            table[i] = new TNode[n+1];

        createTree();
    }

    void initTable(){

        // Initializing digonal elements
        for(int i=0; i<=n; i++){
            table[i][i].weight = q[i];
            table[i][i].cost = 0;
            table[i][i].root = 0;
        }


        for(int gap = 1; gap<=n; gap++){
            int i = 0;
            int j = i+gap;

            while(j<=n){
                // Calculating Weights: W[i, j] = W[i, j-1] + p[j-1] + q[j]
                table[i][j].weight = table[i][j-1].weight + p[j-1] + q[j];

                // Calculating Cost: C[i, j] = min(C[i, k-1] + C[k, j]) + W[i, j]
                // Where i<k<=j
                // Also storing root
                for(int k=i+1; k<=j; k++){
                    int c = table[i][k-1].cost + table[k][j].cost;
                    if(table[i][j].cost>c){
                        table[i][j].root = k;
                        table[i][j].cost = c;
                    }
                }
                table[i][j].cost+=table[i][j].weight;
                i++;
                j++;
            }
        }

    }

    void createTree(){
        initTable();

        int i = 0;
        int j = n;
        int k = 0;

        Node *newnode = new Node(keys[(table[i][j].root)-1], i, j);
        root  = newnode;

        queue<Node*> q;
        q.push(newnode);

        while(!q.empty()){
            newnode = q.front();
            q.pop();

            i = newnode->i;
            j = newnode->j;

            k = table[i][j].root;

            if(k-1 != i){
                Node* temp = new Node(keys[table[i][k-1].root-1], i, k-1);
                newnode->left = temp;
                q.push(temp);
            }else newnode->left = NULL;

            if(k!=j){
                Node* temp = new Node(keys[table[k][j].root-1], k, j);
                newnode->right = temp;
                q.push(temp);
            }else newnode->right = NULL;
        }
        cout<<"\nTree Built\n";
        printBT("", root, false);
        cout<<"\nCost of OBST: "<<table[0][n].cost;

    }

    void printBT(const string& prefix, const Node* root, bool isLeft)
    {
        if( root != nullptr )
        {
            cout << prefix;

            cout << (isLeft ? "├──" : "└──" );

            cout << root->data << std::endl;

            printBT( prefix + (isLeft ? "│   " : "    "), root->left, true);
            printBT( prefix + (isLeft ? "│   " : "    "), root->right, false);
        }
    }

    ~OBST() {
        delete[] keys;
        delete[] p;
        delete[] q;
        for (int i = 0; i <= n; i++)
            delete[] table[i];
        delete[] table;
        deleteTree(root); // Recursively deletes the tree
    }
    
    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

};

int main(){
    OBST t;
    return 0;
}