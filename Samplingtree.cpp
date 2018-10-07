//
// Created by jamal on 30/09/2018.
//

#include <math.h>
#include "Samplingtree.h"
#include <iostream>

Samplingtree::Samplingtree(int n, double* inprobs) {
    int n2 = pow(2, ceil(log2(n)));
    numProbs = n2;
    probs = new SamplingTreeNode*[n2];
    for (int i = 0; i < n2; i++) {
        probs[i] = new SamplingTreeNode;
        if (i < n) {
            probs[i]->setProbability(inprobs[i]);
        }
    }
    makeTree();
}

void Samplingtree::makeTree() {
    SamplingTreeNode** currentlayer = probs;
    SamplingTreeNode** nextlayer = nullptr;
    for (int i = log2(numProbs); i > 0; i--) {
        nextlayer = new SamplingTreeNode*[pow(2, i-1)];
        int j = 0;
        while (j < (pow(2, i))) {
            auto* newNode = new SamplingTreeNode;
            newNode->setLeftChild(currentlayer[j]);
            newNode->setRightChild(currentlayer[j+1]);
            newNode->setProbability(currentlayer[j]->getProbability() + currentlayer[j+1]->getProbability());
            currentlayer[j]->setParent(newNode);
            currentlayer[j+1]->setParent(newNode);
            nextlayer[j/2] = newNode;
            j += 2;
        }
        if (i != log2(numProbs)) {
            delete [] currentlayer;
        }
        currentlayer = nextlayer;
        if (i==1) {
            root = nextlayer[0];
        }
    }
}

void Samplingtree::traversePostOrderHelper(SamplingTreeNode* node) {
    // first recur on left subtree
    if (node->getLeftChild(node) != nullptr) {
        traversePostOrderHelper(node->getLeftChild(node));

        // then recur on right subtree
        traversePostOrderHelper(node->getRightChild(node));
    }

    // now deal with the node
    cout << node->getProbability() << " ";
}

void Samplingtree::traversePostOrder() {
    traversePostOrderHelper(root);
    cout << endl;
}

void Samplingtree::updateProb(int index, double newprob) {
    SamplingTreeNode* node = probs[index];
    node->setProbability(newprob);
    while (node->getParent() != nullptr) {
        node = node->getParent();
        node->recalculateProbability();
    }
}
