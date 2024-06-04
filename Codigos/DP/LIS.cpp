// Longest Increasing Subsequence
// O(n log n)

int A[MAX_N];

void print_LIS(int i) {
    if (p[i] == -1) { printf("%d", A[i]); return; }
    print_LIS(p[i]);
    cout << A[i] << endl;
}

int lis(int n) {
    int k = 0, lis_end = 0;
    vi L(n, 0), L_id(n, 0);
    p.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
        L[pos] = A[i];
        L_id[pos] = i;
        p[i] = pos ? L_id[pos-1] : -1;
        if (pos == k) {
            k = pos+1;
            lis_end = i;
        }
    }

    print_LIS(lis_end);

    return k; // length of LIS
}