//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "Samplingtree.h"
#include "SamplingTreeNode.h"
#include <math.h>
#include <time.h>
using namespace std;

int main () {
    srand(time(0));
    int n = 5;
    double* probs = new double[n];
    probs[0] = 0.1;
    probs[1] = 0.3;
    probs[2] = 0.6;
    probs[3] = 0.2;
    probs[4] = 0.4;
    Samplingtree stree = Samplingtree(n, probs);
    stree.traversePostOrder();
    probs[2] = 0.8;
    stree.updateProb(probs);
    stree.traversePostOrder();
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    return 0;
}