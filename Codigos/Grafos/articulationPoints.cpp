#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<bool> visited(MAXN);
vector<int> articulationPoints;
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
int entryTime;

void init(int numV, int numE) {
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

void solve() {
    ll n, m, a, b;
    cin >> n >> m;
    init(n, m);

    for (ll i = 0; i < m; i++) {
        cin >> a >> b; a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    for (int i = 0; i < n; i++) if(!visited[i]) dfs(i,i);

    cout << "Number of articulation points: " << articulationPoints.size() << endl;
    for (int point : articulationPoints) cout << point+1 << " ";
    cout << endl;
}

int main() {
    ll t;
    cin >> t;

    while (t--) solve();

    return 0;
}