// Biconnected Components = 2-Vertex Connected Components
#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> edgeIds(MAXN);
vector<pair<int,int>> edges(MAXN);
vector<bool> visited(MAXN);
vector<bool> edgeVisited(MAXN);
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
vector<int> isArticulationPoint(MAXN);
stack<int> edgesStack;
vector<vector<pair<int,int>>> bcc; // biconnected components
int entryTime;

void init(int numV, int numE) {
    entryTime = 0;
    bcc.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        edgeIds[i].clear();
        visited[i] = false;
        isArticulationPoint[i] = false;
    }
    for (int i = 0; i < 2*numE; i++) {
        edgeVisited[i] = false;
    }
}

void newBiconnectedComponent (int edgeId) {
    if(edgesStack.empty()) return; // dealing with connected component of one vertex
    
    vector<pair<int,int>> newComponent;
    int currId;
    do {
        currId = edgesStack.top();
        newComponent.push_back(edges[currId]);
        edgesStack.pop();
        if(edgesStack.empty()) break;
    } while(currId != edgeId);
    bcc.push_back(newComponent);
}

void dfs(int v, int parent) {
    visited[v] = true;
    lowlink[v] = tin[v] = entryTime++;

    int numChildren = 0;
    for (int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        int edgeId = edgeIds[v][i];

        if (edgeVisited[edgeId]) continue;
        edgeVisited[edgeId] = true;
        edgesStack.push(edgeId);

        if (!visited[u]) {
            numChildren++;

            dfs(u, v);
            lowlink[v] = min(lowlink[v], lowlink[u]);

            bool foundNewComponent = false;
            if (v == parent && numChildren >= 2) foundNewComponent = true;
            if (v != parent && lowlink[u] >= tin[v]) foundNewComponent = true;

            if (foundNewComponent) {
                isArticulationPoint[v] = true;
                newBiconnectedComponent(edgeId);
            }
        } else {
            lowlink[v] = min(lowlink[v], tin[u]);
        }
    }
}

void findBiconnectedComponents(int n) {
    for (int i = 0; i < n; i++) {
        if(!visited[i]) {
            dfs(i,i);
            newBiconnectedComponent(-1);
        }
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
        edges[i] = {a, b};
    }

    findBiconnectedComponents(n);

    cout << "Num components: " << bcc.size() << endl; 
    for (auto component : bcc) {
        cout << "=> ";
        for (auto el : component) cout << "(" << el.first+1 << ", " << el.second+1 << ") ";
        cout << endl;
    }       
}

int main() {
    ll t;
    cin >> t;

    while (t--) solve();

    return 0;
}