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
    double M = 0;
    double ** x;

public:
    double ApxTrans(double* u, double M, int state, int action, double epsilon, double psi) ;
    value_policy* ApxVal(double* u, double* v0, double** x, double epsilon, double psi);
    value_policy*  RandomizedVI(double * v0, int L, double epsilon, double delta);
    value_policy* HighPrecisionRandomVI(double epsilon, double delta);
    value_policy* SampledRandomizedVI(double * v0, int L, double epsilon, double delta, int k, int samplingRate);
    value_policy* SublinearRandomVI(double epsilon, double delta, int samplingRate);
    Algo3(int S, int A, Inputs inp);
};


#endif //MARKOVDECISION_ALGO3_H
