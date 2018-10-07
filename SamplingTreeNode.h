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
    int index = -1;
public:
    void setLeftChild(SamplingTreeNode* lc);
    void setRightChild(SamplingTreeNode* rc);
    SamplingTreeNode* getLeftChild();
    SamplingTreeNode* getRightChild();
    void setProbability(double prob);
    void setParent(SamplingTreeNode* p);
    SamplingTreeNode* getParent();
    void recalculateProbability();
    double getProbability();
    void setIndex(int i);
    int getIndex();
};


#endif //MARKOVDECISION_SAMPLINGTREENODE_H
