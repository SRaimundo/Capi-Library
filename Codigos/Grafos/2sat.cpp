// Algoritmo 2-SAT usando Kosaraju
// init: Inicializa as estruturas de dados
// addDisjunction: Adiciona uma disjunção - na e nb significam se a e b devem ser negados
// solve2Sat: Resolve o problema 2-SAT e retorna verdadeiro se houver uma solução
// res[i]: Valor que a i-ésima variável deve assumir para a resposta ser válida
// Complexidade das operações: O(V + E)
/*
    init(2*n)
    f(i,0,m) addDisjunction(a, c1 == '-', b, c2 == '-')
    if (solve2Sat(n))
        for (i,0,n) cout << res[i];
*/
const ll MAXN = 200010;
vector<vector<int>> graph(MAXN);
vector<vector<int>> reverseGraph(MAXN);
vector<int> visited(MAXN);
vector<int> exitOrder;
vector<int> componentOfV(MAXN);
vector<bool> res(MAXN);
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

void addDisjunction(int a, bool na, int b, bool nb) {
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
