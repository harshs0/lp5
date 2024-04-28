#include <bits/stdc++.h>
using namespace std;

class graph
{
    int v;
    vector<vector<int>> adj;

public:
    graph(int v) : v(v), adj(v) {}
    void addedge(int v, int w)
    {
        adj[v].push_back(w);
    }
    void paralleldfs(int startvertex)
    {
        vector<bool> visited(v, false);
        paralleldfsutil(startvertex, visited);
    }

    void paralleldfsutil(int v, vector<bool> &visited)
    {
        visited[v] = true;
        cout << v << " ";
#pragma omp parallel for
        for (int i = 0; i < adj[v].size(); ++i)
        {
            int n = adj[v][i];
            if (!visited[n])
                paralleldfsutil(n, visited);
        }
    }

    void parallelbfs(int startvertex)
    {
        vector<bool> visited(v, false);
        visited[startvertex] = true;
        queue<int> q;
        q.push(startvertex);

        while (!q.empty())
        {
            int vv = q.front();
            q.pop();
            cout << vv << " ";

#pragma omp parallel for
            for (int i = 0; i < adj[vv].size(); ++i)
            {
                int n = adj[vv][i];
                if (!visited[n])
                {
                    visited[n] = true;
                    q.push(n);
                }
            }
        }
    }
};

int main()
{
    int n;
    int n1, n2;
    cout << "Enter the points you want to add : " << endl;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the two points : " << endl;
        cin >> n1 >> n2;
        g.addedge(n1, n2);
    }

    int ch;
    do
    {
        cout << "----MENU----" << endl;
        cout << "1.Breadth First Search" << endl;
        cout << "2.Depth First Search" << endl;
        cout << "3.Exit" << endl;
        cout << "Enter your choice : " << endl;
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "BFS: ";
            g.parallelbfs(0);
            break;

        case 2:
            cout << "DFS: ";
            g.paralleldfs(0);
            break;

        case 3:
            cout << "Thankyou for using our program .";
            break;

        default:
            cout << "Invalid choice ";
            break;
        }
    }while (ch != 3);

return 0;
}
