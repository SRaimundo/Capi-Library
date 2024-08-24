// Divide and Conquer DP
// recorrencia: dp(i,j) = min{0<=k<=j} dp(i-1,k-1) + C(k,j);
// precisa que opt seja monotono 
// no geral isso acontece quando 
// C(a, c) + C(b, d) <=  C(a, d) + C(b, c)
// para a <= b <= c <= d

vector<vector<ll>> dp;

int query(int i,int j){}

void dc_dp(int l,int r, int optl,int optr,int k){
    if(l>r) return;
    int mid = (l+r)/2, pos = -1;;
    ll best = INT_MAX;
    for(int j=optl;j<=min(mid,optr);j++){
        ll curCost = dp[k-1][j-1]+query(j,mid);
        if(curCost<best){
            best = curCost;
            pos = j;
        }
    }
    dp[k][mid] = best;
    dc_dp(l,mid-1,optl,pos,k);
    dc_dp(mid+1,r,pos,optr,k);
}

int solve(int n,int k){
    dp.resize(2,vector<ll>(n+1,INF));
    dp[0][0] = 0;
    for(int i=1;i<=k;i++){
        dc_dp(1,n,1,n,i);
    }
    return (dp[k][n]);
}