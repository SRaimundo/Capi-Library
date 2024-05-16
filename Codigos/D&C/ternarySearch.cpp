#include "bits/stdc++.h"
using namespace std;

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



int main() {
    cout << "Minimum Point: " << ternarySearchGetMin(0.0,1000.0) << endl;
    cout << "Maximum Point: " << ternarySearchGetMax(0.0,1000.0) << endl;
    return 0;
}