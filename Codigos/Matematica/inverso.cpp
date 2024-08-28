/*
    Calcula o inverso modular de todos os números de 1 a MAXN-1
    1/1, 1/2, 1/3, ... mod MOD
*/
ll inverso[MAXN];
void init() {
    inverso[1] = 1;
    for (int i =2; i<MAXN; i++){
        inverso[i] = MOD - (MOD/i) * inverso[MOD % i] % MOD;
    }
}