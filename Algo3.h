//
// Created by jamal on 30/10/2018.
//

#ifndef MARKOVDECISION_ALGO3_H
#define MARKOVDECISION_ALGO3_H

#include <iostream>
#include "generateInput.cpp"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Samplingtree.h"

class Algo3 {
private:
    Inputs inputs;
    int n;
    int m;
    Samplingtree*** probTrees;
    double ** R;

public:
    double ApxTrans(double* u, double M, double epsilon, double psi, int action, int state);
    double** ApxVal(double* u, double* v0, double** x, double epsilon, double psi);
    value_policy RandomizedVI(double * v0, int L, double epsilon, double delta);
    value_policy HighPrecisionRandomVI(double epsilon, double delta);
    Algo3();
};


#endif //MARKOVDECISION_ALGO3_H
