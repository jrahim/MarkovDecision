//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "generateInput.cpp"
#include "Samplingtree.h"
#include <cstdlib>
#include <ctime>
#include "Algorithm1.h"
#include "Algorithm2.h"

using namespace std;

int main() {
    int n = 10;
    //int m = 5;
    //double gamma = 0.5;
    //srand(time(0));
    //Inputs inp = initialize(n, m, gamma);


    /*for(int i=0; i<n; i++){
        for(int a =0; a<m; a++){
            for(int j=0; j<n; j++)std::cout<<inp.R[i][a][j]<<" ";
            std::cout<<"\n";
        }
    }

    Algorithm1 *algo1 = new Algorithm1();
    algo1->initializeAlgorithm(n,m,inp,1000000);
    algo1->run();
    algo1->outputV();
    algo1->clearData();


    std::cout<<"algo2:\n";
    Algorithm2 *algo2 = new Algorithm2(inp, n, m);
    algo2->runAlgorithm(10000);
    algo2->printV();

    clearInputs(n,m, inp);
     */
    n = 15;
    double * test = new double[n];
    for(int i=0; i<n; test[i++]= i+1);

    Samplingtree *testTree = new Samplingtree(n, test);

    for(int i=0; i<1000; i++){
        std::cout<<testTree->performSampling()<<"\n";
    }
    return 0;
}