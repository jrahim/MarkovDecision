//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "generateInput.cpp"
#include "Samplingtree.h"
#include <cstdlib>
#include <ctime>
#include "Algorithm1.h"
#include "Algorithm2.h"

using namespace std;

int main() {
     int n = 3;
    int m = 2;
    double gamma = 0.5;
    srand(time(0));
    Inputs inp = initialize(n, m, gamma);

    Algorithm1 *algo1 = new Algorithm1();
    algo1->initializeAlgorithm(n, m, inp, 1000);
    algo1->run();
    algo1->outputV();
    algo1->clearData();

    std::cout<<"algo2:\n";
    Algorithm2 *algo2 = new Algorithm2(inp, n, m);
    algo2->runAlgorithm(500);
    algo2->printV();

    std::cout<< "\n"<<inp.R[0][0][0];

    clearInputs(n,m, inp);


    return 0;
}