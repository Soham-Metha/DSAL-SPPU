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
    set_default();
    visited[start] = true;
    cout << start << " ";

    list<string>::iterator i;
    for (i = adjList[start].begin(); i != adjList[start].end(); i++)
        if (!visited[*i]){
            cout << "start:";
            DFS(*i);
            cout << "back:";
        }
}

void Graph::BFS(string s)
{
    set_default();

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
        cout << "Enter the name of vertice " << i + 1 << " - ";
        cin >> name;
        name_list[i] = name;
    }
    Graph g(nodeCnt, name_list);
    char connected;
    cout << "\nY-YES & N-NO\n";
    for (int i = 0; i < nodeCnt; i++)
    {
        for (int j = 0; j < nodeCnt; j++)
        {
            cout << "\n" << name_list[i] << " connected " << name_list[j] << "--->";
            cin >> connected;
            if (connected == 'y' || connected == 'Y')
            {
                g.addEdge(name_list[i], name_list[j]);
            }
        }
        cout << "\n--------------------------------\n";
    }
    
    cout << "-------------------------------------\n";
    cout << "Enter place :: ";
    cin >> name;
    cout << "\nDFS :: ";
    g.DFS(name);
    cout << "\nBFS :: ";
    g.BFS(name);

    return 0;
}