//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "Samplingtree.h"
#include "SamplingTreeNode.h"
using namespace std;

int main () {
    int n = 4;
    float* probs = new float[n];
    probs[0] = 0.1;
    probs[1] = 0.3;
    probs[2] = 0.4;
    probs[3] = 0.2;
    Samplingtree stree = Samplingtree(n, probs);
    stree.traversePostOrder();
    return 0;
}