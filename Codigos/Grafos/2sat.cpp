#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> reverseGraph(MAXN);
vector<int> visited(MAXN);
vector<int> exitOrder;
vector<int> componentOfV(MAXN);
vector<bool> res(MAXN);
vector<vector<int>> components;

void init(int numV, int numE) {
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

void addDisjunction(int a, bool na, int b, bool nb) {
    // na and nb signify whether a and b are to be negated 
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int negA = a ^ 1;
    int negB = b ^ 1;

    graph[negA].push_back(b);
    graph[negB].push_back(a);
    reverseGraph[b].push_back(negA);
    reverseGraph[a].push_back(negB);
}

bool solve2Sat(int n) {
    // first dfs of kosaraju
    for (int i = 0; i < 2*n; i++) if(visited[i] == 0) dfs(i);

    int componentId = 0;
    for (int i = exitOrder.size()-1; i >= 0; i--) if(visited[exitOrder[i]] == 1) {
        components.push_back(vector<int>());
        dfs2(exitOrder[i], componentId++);
    }

    for (int i = 0; i < n; i++) {
        if (componentOfV[2*i] == componentOfV[2*i+1]) return false;

        res[i] = (componentOfV[2*i] > componentOfV[2*i+1]);
    }
    return true;
}

void solve() {
    ll n, m, a, b;
    char c1, c2;

    cin >> n >> m;

    init(2*n, 2*m);

    for (ll i = 0; i < m; i++) {
        cin >> c1 >> a >> c2 >> b; a--; b--;
        
        addDisjunction(a, c1 == '-', b, c2 == '-');
    }

    if (solve2Sat(n)) {
        for (int i = 0; i < n; i++) {
            cout << (res[i] ? "+" : "-") << " \n"[i == n-1];
        }
    } else {
        cout << "IMPOSSIBLE" << endl;
    }
}

int main() {
    ll t;
    cin >> t;

    while (t--) solve();

    return 0;
}