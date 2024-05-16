// Small To Large
// 1. Faz queries sem update na subárvore
// 2. Resolve os filhos leves e depois os pesados. 
// 3. A resposta para os filhos leves é sempre adicionada e apagada. 
// 4. A resposta dos filhos pesados é mantida.
//
// O(N * log(N) * C(u))
// 
// C(u) é acomplexidade do update da
// informação de um vértice na resposta

void add(int u) {/* aqui adiciona a subarvore de u na resposta */}

void rem(int u) {/* aqui remove a subarvore de u da resposta */}
 
void solve(int u, int keep=1) {
    int mx = -1;
    for(int v : adj[u]) if(v != par[u]) {
        if(mx == -1 or subt[v] >= subt[mx]) {
            mx = v;
        }
    }
    for(int v : adj[u]) if(v != par[u] and v != mx) solve(v, 0);
    if(mx != -1) solve(mx, 1);
    /* aqui adiciona a informação de u na resposta */
    for(int v : adj[u]) if(v != par[u] and v != mx) add(v);
    /* aqui responde a query de u. ans[u] = ... */
    if(!keep) rem(u);
}