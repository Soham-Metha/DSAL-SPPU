#include <iostream>

void setInp()
{
#ifndef INPUT
    freopen("p6_i.txt", "r", stdin);
#endif
}
using namespace std;

int count = 0;

int getCount()
{
    return count++;
}

class Node
{
public:
    string name;
    int id;
    Node *next;
    Node *down;
    Node(string nm, Node *n, Node *d) : name(nm), next(n), down(d), id(getCount()) {};
};

class AdjList
{
public:
    Node *head, *tail;
    AdjList()
    {
        head = NULL;
        tail = NULL;
    }
    Node *insertDownNode(string nm)
    {
        if (tail)
        {
            tail->down = new Node(nm, NULL, NULL);
            tail = tail->down;
        }
        else
        {
            head = new Node(nm, NULL, NULL);
            tail = head;
        }
        cout << "\nInserted " << tail->name;
        return tail;
    }
    Node *searchNode(string nm)
    {
        Node *tmp = head;
        if (head == NULL)
        {
            return insertDownNode(nm);
        }
        while (tmp->name != nm && tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        if (tmp->next == NULL && tmp->name!=nm)
        {
            return insertDownNode(nm);
        }
        return tmp;
    }
    void AppendNextNode(Node *n, Node *o)
    {
        Node *tmp = n;
        while (tmp->next != NULL)
        {
            if (tmp == o)
            {
                return;
            }
            tmp = tmp->next;
        }
        cout << "\nAppended " << o->name << " to " << tmp->name << "\n";
        tmp->next = o;
    }
    void addNodeToGraph()
    {
        string name;
        int cnt = 0;
        cout << "\nEnter name of city : ";
        cin >> name;
        cout << name;
        Node *n = searchNode(name);
        cout << "\nHow many adjecent nodes?";
        cin >> cnt;
        cout << cnt;
        for (size_t i = 0; i < cnt; i++)
        {
            string adj;
            cout << "\nEnter adjecent node : ";
            cin >> adj;
            cout << adj;
            Node *nn = searchNode(adj);
            AppendNextNode(n, nn);
            AppendNextNode(nn, n);
        }
    }
    void disp()
    {
        Node *tmpd = head;
        while (tmpd->next != NULL)
        {
            Node *tmpn = tmpd;
            while (tmpn->next != NULL)
            {
                cout << "-->" << tmpn->name;
                tmpn = tmpn->next;
            }
            tmpd = tmpd->down;
            cout << endl;
        }
    }
};
int main()
{
    setInp();
    AdjList list;
    list.addNodeToGraph();
    list.disp();
    list.addNodeToGraph();
    list.disp();
    list.addNodeToGraph();
    // list.disp();
    list.addNodeToGraph();
    // list.disp();
    return 0;
}