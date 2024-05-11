// Algoritmo de Tarjan para pontes
// O(n+m)

const int MAXN = 200010;

vector<bool> marc(MAXN,false);
vector<int> pre(MAXN),low(MAXN),comp(MAXN);
stack<int> pilha;

vector<int> grafo[MAXN];
vector<int> vertices_da_componente[MAXN];
vector<pair<int,int> > bridges;

vector<int> componente;

int t=0,c=0,p=0;

void dfs(int v,int pai){
    t++;
    pre[v] = t;
    low[v] = t;
    marc[v] = true;
    pilha.push(v);

    for(int viz:grafo[v]){
        if(!marc[viz]){
            dfs(viz,v);
            low[v] = min(low[v],low[viz]);
        }else{
            if(viz==pai) continue;
            low[v] = min(low[v],pre[viz]);
        }
    }

    if(low[v]==pre[v]){
        c++;
        int vertice;

        if(v!=0){
            bridges.push_back({v,pai});
        }

        do{
            vertice = pilha.top();
            pilha.pop();
            comp[vertice] = c;
            vertices_da_componente[c].push_back(vertice);
            componente[vertice] = c;
        }while(vertice != v);
    }
}


vector<vector<int> > bridgesTree(){
    vector<vector<int> > tree(c+1);
    for(int i=0;i<bridges.size();i++){
        auto [a,b] = bridges[i];
        tree[componente[a]].push_back(componente[b]);
        tree[componente[b]].push_back(componente[a]);
    }
    return tree;
}
