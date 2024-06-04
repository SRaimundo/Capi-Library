// Bridge Tree / Edge-Biconnected Components
// NÃO FUNCIONA COM ARESTAS MÚLTIPLAS
// Encontra os EBCC de um grafo não direcionado
// ebcc: vetor de EBCCs
// Complexidade: O(V + E)
/*
    init(n);
    f(i,0,m){
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    f(i,0,n) if(!visited[i]) dfs(i,i);
*/
#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<bool> visited(MAXN);
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
stack<int> vertices;
vector<vector<int>> ebcc;
int entryTime;

void init(int numV) {
    entryTime = 0;
    ebcc.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        visited[i] = false;
    }
}

void dfs(int v, int parent) {
    visited[v] = true;
    lowlink[v] = tin[v] = entryTime++;
    vertices.push(v); 

    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs(u, v);
            lowlink[v] = min(lowlink[v], lowlink[u]);
        } else {
            if (u == parent) continue;

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
