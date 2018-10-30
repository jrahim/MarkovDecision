//
// Created by jamal on 30/10/2018.
//

#include "Algo3.h"

Algo3::Algo3(int S, int A, Inputs inp) {
    n = S;
    m = A;
    inputs = inp;
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

value_policy Algo3::ApxVal(double *u, double *v0, double **x, double epsilon, double psi) {
    double* uminv0 = new double[n]();
    double M = 0;
    for (int i = 0; i < n; i++) {
        uminv0[i] = u[i] - v0[i];
        if (abs(uminv0[i]) > M) {
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
        delete Q[i];
        delete S[i];
    }
    delete Q;
    delete S;
    value_policy vpl = new value_policy();
    vpl.values = v;
    vpl.pi = p;
    return vpl;
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