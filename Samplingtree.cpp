//
// Created by jamal on 30/09/2018.
//

#include <math.h>
#include "Samplingtree.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

Samplingtree::Samplingtree(int n, double* inprobs) {
    int n2 = pow(2, ceil(log2(n)));
    numProbs = n2;
    numOrgProbs = n;
    probs = new SamplingTreeNode*[n2];
    for (int i = 0; i < n2; i++) {
        probs[i] = new SamplingTreeNode;
        if (i < n) {
            probs[i]->setProbability(inprobs[i]);
            probs[i]->setIndex(i);
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
    if (node->getLeftChild() != nullptr) {
        traversePostOrderHelper(node->getLeftChild());

        // then recur on right subtree
        traversePostOrderHelper(node->getRightChild());
    }

    // now deal with the node
    cout << node->getProbability() << " ";
}

void Samplingtree::traversePostOrder() {
    traversePostOrderHelper(root);
    cout << endl;
}

void Samplingtree::updateHelper(SamplingTreeNode *node) {
    if (node->getLeftChild() != nullptr) {
        updateHelper(node->getLeftChild());
        updateHelper(node->getRightChild());
        node->recalculateProbability();
    }
}

void Samplingtree::updateProb(double * newprob) {
    for (int i = 0; i < numProbs; i++) {
        probs[i]->setProbability(newprob[i]);
    }
    updateHelper(root);
}

void Samplingtree::deleteTreeHelper(SamplingTreeNode* node) {
    // first recur on left subtree
    if (node->getLeftChild() != nullptr) {
        deleteTreeHelper(node->getLeftChild());

        // then recur on right subtree
        deleteTreeHelper(node->getRightChild());
    }

    // now deal with the node
    delete node;
}

void Samplingtree::deleteTree() {
    deleteTreeHelper(root);
}

int Samplingtree::performSampling() {
    SamplingTreeNode* node = root;
    while (node->getLeftChild() != nullptr) {
        SamplingTreeNode* leftChild = node->getLeftChild();
        double prob = leftChild->getProbability() / node->getProbability();
        double rndnum = (double) rand() / RAND_MAX;
        if (rndnum < prob) {
            node = leftChild;
        } else {
            node = node->getRightChild();
        }
    }
    return node->getIndex();
}

