// Combinacao
// comb(n,k) retorna a combinação de n elementos
// agrupados k a k 

ll fat[MAXN], invfat[MAXN];
 
ll inv(ll a, ll b) {
	return a > 1 ? b - inv(b%a, a)*b/a : 1;
}
 
ll comb(int n,int k){
    if(k>n) return 0;
    ll val = (fat[n] * invfat[n-k])%MOD;
    val = (val*invfat[k])%MOD;
    return val;
}

void init(){
    fat[0] = 1;
    invfat[0] = inv(fat[0],MOD);
    for(int i=1;i<MAXN;i++){
        fat[i] = (fat[i-1]*i)%MOD;
        invfat[i] = inv(fat[i],MOD);
    }
}