// Bridge Tree / Edge-Biconnected Components
// Versão que lida com arestas múltiplas
// Encontra os EBCC de um grafo não direcionado
// ebcc: vetor de EBCCs
// Complexidade: O(V + E)
/*
    init(n, m);
    f(i,0,m) {
        graph[a].push_back(b);
        graph[b].push_back(a);
        edgeIds[a].push_back(i);
        edgeIds[b].push_back(i);
    }
    f(i,0,n) if(!visited[i]) dfs(i,i);
*/

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> edgeIds(MAXN);
vector<bool> visited(MAXN);
vector<bool> edgeVisited(MAXN);
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
stack<int> vertices;
vector<vector<int>> ebcc;
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
            lowlink[v] = min(lowlink[v], tin[u]);
        }
    }

    if (lowlink[v] == tin[v]) {
        vector<int> newComponent;
        do {
            newComponent.push_back(vertices.top());
            vertices.pop();
        } while (newComponent.back() != v);

        ebcc.push_back(newComponent);
    }
}
