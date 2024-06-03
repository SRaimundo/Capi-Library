// Centroid Decomposition e Centroid Tree

// c_tree contem a arvore de centroids
// c_par contem o pai de cada vertice na arvore de centroid
// dist[i] = distancia de i para os centroid

// O(n log(n)) (tempo e memoria)

vector<vector<int>> g(MAXN);

namespace centroid{
    vector<int> sz(MAXN);
    vector<bool> visit(MAXN,false);
    vector<vector<int>> c_tree(MAXN);
    vector<int> c_par(MAXN,-1);
    vector<vector<pair<int,int>>> dist(MAXN); // distancia, vertice

    void dfs_size(int v,int p=-1){
        sz[v] = 1;
        for(int u:g[v]) if(u!=p and !visit[u]){
            dfs_size(u,v);
            sz[v]+=sz[u];
        }
    }

    int find_centroid(int v, int size, int p=-1){
        for(int u:g[v])if(u!=p and !visit[u]){
            if(sz[u]>size/2) return find_centroid(u,size,v);
        }
        return v;
    }

    void dfs_dist(int v,int c,int p=-1,int d=0){
        dist[v].push_back({d,c});
        for(int u:g[v])if(u!=p and !visit[u]){
            dfs_dist(u,c,v,d+1);
        }
    }

    int build_centroid(int v=1){
        dfs_size(v);
        int c = find_centroid(v,sz[v]);

        visit[c] = true;
        dfs_dist(c,c);

        for(int u:g[c])if(!visit[u]){
            int neighbor = build_centroid(u);
            c_tree[c].push_back(neighbor);
            c_par[neighbor] = c;
        }

        return c;
    }

};