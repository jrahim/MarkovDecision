//
// Created by jamal on 18/10/2018.
//

#include "Algorithm2.h"

using namespace std;

Algorithm2::Algorithm2(Inputs inp, int numStates, int numActions) {
    inputs = inp;
    n = numStates;
    m = numActions;
}

void Algorithm2::runAlgorithm(int numIterations) {
    v = new double[n];
    double * Tv = new double[n];
    for (int iter = 0; iter < numIterations; iter++) {
        for (int i = 0; i < n; i++) {
            double Ti = 0.0;
            for (int a = 0; a < m; a++) {
                double sum1 = 0.0;
                double sum2 = 0.0;
                for (int j = 0; j< n; j++) {
                    sum1 += inputs.P[i][a][j] * v[j];
                    sum2 += inputs.P[i][a][j] * inputs.R[i][a][j];
                }
                double total = inputs.y * sum1 + sum2;
                if (total > Ti) {
                    Ti = total;
                }
            }
            Tv[i] = Ti;
        }
        delete[] v;
        v = Tv;
    }
}

void Algorithm2::printV() {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << v[i] << ", " ;
    }
    cout << "]" << endl;
}