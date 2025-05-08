#include <iostream>
#define MAX_VERTEX 10

using namespace std;

int unionFind[MAX_VERTEX];

class Edge
{
  public:
    int start;
    int end;
    int cost;
    Edge(int s, int e, int c) : start(s), end(e), cost(c) {};
    bool operator>(Edge other)
    {
        return cost > other.cost;
    }
    void disp()
    {
        cout << start << " \t| " << end << " \t| " << cost << "\n";
    }
};

void InsertionSort(int edgeCount, Edge arr[])
{
    for (int i = 1; i < edgeCount; ++i)
    {
        Edge key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void display(int vertexCount, int edgeCount, Edge arr[])
{
    int adjMatrix[vertexCount][vertexCount];

    for (size_t i = 0; i < vertexCount; i++)
        for (size_t j = 0; j < vertexCount; j++)
            adjMatrix[i][j] = 0;

    for (size_t i = 0; i < edgeCount; i++)
    {
        adjMatrix[arr[i].start - 1][arr[i].end - 1] = arr[i].cost;
        adjMatrix[arr[i].end - 1][arr[i].start - 1] = arr[i].cost;
    }
    for (size_t i = 0; i < vertexCount; i++)
    {
        for (size_t j = 0; j < vertexCount; j++)
            cout << adjMatrix[i][j] << "\t";
        cout << endl;
    }
}

void findShortestPath(int vertexCount, int edgeCount, Edge arr[])
{
    InsertionSort(edgeCount, arr);
    int cost = 0;
    for (size_t i = 0; i < edgeCount; i++)
    {
        int x = arr[i].start;
        while (unionFind[x] != x)
            x = unionFind[x];

        int y = arr[i].end;
        while (unionFind[y] != y)
            y = unionFind[y];
        if (x == y)
        {
            continue;
        }
        unionFind[y] = x;
        cost += arr[i].cost;

        arr[i].disp();
    }
    cout << "TOTAL COST : " << cost << endl;
}

int main()
{
    for (size_t i = 0; i < MAX_VERTEX; i++)
    {
        unionFind[i] = i;
    }

    Edge graph[] = {Edge(1, 2, 21), Edge(1, 3, 12), Edge(1, 4, 37), Edge(2, 4, 10),
                    Edge(3, 4, 14), Edge(3, 5, 17), Edge(4, 5, 12)};

    int egdeCnt = 7;
    int vertexCnt = 5;

    display(5, 7, graph);

    cout << "Edges chosen : \n"
         << "start\t| end\t| cost\n";
    findShortestPath(5, 7, graph);
    cout << endl;

    return 0;
}