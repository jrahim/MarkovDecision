//
// Created by jamal on 30/09/2018.
//

#include "SamplingTreeNode.h"

void SamplingTreeNode::setProbability(double prob) {
    probability = prob;
}

void SamplingTreeNode::setLeftChild(SamplingTreeNode *lc) {
    leftChild = lc;
}

void SamplingTreeNode::setRightChild(SamplingTreeNode *rc) {
    rightChild = rc;
}

void SamplingTreeNode::setParent(SamplingTreeNode *p) {
    parent = p;
}

double SamplingTreeNode::getProbability() {
    return probability;
}

SamplingTreeNode* SamplingTreeNode::getLeftChild(SamplingTreeNode* node) {
    return node->leftChild;
}

SamplingTreeNode* SamplingTreeNode::getRightChild(SamplingTreeNode* node) {
    return node->rightChild;
}

SamplingTreeNode* SamplingTreeNode::getParent() {
    return parent;
}

void SamplingTreeNode::recalculateProbability() {
    probability = leftChild->getProbability() + rightChild->getProbability();
}
