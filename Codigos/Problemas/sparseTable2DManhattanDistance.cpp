/*
    Sparse Table 2D para distância Manhattan.
        - precisa colocar os valores iniciais do ponto (i,j) original em table[0][i+j][i-j+C] e chamar o build()
            - onde C+i-j >= 0 para todo i,j
        - a query de distancia manhattan do ponto (i,j) original deve ser feita como 
            query(i+j, i-j+C, distancia)
        Mantenha LOGN um pouco maior que o log real
*/

namespace sparse2D {
    const int LOGN = 11;
    int table[LOGN][MAXN][MAXN];
    int LOG[MAXN];
    void build() {
        for(int k=1; k<LOGN; k++) {
            int sz = (1 << k);
            int sz2 = (1 << (k-1));
            for(int i=0; i + sz <= MAXN; i++) {
                for(int j=0; j + sz <= MAXN; j++) {
                    table[k][i][j] = max({
                        table[k-1][i][j],
                        table[k-1][i+sz2][j],
                        table[k-1][i][j+sz2],
                        table[k-1][i+sz2][j+sz2]
                    });
                }
            }
        }
        LOG[1] = 0;
        for(int i=2; i<MAXN; i++) LOG[i] = 1 + LOG[i >> 1];
    }
    int query(int x, int y, int d) {
        int i1 = max(0, x-d);
        int i2 = min(MAXN-1, x+d);
        int j1 = max(0, y-d);
        int j2 = min(MAXN-1, y+d);
        int k = LOG[min(i2-i1+1, j2-j1+1)];
        int sz = (1<<k);
        int resp = 0;
        for(int i=i1; i<=i2; i += sz) {
            for(int j=j1; j<=j2; j += sz) {
                int p1 = min(i, i2-sz+1);
                int p2 = min(j, j2-sz+1);
                resp = max(resp, table[k][p1][p2]);
            }
        }
        return resp;
    }
};