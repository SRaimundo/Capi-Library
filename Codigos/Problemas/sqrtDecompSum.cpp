int N;
int A[MAX];

int SQRT, SIZE;
long long sq[1001];

void build() {
    SQRT = (int) sqrt(N);
    SIZE = (N + SQRT - 1) / SQRT;
    for(int i=0; i<SIZE; ++i) {
        for(int j=0; j<SQRT and i*SQRT + j < N; ++j) {
            sq[i] += A[i*SQRT + j]; 
        }
    }
}

void update(int p, int x) {
    sq[(p/SQRT) + (p%SQRT)] += x - A[p];
    A[p] = x;
}

long long query(int a, int b) {
    int pb = (b / SQRT);
    int pa = min(pb, (a + SQRT - 1) / SQRT);

    long long sum = 0;

    for(; a < SQRT*pa; ++a) sum += A[a];
    for(; pa < pb; pa++, a += SQRT) sum += sq[pa];
    for(; a <= b; a++) sum += A[a]; 

    return sum;
}