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

using namespace std;

int main() {
    int n=10;
    int m = 10;
    double gamma = 0.5;
    Inputs inp = initialize(n,m,gamma);
    Algorithm1 *algo1 = new Algorithm1();

    algo1->initializeAlgorithm(n,m,inp,100);
    algo1->run();
    algo1->outputPiHat();
    algo1->clearData();
    return 0;
}

