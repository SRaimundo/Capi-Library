// Max 2D Range Sum
// Find a sub-matrix of A with the maximum sum
// O(n^3)

#define MAX_n 110
int A[MAX_n][MAX_n];

int max2DRangeSum(int n) {
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      if (j > 0) A[i][j] += A[i][j-1];
    }
  int maxSubRect = INT_MIN; // lowest possible val
  for (int l = 0; l < n; ++l)
    for (int r = l; r < n; ++r) {
      int subRect = 0;
      for (int row = 0; row < n; ++row) {
        if (l > 0) subRect += A[row][r] - A[row][l-1];
        else       subRect += A[row][r];
        if (subRect < 0) subRect = 0;
        maxSubRect = max(maxSubRect, subRect);
      }
    }
  return maxSubRect;
}
