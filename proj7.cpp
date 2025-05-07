#include <bits/stdc++.h>
using namespace std;
const int max = INT_MAX;

class Graph {
    int **adjMatrix;
    int vertexCount;
    int edgeCount;
    map<string, int> cities;
    map<int, string> inv_cities;


    void add(string city1,string city2, int dist) {
        adjMatrix[cities[city1]][cities[city2]] = dist;
        adjMatrix[cities[city2]][cities[city1]] = dist;
    }

    int minimum_key(int key[], bool mst[]) {
        int min = -1;
        int minimum = INT_MAX;
        for(int i=0; i<vertexCount; i++) {
            if(mst[i] == false && key[i] < minimum) {
                minimum = key[i];
                min = i;
            }
        }
        return min;     //return the index (i.e min) not the value
    }

    public:
    Graph() {
        //get the vertex and edge count from the user
        cout << "Enter the vertex count:" << endl;
        cin >> vertexCount;
        cout << "Enter the edge count:" << endl;
        cin >> edgeCount;
        
        adjMatrix = new int*[vertexCount];
        for(int i=0; i<vertexCount; i++) {
            adjMatrix[i] = new int[vertexCount];
            for(int j = 0; j<vertexCount; j++) {
                adjMatrix[i][j] = 0;
            }
        }

        //Now we have to populate the matix.
        cout << "Add cities in order: " << endl;
        for(int i=0; i<vertexCount; i++) {
            string city;
            cin >> city;
            cities.insert(pair<string, int>(city, i));
            inv_cities.insert(pair<int, string>(i, city));
        }
        
        cout << "Add the " << edgeCount << " edges:";
        for(int i=0; i<edgeCount; i++) {
            string u, v;
            int d;
            cout << "City 1:" << endl;
            cin >> u;
            cout << "City 2:" << endl;
            cin >> v;
            cout << "Enter the distance between them:" << endl;
            cin >> d;
            add(u, v, d);
        }        
    }
    void prims(Graph g) {
        int n = g.vertexCount;
        int parent[n]; 
        int key[n];
        bool mst[n];

        for(int i=0; i<vertexCount; i++) {
            key[i] = INT_MAX;
            mst[i] = false;
        }

        //we start with the first vertex
        key[0] = 0;
        parent[0] = -1;

        for(int count=0; count<n-1; count++) {
            int u = minimum_key(key, mst);
            mst[u] = true;

            for(int v=0; v < vertexCount; v++) {
                if(g.adjMatrix[u][v] != 0 && mst[v] != true && g.adjMatrix[u][v] < key[v]) {
                    key[v] = g.adjMatrix[u][v];
                    parent[v] = u;
                }
            }

        }

        cout << "MST of the given graph: " << endl;
        cout << "Edges \t Weight" << endl;  
        for(int i=1; i<vertexCount; i++) {
            cout << inv_cities[parent[i]] << " <-> " << inv_cities[i] << "\t" << g.adjMatrix[i][parent[i]];
        }
    }
};

int main() {
    Graph g;
    g.prims(g);
    return 0;
}
