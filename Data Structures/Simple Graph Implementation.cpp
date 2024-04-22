#include <iostream> 
#include <vector>
#include <stack>
#include <queue> 
#include <map>
#include <set>
#include <unordered_map>
#include <fstream>
using namespace std;


class Graph {
private:
    unordered_map<int, vector<int>> adjList;

public:
    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src);
    }

    void printGraph() {
        for (auto it = adjList.begin(); it != adjList.end(); it++)
        {
            cout<< "Vertex: " << it->first << " -> "; 
            for (int neighbor : it->second)
            {
                cout << neighbor << " ";
            }
            cout << endl;
            
        }
        
    }

    void addNode(int node) {
        //inserting a new node with an empty vector as its value
        adjList.insert({node, vector<int>()});
    }

    bool findNode(int node) {
        return adjList.find(node) != adjList.end();
    }

};


int main(int argc, char const *argv[])
{
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.printGraph();
    
    return 0;
}
