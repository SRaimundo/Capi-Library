// Algoritmo para encontrar pontos de articulação em um grafo
// articulationPoints: vetor com os índices dos articulation points
// Complexidade das operações: O(V + E)
/*
    init(n);
    f(i,0,m) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    f(i,0,n) if(!visited[i]) dfs(i,i);
*/

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<bool> visited(MAXN);
vector<int> articulationPoints;
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
int entryTime;

void init(int numV) {
    entryTime = 0;
    articulationPoints.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        visited[i] = false;
    }
}

void dfs(int v, int parent) {
    visited[v] = true;
    lowlink[v] = tin[v] = entryTime++;

    bool isArticulationPoint = false;
    int numChildren = 0;

    for (int u : graph[v]) {
        if (!visited[u]) {
            numChildren++;
            
            dfs(u, v);
            lowlink[v] = min(lowlink[v], lowlink[u]);

            if (lowlink[u] >= tin[v]) isArticulationPoint = true;
        } else {
            if (u == parent) continue;

            lowlink[v] = min(lowlink[v], tin[u]);
        }
    }

    if (v == parent && numChildren >= 2) articulationPoints.push_back(v);
    if (v != parent && isArticulationPoint) articulationPoints.push_back(v);
}
