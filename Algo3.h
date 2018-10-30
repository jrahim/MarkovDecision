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

class value_policy{
public:
    double * values;
    double * pi;
};

class Algo3 {
private:
    Inputs inputs;
    int n;
    int m;
    Samplingtree*** probTrees;
    double ** R;
public:
    double ApxTrans(double* u, double M, double epsilon, double psi, int action, int state);
    value_policy ApxVal(double* u, double* v0, double** x, double epsilon, double psi);
    value_policy  RandomizedVI(double * v0, int L, double epsilon, double delta);
    Algo3(int S, int A, Inputs inp);
};


#endif //MARKOVDECISION_ALGO3_H
