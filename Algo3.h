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
    double * v;
    Samplingtree*** probTrees;
public:
    double ApxTrans(double M, double epsilon, double psi, int action, int state);
    Algo3();
};


#endif //MARKOVDECISION_ALGO3_H
