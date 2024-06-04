// Bridges - pontes
// bridges: vetor de pontes
// Complexidade: O(V + E)
/*
    init(n);
    f(i,0,m){
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    f(i,0,n) if(!visited[i]) dfs(i,i);
*/

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<bool> visited(MAXN);
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
vector<pair<int, int>> bridges;
int entryTime;

void init(int numV) {
    entryTime = 0;
    bridges.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        visited[i] = false;
    }
}

void dfs(int v, int parent) {
    visited[v] = true;
    lowlink[v] = tin[v] = entryTime++;

    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs(u, v);
            lowlink[v] = min(lowlink[v], lowlink[u]);
        } else {
            if (u == parent) continue;

            lowlink[v] = min(lowlink[v], tin[u]);
        }
    }

    if (v != parent && lowlink[v] == tin[v]) {
        bridges.push_back({v, parent});
    }
}
