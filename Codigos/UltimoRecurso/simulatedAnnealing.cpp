// Simulated Annealing
// Dado um vetor e uma função que o valor do vetor
// altera o vetor para conseguir o maior valor possível

// it = temperatura inicial (não alterar)
// cr = taxa de resfriamento
// ni = numero de iteracoes
// n = tamanho do vetor
// simulatedAnnealing = retorna o melhor valor encontrado

// Complexidade: O(ni*n)

#define ld long double

ld it = 100, cr = 0.999;
int ni = 100000;

int calculate(vector<int> &v) {
    // calcular um valor a partir de v
    // quanto mais perto v estiver da resposta
    // maior deve ser o valor retornado por essa função
}

int simulatedAnnealing(vector<int> &best) {
    ld t = it;
    vector<int> curr(best);
    int bestVal, currVal;
    bestVal = currVal = calculate(curr);

    for (int i = 0; i < ni; i++) {
        int r1 = rand()%curr.size();
        int r2 = rand()%curr.size();
        swap(curr[r1], curr[r2]);

        int newVal = calculate(curr);
        int d = currVal - newVal;

        if (d <= 0 || (rand() / static_cast<ld>(RAND_MAX)) < exp(-d / t)) {
            currVal = newVal;
            if (currVal > bestVal) {
                best = curr;
                bestVal = currVal;
            }
        } else swap(curr[r1], curr[r2]);
        
        t *= cr;
    }
    
    return bestVal;
}

int main() {
    srand(time(0));
    // main
    return 0;
}