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
#include "Algo3.h"
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
    int n = 1;
    int m = 1;
    double gamma = 0.5;
    Inputs inp = initialize(n, m, gamma);

    Algorithm2 *algo2 = new Algorithm2(inp, n, m);
    algo2->runAlgorithm(1000);
    algo2->printV();

/*
    Algorithm1 *algo1 = new Algorithm1();
    algo1->initializeAlgorithm(n, m, inp, 10000);
    algo1->run();
    algo1->outputV();
  //algo1->outputPi();
    algo1->clearData();


    std::thread algo1T(runAlgo1, inp, n, m, 100);
    std::thread algo2T(runAlgo2, inp, n, m, 100);

    */


    double epsilon = 0.9;
    double delta = 0.9;

    value_policy *vpl;
    Algo3 *algo3 = new Algo3(n,m,inp);
    vpl = algo3->HighPrecisionRandomVI(epsilon, delta);

    std::cout<<"algo3:\n";
    for(int i=0; i<n; i++){
        std::cout<<vpl->values[i]<<" ";
    }
    return 0;
}