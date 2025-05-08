#include <bits/stdc++.h>
#define MAX_VERTEX 10
#define START(INDEX) arr[INDEX].start
#define END(INDEX) arr[INDEX].end
#define COST(INDEX) arr[INDEX].cost
#define FIND(I)                                                                                                        \
    {                                                                                                                  \
        while (unionFind[I] != I)                                                                                      \
            I = unionFind[I];                                                                                          \
    }

using namespace std;

int unionFind[MAX_VERTEX];

class Edge
{
  public:
    int start, end, cost;
    Edge(int s, int e, int c) : start(s), end(e), cost(c) {};
    bool operator<(const Edge &other) const
    {
        return cost < other.cost;
    }
    void disp()
    {
        cout << start << " \t| " << end << " \t| " << cost << "\n";
    }
};

void display(int vertexCount, int edgeCount, Edge arr[])
{
    int adjMatrix[vertexCount][vertexCount];

    for (size_t i = 0; i < vertexCount; i++)
        for (size_t j = 0; j < vertexCount; j++)
            adjMatrix[i][j] = 0;

    for (size_t i = 0; i < edgeCount; i++)
    {
        adjMatrix[START(i) - 1][END(i) - 1] = COST(i);
        adjMatrix[END(i) - 1][START(i) - 1] = COST(i);
    }

    for (size_t i = 0; i < vertexCount; i++)
    {
        for (size_t j = 0; j < vertexCount; j++)
            cout << adjMatrix[i][j] << "\t| ";
        cout << endl;
    }
    cout << endl;
}

void findShortestPath(int vertexCount, int edgeCount, Edge arr[])
{
    // InsertionSort(edgeCount, arr);
    sort(arr, arr + edgeCount);
    int cost = 0;
    for (size_t i = 0; i < edgeCount; i++)
    {
        int x = START(i);
        FIND(x);

        int y = END(i);
        FIND(y);

        if (x == y)
            continue;

        unionFind[y] = x;
        cost += COST(i);

        arr[i].disp();
    }
    cout << "TOTAL COST : " << cost << endl;
}

int main()
{
    for (size_t i = 0; i < MAX_VERTEX; i++)
        unionFind[i] = i;

    Edge graph[] = {Edge(1, 2, 21), Edge(1, 3, 12), Edge(1, 4, 37), Edge(2, 4, 10),
                    Edge(3, 4, 14), Edge(3, 5, 17), Edge(4, 5, 12)};

    int edgeCnt = 7;
    int vertexCnt = 5;

    for (size_t i = 0; i < edgeCnt; i++)
        graph[i].disp();

    cout << "\n\n MATRIX \n\n";

    display(vertexCnt, edgeCnt, graph);

    cout << "Edges chosen : \n"
         << "start\t| end\t| cost\n";
    findShortestPath(vertexCnt, edgeCnt, graph);
    cout << endl;

    return 0;
}

// DONT NEED THIS
/*

    bool operator>(Edge other)
    {
        return cost > other.cost;
    }

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

*/
