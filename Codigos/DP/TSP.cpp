// Traveling-Salesman-Problem
// A resposta é encontrada ao chamar: 
// dp(0, (1<<(n-1))-1)
// Complexidade: O(2^(n-1) * n^2)
// Permite resolução até n = [18..19].

#define LSOne(S) ((S) & -(S))

const int MAX_n = 11;

int dist[MAX_n][MAX_n], memo[MAX_n][1<<(MAX_n-1)];

int dp(int u, int mask) {
  if (mask == 0) return dist[u][0];
  int &ans = memo[u][mask];
  if (ans != -1) return ans;
  ans = INT_MAX;
  int m = mask;
  while (m) {
    int lso = LSOne(m);
    int v = __builtin_ctz(lso)+1;
    ans = min(ans, dist[u][v] + dp(v, mask^lso));
    m -= lso;
  }
  return ans;
}