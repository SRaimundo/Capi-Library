// Max 1D Range Sum
// O(n)

int max1DRangeSum(vector<int> A, int n) {
  int sum = 0, ans = 0;
  for (int i = 0; i < n; ++i) {
    sum += A[i];
    ans = max(ans, sum);
    if (sum < 0) sum = 0;
  }
  return ans;
}