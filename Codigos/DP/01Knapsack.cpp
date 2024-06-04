// 0-1 Knapsack - Problema da Mochila
// A resposta é obtida chamando dp(0, S), onde S é o tamanho máximo da mochila
// Complexidade: O(nS)

int N, V[MAX_N], W[MAX_N], memo[MAX_N][MAX_W];

int dp(int id, int remW) {
  if ((id == N) || (remW == 0)) return 0;
  int &ans = memo[id][remW];
  if (ans != -1) return ans;
  if (W[id] > remW) return ans = dp(id+1, remW);
  return ans = max(dp(id+1, remW), V[id]+dp(id+1, remW-W[id]));
}