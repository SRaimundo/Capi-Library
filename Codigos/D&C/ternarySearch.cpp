// ternarySearchGetMin: Realiza uma busca ternária no intervalo [l, r] para encontrar o mínimo valor da função fMin
// ternarySearchGetMax: Realiza uma busca ternária no intervalo [l, r] para encontrar o máximo valor da função fMax
// Complexidade: O(log(n))

double fMin(double x){
    return abs(500.0-x);
}

double ternarySearchGetMin(double l, double r) {
    // double eps = 1e-9;              //set the error limit here
    // while (r - l > eps) {
    for (int i = 0; i < 100; ++i) {
        double delta = (r - l) / 3;
        double m1 = l + delta;
        double m2 = r - delta;
        (fMin(m1) > fMin(m2)) ? l = m1 : r = m2;
    }
    return l;
}

double fMax(double x){
    return 1000.0 - abs(500.0-x);
}

double ternarySearchGetMax(double l, double r) {
    // double eps = 1e-9;              //set the error limit here
    // while (r - l > eps) {
    for (int i = 0; i < 100; ++i) {
        double delta = (r - l) / 3;
        double m1 = l + delta;
        double m2 = r - delta;
        (fMax(m1) > fMax(m2)) ? r = m2 : l = m1;
    }
    return l;
}