struct SparseTable {
private:
    vector<vector<int>> sparse;
    vector<int> LOG;

public:
    SparseTable(vector<int> &v) {
        int N = v.size();
        LOG.assign(N+1, 0);
        for(int i=2; i<=N; ++i) LOG[i] = 1 + LOG[i >> 1];

        sparse.assign(LOG[N]+1, vector<int>(N));
        sparse[0] = v;
        for(int l=1; l<=LOG[N]; ++l) {
            for(int i=0; i+(1 << l) <= N; ++i) {
                sparse[l][i] = max(sparse[l-1][i], sparse[l-1][i + (1 << (l-1))]);
            }
        }
    }

    int RMQ(int i, int j) {
        int N = j-i+1;
        int L = LOG[N];
        return max(sparse[L][i], sparse[L][j-(1 << L)+1]);
    }
};