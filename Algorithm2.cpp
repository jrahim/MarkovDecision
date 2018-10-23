//
// Created by jamal on 18/10/2018.
//

#include "Algorithm2.h"


Algorithm2::Algorithm2(Inputs inp, int numStates, int numActions) {
    inputs = inp;
    n = numStates;
    m = numActions;
}

void Algorithm2::runAlgorithm(int numIterations) {
    v = new double[n]();
    double * Tv;
    for (int iter = 0; iter < numIterations; iter++) {
        Tv = new double[n];
        for (int i = 0; i < n; i++) {
            double Ti = 0.0;
            for (int a = 0; a < m; a++) {
                double sum1 = 0.0;
                double sum2 = 0.0;
                for (int j = 0; j< n; j++) {
                    sum1 += inputs.P[i][a][j] * v[j] * inputs.y;
                    sum2 += inputs.P[i][a][j] * inputs.R[i][a][j]; //precompute
                }
                double total = sum1 + sum2;
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
    std::cout << "[";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << ", " ;
    }
    std::cout << "]" << std::endl;
}