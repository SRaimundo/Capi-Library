// Strongly Connected Components - Componentes fortemente conexas
// components: componentes fortemente conexas
// Complexidade: O(V + E)
/*
    init(n);
    f(i,0,m) {
        graph[a].push_back(b);
        reverseGraph[b].push_back(a);
    }
    f(i,0,n) if(visited[i] == 0) dfs(i);

    int componentId = 0;
    for (int i = exitOrder.size()-1; i >= 0; i--) if(visited[exitOrder[i]] == 1) {
        components.push_back(vector<int>());
        dfs2(exitOrder[i], componentId++);
    }
*/

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> reverseGraph(MAXN);
vector<int> visited(MAXN);
vector<int> exitOrder;
vector<int> componentOfV(MAXN);
vector<vector<int>> components;

void init(int numV) {
    exitOrder.clear();
    components.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        reverseGraph[i].clear();
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
