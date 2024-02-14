// C++ implementation of the approach
//#include<bits/stdc++.h>
#include<vector>
#include<set>
#include<iostream>
using namespace std;

vector<vector<int>> adj;


// function to add edge to the graph
void addEdge(int x, int y)
{
    adj[x].push_back(y);
}

// Function to print the required topological
// sort of the given graph
void topologicalSort()
{
    int V = adj.size();
    // Create a vector to store indegrees of all
    // the vertices
    // Initialize all indegrees to 0
    vector<int> in_degree(V, 0);

    // Traverse adjacency lists to fill indegrees of
    // vertices
    // This step takes O(V+E) time
    for (int u = 0; u < V; u++) {
        for (auto x : adj[u])
            in_degree[x]++;
    }

    // Create a set and inserting all vertices with
    // indegree 0
    multiset<int> s;
    for (int i = 0; i < V; i++)
        if (in_degree[i] == 0)
            s.insert(i);

    // Initialize count of visited vertices
    int cnt = 0;

    // Create a vector to store result (A topological
    // ordering of the vertices)
    vector<int> top_order;

    // One by one erase vertices from setand insert
    // adjacents if indegree of adjacent becomes 0
    while (!s.empty()) {

        // Extract vertex with minimum number from multiset
        // and add it to topological order
        int u = *s.begin();
        s.erase(s.begin());
        top_order.push_back(u);

        // Iterate through all its neighbouring nodes
        // of erased node u and decrease their in-degree
        // by 1
        for (auto x : adj[u])

            // If in-degree becomes zero, add it to queue
            if (--in_degree[x] == 0)
                s.insert(x);

        cnt++;
    }

    // Check if there was a cycle
    if (cnt != V) {
        cout << -1;
        return;
    }

    // Print topological order
    for (int i = 0; i < top_order.size(); i++)
        cout << top_order[i] << " ";
}
int main()
{
    // number of vertices
    int v = 6;


    // adjacency matrix
    adj = vector<vector<int>>(v);

    addEdge(5, 2);
    addEdge(5, 0);
    addEdge(4, 0);
    addEdge(4, 1);
    addEdge(2, 3);
    addEdge(3, 1);

    // find required topological order
    topologicalSort();
}