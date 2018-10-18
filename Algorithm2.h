//
// Created by jamal on 18/10/2018.
//

#ifndef MARKOVDECISION_ALGORITHM2_H
#define MARKOVDECISION_ALGORITHM2_H

#include <iostream>
#include "generateInput.cpp"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Algorithm2 {
private:
    Inputs inputs;
    int n;
    int m;
    double * v;

public:
    Algorithm2(Inputs inp, int numStates, int numActions);
    runAlgorithm(int numIterations);
    printV();
};


#endif //MARKOVDECISION_ALGORITHM2_H
