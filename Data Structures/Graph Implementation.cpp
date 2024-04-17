#include <iostream>
#include <list>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

class Graph 
{
    int V;
    // pointer to an array containing adjacency lists
    vector<vector<int>> adj;
    void _DFS(int v, vector<bool>& visited);

public:
    Graph(int V);
    void addEdge(int v, int w);
    void BFS(int s);
    void DFS(int v);
};

//getting the number of vertices
Graph::Graph(int V)
{
    this->V = V;
    adj.resize(V);
}

//takes two vertices and connects them
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

//
void Graph::_DFS(int v, vector<bool>& visited)
{
    visited[v] = true;
    cout << v << " ";

    for (auto i = adj[v].begin(); i!= adj[v].end(); i++)
    {
        if (!visited[*i])
        {
            _DFS(*i, visited);
        }
    }
}

void Graph::BFS(int s)
{
    //mark all the vertices as not visited
    vector<bool> visited(V, false);
    queue<int> q;
    visited[s] = true;
    q.push(s);

    while (!q.empty())
    {
        s = q.front();
        cout << s << " ";
        q.pop();
        for (auto i = adj[s].begin(); i!= adj[s].end(); i++)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                q.push(*i);
            }
        }
    }
}

void Graph::DFS(int v)
{
    //mark all the vertices as not visited
    vector<bool> visited(V, false);
    _DFS(v, visited);
}
