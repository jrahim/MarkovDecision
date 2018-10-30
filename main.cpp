//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "generateInput.cpp"
#include <cmath>
#include "Samplingtree.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Algorithm1.h"
#include "Algorithm2.h"
#include <thread>


void runAlgo1(Inputs inp, int n, int m, int numIterations) {
    Algorithm1 *algo1 = new Algorithm1();
    algo1->initializeAlgorithm(n,m,inp, numIterations);
    algo1->run();
    algo1->outputV();
    algo1->outputPi();
    algo1->clearData();
}

void runAlgo2(Inputs inp, int n, int m, int numIterations) {
    Algorithm2 *algo2 = new Algorithm2(inp, n, m);
    algo2->runAlgorithm(numIterations);
    algo2->printV();
}

int main() {
    int n = 2;
    int m = 1;
    double gamma = 0.5;
    Inputs inp = initialize(n, m, gamma);

    Algorithm1 *algo1 = new Algorithm1();
    algo1->initializeAlgorithm(n, m, inp, 10000);
    algo1->run();
    algo1->outputV();
  //algo1->outputPi();
    algo1->clearData();

    Algorithm2 *algo2 = new Algorithm2(inp, n, m);
    algo2->runAlgorithm(1000);
    algo2->printV();

    std::thread algo1T(runAlgo1, inp, n, m, 100);
    std::thread algo2T(runAlgo2, inp, n, m, 100);

    return 0;
}