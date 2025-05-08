#include <bits/stdc++.h>
using namespace std;

class Graph
{
  public:
    int nodeCnt;
    string values[10];
    map<string, bool> visited;
    map<string, list<string>> adjMatrix;

    Graph(int v, string place[10])
    {
        nodeCnt = v;
        for (int i = 0; i < v; i++)
            values[i] = place[i];
    }
    void addEdge(string v, string w);
    void set_default()
    {
        for (int i = 0; i < nodeCnt; i++)
        {
            visited[values[i]] = false;
        }
    }
    void DFS(string v);
    void BFS(string v);
};

void Graph::addEdge(string v, string w)
{
    adjMatrix[v].push_back(w);
}

void Graph::DFS(string v)
{
    visited[v] = true;
    cout << v << " ";

    list<string>::iterator i;
    for (i = adjMatrix[v].begin(); i != adjMatrix[v].end(); ++i)
        if (!visited[*i])
            DFS(*i);
}

void Graph::BFS(string s)
{
    visited[s] = false;

    list<string> queue;

    visited[s] = true;
    queue.push_back(s);

    list<string>::iterator i;

    while (!queue.empty())
    {
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        for (i = adjMatrix[s].begin(); i != adjMatrix[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}

int main()
{

    int n;
    cout << "\nEnter the number of elements in the graph - ";
    cin >> n;
    int mat[n][n];
    string name;
    string name_list[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the name of vertice " << i + 1 << " - ";
        cin >> name;
        name_list[i] = name;
    }
    Graph g(n, name_list);
    char connected;
    cout << "\nY-YES & N-NO\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << "\n" << name_list[i] << " connected " << name_list[j] << "--->";
            cin >> connected;
            if (connected == 'y' || connected == 'Y')
            {
                g.addEdge(name_list[i], name_list[j]);
            }
            else
            {
                continue;
            }
        }
        cout << "\n--------------------------------\n";
    }
    char loop = 'y';
    while (loop == 'y' || loop == 'Y')
    {
        cout << "-------------------------------------\n";
        cout << "Enter place :: ";
        cin >> name;
        cout << "\nDFS :: ";
        g.set_default();
        g.DFS(name);
        cout << "\nBFS :: ";
        g.set_default();
        g.BFS(name);
        cout << "\nYou want to continue (y/n) :: ";
        cin >> loop;
    }

    return 0;
}