//
// Created by jamal on 18/10/2018.
// Value iteration
//

#include "Algorithm2.h"


double Algorithm2::getTime() {
    return totalTime / (double) CLOCKS_PER_SEC;
}

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
                    sum1 += inputs.P[i][a][j] * v[j] * inputs.gamma;
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

void Algorithm2::runAlgorithmToConverge(double epsilon) {
    v = new double[n]();
    double * Tv;
    clock_t start;
    while (true) {
        start = clock();
        Tv = new double[n];
        for (int i = 0; i < n; i++) {
            double Ti = 0.0;
            for (int a = 0; a < m; a++) {
                double sum1 = 0.0;
                double sum2 = 0.0;
                for (int j = 0; j< n; j++) {
                    sum1 += inputs.P[i][a][j] * v[j] * inputs.gamma;
                    sum2 += inputs.P[i][a][j] * inputs.R[i][a][j]; //precompute
                }
                double total = sum1 + sum2;
                if (total > Ti) {
                    Ti = total;
                }
            }
            Tv[i] = Ti;
        }
        totalTime += (clock() - start);

        double Linf = 0;
        for (int i = 0; i < n; i++) {
            double diff = abs(Tv[i] - v[i]);
            if (diff > Linf) {
                Linf = diff;
            }
        }
        delete[] v;
        v = Tv;
        if (Linf <= epsilon / (1 - inputs.gamma)) {
            break;
        }
    }

}

void Algorithm2::printV() {
    std::cout << "algo2's V: [";
    for (int i = 0; i < n; i++) {
        std::cout << v[i] << ", " ;
    }
    std::cout << "]" << std::endl;
}