//
// Created by jamal on 30/09/2018.
//

#ifndef MARKOVDECISION_SAMPLINGTREENODE_H
#define MARKOVDECISION_SAMPLINGTREENODE_H


class SamplingTreeNode {
private:
    SamplingTreeNode* leftChild = nullptr;
    SamplingTreeNode* rightChild = nullptr;
    SamplingTreeNode* parent = nullptr;
    double probability = 0.0;
public:
    void setLeftChild(SamplingTreeNode* lc);
    void setRightChild(SamplingTreeNode* rc);
    SamplingTreeNode* getLeftChild(SamplingTreeNode* node);
    SamplingTreeNode* getRightChild(SamplingTreeNode* node);
    void setProbability(double prob);
    void setParent(SamplingTreeNode* p);
    SamplingTreeNode* getParent();
    void recalculateProbability();
    double getProbability();
};


#endif //MARKOVDECISION_SAMPLINGTREENODE_H
