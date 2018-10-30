//
// Created by jamal on 30/10/2018.
//

#include "Algo3.h"

Algo3::Algo3() {
    probTrees = new Samplingtree** [n];
    for (int i = 0; i < n; i++) {
        probTrees[n] = new Samplingtree *[m];
        for (int a = 0; a < m; a++) {
            probTrees[i][a] = new Samplingtree(n, inputs.P[i][a]);
        }
    }
}

double Algo3::ApxTrans(double M, double epsilon, double psi, int action, int state) {
    double m = ceil( (2 * pow(M, 2) / pow(epsilon, 2) * log(2 / psi)) );
    
    for (int i = 0; i < m; i++) {
        double j = probTrees[state][action];
    }
}