// Crivo de Eratosthenes

// crivo - O(n log(log(n)))
// fact - O(log(n))

ll _tam_crivo;
bitset<10000010> bs;
vector<int> primos;

void crivo(ll limite){
    _tam_crivo = limite +1;
    bs.reset();bs.flip();
    bs.set(0,false); bs.set(1,false);
    for(ll i=2;i<=_tam_crivo; i++){
        if(bs.test((size_t)i)){
            for(ll j = i*i; j<=_tam_crivo;j+=i){
                bs.set((size_t)j,false);
            }
            primos.push_back((int)i);
        }
    }
}

bool eh_primo(ll N){
    if(N<_tam_crivo) return bs.test(N);
    for(int i=0;i<primos.size();i++){
        if(N%primos[i]==0){
            return false;
        }
    }
    return true;
}

vector<int> primeFactors(int N){
    vector<int> factors;
    int PF_idx = 0, PF = primos[PF_idx];
    while(N!=1 && PF*PF <= N){
        while(N%PF == 0){
            N/=PF;
            factors.push_back(PF);
        }
        PF=primos[++PF_idx];
    }
    if(N!=1) factors.push_back(N);
    return factors;
}

