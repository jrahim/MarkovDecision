//
// Created by jamal on 30/10/2018.
//

#include "Algo3.h"

struct value_policy{
    double * values;
    double * pi;
};

Algo3::Algo3(int S, int A, Inputs inp) {
    n = S;
    m = A;
    inputs = inp;
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

double ** Algo3::RandomizedVI(double *v0, int L, double epsilon, double delta) {
    double ** x = new double*[n];
    //line 1
    for(int i=0; i<n; i++){
        x[i] = new double[m];
        for(int a=0; a<m; a++) {
            x[i][a] = 0;
            for (int j = 0; j < n; j++) {
                x[i][a] += inputs.P[i][a][j] * v0[j];
            }
        }
    }
    value_policy vpl;
    vpl.values =
    for(int i=1; i<L; i++){

    }
}