#include <bits/stdc++.h>
using namespace std;

class Graph
{
  public:
    int nodeCnt;
    string values[10];
    map<string, bool> visited;
    map<string, list<string>> adjList;

    Graph(int v, string place[10])
    {
        nodeCnt = v;
        for (int i = 0; i < v; i++)
            values[i] = place[i];
    }
    void set_default()
    {
        for (int i = 0; i < nodeCnt; i++)
            visited[values[i]] = false;
    }
    void addEdge(string v, string w);
    void DFS(string v);
    void BFS(string v);
};

void Graph::addEdge(string a, string b)
{
    adjList[a].push_back(b);
    adjList[b].push_back(a);
}

void Graph::DFS(string start)
{
    visited[start] = true;
    cout << start << " ";

    list<string>::iterator i;
    for (i = adjList[start].begin(); i != adjList[start].end(); ++i)
        if (!visited[*i]){
            DFS(*i);
        }
}

void Graph::BFS(string s)
{
    list<string> queue;

    visited[s] = true;
    queue.push_back(s);

    list<string>::iterator i;

    while (!queue.empty())
    {
        s = queue.front();
        queue.pop_front();
        cout << s << " ";

        for (i = adjList[s].begin(); i != adjList[s].end(); ++i)
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
    }
}

int main()
{

    int nodeCnt;
    cin >> nodeCnt;

    string name;
    string name_list[nodeCnt];
    for (int i = 0; i < nodeCnt; i++)
    {
        cin >> name;
        name_list[i] = name;
    }
    Graph g(nodeCnt, name_list);
    char connected;
    for (int i = 0; i < nodeCnt; i++)
    {
        for (int j = 0; j < nodeCnt; j++)
        {
            cin >> connected;
            if (connected == 'y' || connected == 'Y')
            {
                g.addEdge(name_list[i], name_list[j]);
            }
        }
    }
    cin >> name;
    
    cout << "-------------------------------------\n";
    cout << "\nDFS :: ";
    g.set_default();
    g.DFS(name);
    cout << "\nBFS :: ";
    g.set_default();
    g.BFS(name);
    cout << "\n-------------------------------------\n";

    return 0;
}