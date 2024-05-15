// Biconnected Components = 2-Vertex Connected Components
#include "bits/stdc++.h"

#define ll long long

using namespace std;

const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> blockCutTree(MAXN);
vector<vector<int>> edgeIds(MAXN);
vector<pair<int,int>> edges(MAXN);
vector<bool> visited(MAXN);
vector<bool> compVisited(MAXN);
vector<bool> edgeVisited(MAXN);
vector<int> tin(MAXN);
vector<int> lowlink(MAXN);
vector<int> isArticulationPoint(MAXN);
stack<int> edgesStack;
vector<int> componentOfEdge(MAXN);
int componentId;
vector<vector<pair<int,int>>> bcc; // biconnected components
int entryTime;

void init(int numV, int numE) {
    entryTime = 0;
    componentId = 0;
    bcc.clear();
    for (int i = 0; i < numV; i++) {
        graph[i].clear();
        blockCutTree[i].clear();
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
        componentOfEdge[currId] = componentId;
        edgesStack.pop();
        if(edgesStack.empty()) break;
    } while(currId != edgeId);
    bcc.push_back(newComponent);
    componentId++;
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

void generateBlockCutTree(int n) {
    for (int i = 0; i < n; i++) {
        if (!isArticulationPoint[i]) continue;
        for (int edgeId : edgeIds[i]) {
            int comp = componentOfEdge[edgeId];
            if (!compVisited[comp]) {
                compVisited[comp] = true;
                blockCutTree[componentId].push_back(comp);
                blockCutTree[comp].push_back(componentId);
            }
        }
        for (int edgeId : edgeIds[i]) {
            int comp = componentOfEdge[edgeId];
            compVisited[comp] = false;
        }
        componentId++;
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
    generateBlockCutTree(n);

    cout << "Num components: " << bcc.size() << endl; 
    for (auto component : bcc) {
        cout << "=> ";
        for (auto el : component) cout << "(" << el.first+1 << ", " << el.second+1 << ") ";
        cout << endl;
    }

    cout << "Block-cut tree num of vertices: " << componentId << endl;
    for (int i = 0; i < componentId; i++) {
        for (int j = 0; j < blockCutTree[i].size(); j++) {
            cout << "(" << i+1 << ", " << blockCutTree[i][j]+1 << ") ";
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