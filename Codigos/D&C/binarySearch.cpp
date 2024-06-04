// binarySearchFirstTrue: Encontra o primeiro valor verdadeiro de p no intervalo [l, r].
// binarySearchLastFalse: Encontra o último valor falso de p no intervalo [l, r].
// binarySearchContinuous: Busca binária para valores contínuos para encontrar o limite onde p se torna verdadeiro.
// Complexidade: O(log(r - l))

bool p(int x) {
    return x >= 4;
}

int binarySearchFirstTrue(int l, int r) {
    while(l<r) {
        int m = l + (r-l)/2;

        p(m) ? r = m : l = m+1;
    }
    return p(l) ? l : -1;
}

int binarySearchLastFalse(int l, int r) {
    while(l<r) {
        int m = l + (r-l+1)/2;
        p(m) ? r = m-1 : l = m;
    }
    return p(l) ? -1 : l;
}

double binarySearchContinuous(double l, double r) {
    for(int i=0;i<100;i++) {
        double m = l + (r-l)/2;
        p(m) ? r = m : l = m;
    }
    return l; 
}
