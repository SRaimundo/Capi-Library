#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> reverseGraph(MAXN);
vector<int> visited(MAXN);
vector<int> exitOrder;
vector<int> componentOfV(MAXN);
vector<unordered_set<int>> condensationGraphEdges(MAXN);
vector<vector<int>> condensationGraph(MAXN);
vector<vector<int>> components;

void init(int numV, int numE) {
    exitOrder.clear();
    components.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        reverseGraph[i].clear();
        condensationGraph[i].clear();
        condensationGraphEdges[i].clear();
        visited[i] = 0;
    }
}

void dfs(int v) {
    visited[v] = 1;

    for (int u : graph[v]) if (visited[u] == 0) dfs(u);

    exitOrder.push_back(v);
}

void dfs2(int v, int c) {
    visited[v] = 2;
    componentOfV[v] = c;
    components.back().push_back(v);

    for (int u : reverseGraph[v]) if (visited[u] == 1) dfs2(u, c);
}

void dfs3(int v, int parent) {
    if (componentOfV[v] != componentOfV[parent]) {
        condensationGraphEdges[componentOfV[parent]].insert(componentOfV[v]);
    }
    visited[v] = 3;

    for (int u : graph[v]) if (visited[u] == 2) dfs3(u, v);
}

void createCondensationGraph(int n) {
    for (int i = 0; i < n; i++) if(visited[i] == 2) dfs3(i,i);

    for (int i = 0; i < components.size(); i++) {
        condensationGraph[i].insert(condensationGraph[i].end(), condensationGraphEdges[i].begin(), condensationGraphEdges[i].end());
    }
}

void solve() {
    ll n, m, a, b;
    cin >> n >> m;
    init(n, m);

    for (ll i = 0; i < m; i++) {
        cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }

    for (int i = 0; i < n; i++) if(visited[i] == 0) dfs(i);

    int componentId = 0;
    for (int i = exitOrder.size()-1; i >= 0; i--) if(visited[exitOrder[i]] == 1) {
        components.push_back(vector<int>());
        dfs2(exitOrder[i], componentId++);
    }

    createCondensationGraph(n);

    cout << "Condensation graph num of vertices: " << components.size() << endl;
    for (int i = 0; i < components.size(); i++) {
        for (int j = 0; j < condensationGraph[i].size(); j++) {
            cout << "(" << i+1 << ", " << condensationGraph[i][j]+1 << ") ";
        }
    }
    cout << endl << endl;
}

int main() {
    ll t;
    cin >> t;

    while (t--) solve();

    return 0;
}