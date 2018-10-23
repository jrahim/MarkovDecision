//
// Created by Saad Ghani on 18/10/2018.
//

#ifndef RA_WORK_ALGORITHM1_H
#define RA_WORK_ALGORITHM1_H

#include "Samplingtree.h"
#include "generateInput.cpp"

class Algorithm1 {
private:
    Inputs inputs;
    int noOfStates;
    int noOfActions;

    double * q;
    double Theta, Time;
    double * v;
    double * Epsilon;
    double ** PiI;
    double * PiISum;

    double Beta, Alpha, M;

    Samplingtree *** P;
    double *iProb;
    Samplingtree * iSample;

    Samplingtree ** aSample;

    double *** PiT;
    double ** PiHat;

public:

    void initializeAlgorithm(int n, int m, Inputs inp, int T);
    void run();
    void outputV();
    void outputPiHat();
    void clearData();

};


#endif //RA_WORK_ALGORITHM1_H
