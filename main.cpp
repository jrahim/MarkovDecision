//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "Samplingtree.h"
#include "SamplingTreeNode.h"
#include <math.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main () {
    srand(time(0));
    int n = 3;
    double* probs = new double[n];
    probs[0] = 0.1;
    probs[1] = 0.3;
    probs[2] = 0.6;
    Samplingtree stree = Samplingtree(n, probs);
    stree.traversePostOrder();
    stree.updateProb(2, 0.5);
    stree.traversePostOrder();
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    cout << stree.performSampling() << endl;
    return 0;
}