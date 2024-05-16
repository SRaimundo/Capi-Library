#include "bits/stdc++.h"
using namespace std;

bool p(int x) {
    return x >= 4; // example [false, false, false, false, true, true]
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

int main() {
    cout << "First true: " << binarySearchFirstTrue(0,1000) << endl;
    cout << "Last false: " << binarySearchLastFalse(0,1000) << endl;
    return 0;
}