//
// Created by jamal on 30/10/2018.
//

#include "Algo3.h"

Algo3::Algo3() {
    R = new double* [n];
    probTrees = new Samplingtree** [n];
    for (int i = 0; i < n; i++) {
        R[i] = new double[m]();
        probTrees[n] = new Samplingtree *[m];
        for (int a = 0; a < m; a++) {
            R[i][a] = inputs.R[0][a][i];
            probTrees[i][a] = new Samplingtree(n, inputs.P[i][a]);
        }
    }
}

double Algo3::ApxTrans(double* u, double M, double epsilon, double psi, int action, int state) {
    double m = ceil( (2 * pow(M, 2) / pow(epsilon, 2) * log(2 / psi)) );
    double sum = 0;
    for (int i = 0; i < m; i++) {
        sum += u[probTrees[state][action]->performSampling()];
    }
    return (sum/m);
}

double** Algo3::ApxVal(double *u, double *v0, double **x, double epsilon, double psi) {
    double* uminv0 = new double[n]();
    double M = 0;
    for (int i = 0; i < n; i++) {
        uminv0[i] = u[i] - v0[i];
        if (abs(uminv0[i]) > infnorm) {
            M = abs(uminv0[i]);
        }
    }
    double** S = new double* [n];
    double** Q = new double* [n];
    double* v = new double[n]();
    double* p = new double[n]();
    for (int i = 0; i < n; i++) {
        S[i] = new double[m]();
        Q[i] = new double[m]();
        for (int a = 0; a < m; a++) {
            S[i][a] = x[i][a] + ApxTrans(uminv0, M, i, a, epsilon, psi / (n * m));
            Q[i][a] = R[i][a] + inputs.gamma * S[i][a];
            if (a == 0) {
                v[i] = Q[i][a];
                p[i] = a;
            } else {
                if (Q[i][a] > v[i]) {
                    v[i] = Q[i][a];
                    p[i] = a;
                }
            }
        }
    }
}

