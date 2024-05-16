#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> edgeIds(MAXN);
vector<bool> visited(MAXN);
vector<bool> edgeVisited(MAXN);
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
stack<int> vertices;
vector<vector<int>> ebcc; // edge-biconnected components
int entryTime;

void init(int numV, int numE) {
    entryTime = 0;
    ebcc.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        edgeIds[i].clear();
        visited[i] = false;
    }
    for (int i = 0; i < 2*numE; i++) {
        edgeVisited[i] = false;
    }
}

void dfs(int v, int parent) {
    visited[v] = true;
    lowlink[v] = tin[v] = entryTime++;
    vertices.push(v); 

    for (int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        int edgeId = edgeIds[v][i];

        if (edgeVisited[edgeId]) continue;
        edgeVisited[edgeId] = true;

        if (!visited[u]) {
            dfs(u, v);
            lowlink[v] = min(lowlink[v], lowlink[u]);
        } else {
            // with multiple edges, we can go back to the parent via an unvisited edge
            // if (u == parent) continue;

            lowlink[v] = min(lowlink[v], tin[u]);
        }
    }

    // we need to execute this for the root, so there's no need to check (v != parent)
    if (lowlink[v] == tin[v]) {
        vector<int> newComponent;
        do {
            newComponent.push_back(vertices.top());
            vertices.pop();
        } while (newComponent.back() != v);

        ebcc.push_back(newComponent);
    }
}

void solve() {
    ll n, m, a, b;
    cin >> n >> m;
    init(n, m);

    for (ll i = 0; i < m; i++) {
        cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
        edgeIds[a].push_back(i);
        edgeIds[b].push_back(i);
    }

    for (int i = 0; i < n; i++) if(!visited[i]) dfs(i,i);

    cout << "Num components: " << ebcc.size() << endl; 
    for (auto component : ebcc) {
        cout << "=> ";
        for (auto el : component) cout << el+1 << " ";
        cout << endl;
    }       
}

int main() {
    ll t;
    cin >> t;

    while (t--) solve();

    return 0;
}