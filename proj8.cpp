#include<iostream>
#include<limits>
#include<queue>
using namespace std;

#define WEIGHT(i,j) table[i][j].weight
#define COST(i,j) table[i][j].weight
#define ROOT(i,j) table[i][j].weight

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
    int *successfullProbablity;     // Successful probability p1, p2, p3, ..., pn
    int *unsuccessfullProbablity;     // Unsuccessful probability q0, q1, q2, q3, ..., qn
    int n;      // No. of nodes in binary tree

    TNode **table;

    public:
    OBST(){
        cout<<"\nEnter no. of nodes in tree: ";
        cin>>n;
        
        keys = new int[n];
        successfullProbablity = new int[n];
        unsuccessfullProbablity = new int[n+1];

        cout<<"\nEnter Keys:\n";
        for(int i=0; i<n; i++){
            cout<<"Key K"<<i<<": ";
            cin>>keys[i];
        }

        cout<<"\nEnter Successful Probabilities:\n";
        for(int i=0; i<n; i++){
            cout<<"P"<<i<<": ";
            cin>>successfullProbablity[i];
        }

        cout<<"\nEnter Unsuccessful Probabilities:\n";
        for(int i=0; i<=n; i++){
            cout<<"Q"<<i<<": ";
            cin>>unsuccessfullProbablity[i];
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
            WEIGHT(i,i) = unsuccessfullProbablity[i];
            COST(i,i) = 0;
            ROOT(i,i) = 0;
        }


        for(int gap = 1; gap<=n; gap++){
            int i = 0;
            int j = i+gap;

            while(j<=n){
                WEIGHT(i,j) = WEIGHT(i,j-1) + successfullProbablity[j-1] + unsuccessfullProbablity[j];

                // Calculating Cost: C[i, j] = min(C[i, k-1] + C[k, j]) + W[i, j]
                // Where i<k<=j
                // Also storing root
                for(int k=i+1; k<=j; k++){
                    int c = COST(i,k-1) + COST(k,j);
                    if(COST(i,j)>c){
                        ROOT(i,j) = k;
                        COST(i,j) = c;
                    }
                }
                COST(i,j)+=WEIGHT(i,j);
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

        Node *newnode = new Node(keys[(ROOT(i,j))-1], i, j);
        root  = newnode;

        queue<Node*> q;
        q.push(newnode);

        while(!q.empty()){
            newnode = q.front();
            q.pop();

            i = newnode->i;
            j = newnode->j;

            k = ROOT(i,j);

            if(k-1 != i){
                Node* temp = new Node(keys[ROOT(i,k-1)-1], i, k-1);
                newnode->left = temp;
                q.push(temp);
            }else newnode->left = NULL;

            if(k!=j){
                Node* temp = new Node(keys[ROOT(k,j)-1], k, j);
                newnode->right = temp;
                q.push(temp);
            }else newnode->right = NULL;
        }
        cout<<"\nTree Built\n";
        printBT("", root, false);
        cout<<"\nCost of OBST: "<<COST(0,n);

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

};

int main(){
    OBST t;
    return 0;
}