// Dijkstra

// Calcula a menor distancia de x para todos o vertices
// d[i] = INF => nao existe caminho

//O(v log(e))

typedef pair<int,int> pii;
vector<vector<pii>> g; //vertice, peso

vector<int> dijkstra(int x){
    vector<int> d(g.size(), INF);
    priority_queue<pii, vector<pii>, greater<pii>> fila;
    d[x] = 0;
    fila.push({0, x});
    while(!fila.empty()){
        auto [vdist, v] = fila.top();
        fila.pop();
        if(vdist > d[v]) continue;
        for(auto[u, udist] : g[v]) if(d[u] > d[v] + udist){
            d[u] = d[v] + udist;
            fila.push({d[u], u});
        }
    }
    return d;
}
