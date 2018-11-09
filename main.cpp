//
// Created by jamal on 30/09/2018.
//

#include <iostream>
#include "generateInput.cpp"
#include <cmath>
#include "Samplingtree.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Algorithm1.h"
#include "Algorithm2.h"
#include "Algo3.h"


int main() {
    srand(time(0));

    std::string dataFile, value;
    double epsilon, delta;
    std::cout<<"Please enter input filename (or leave blank to generate input):\n";
    getline(std::cin, dataFile);

    std::cout<<"Epsilon:\n";
    getline(std::cin, value);
    epsilon = stod(value);

    std::cout<<"Delta:\n";
    getline(std::cin, value);
    delta = stod(value);

    Inputs inp;
    int n,m;
    double gamma;
    if(!getData(dataFile, inp)){
        n=10;
        m=5;
        gamma=0.5;
        inp = initialize(n,m,gamma);
        dataFile = getCurrentTime();
        dataFile = dataFile + " - data.csv";
        saveData(dataFile, n, m, inp);
    }else{
        n = inp.N;
        m = inp.M;
    }



    Algorithm2 *algo2 = new Algorithm2(inp, n, m);


    algo2->runAlgorithmToConverge(epsilon);

    std::cout<<"value iteration time: "<< algo2->getTime() <<'\n';
    algo2->printV();


/*  Algorithm1 *algo1 = new Algorithm1();
    algo1->initializeAlgorithm(n, m, inp, 10000);
    algo1->run();
    algo1->outputV();
  //algo1->outputPi();
    algo1->clearData();


    std::thread algo1T(runAlgo1, inp, n, m, 100);
    std::thread algo2T(runAlgo2, inp, n, m, 100);

    */




    value_policy *vpl;
    Algo3 *algo3 = new Algo3(n,m,inp);

    clock_t start;
    double duration;
    start = clock();
    vpl = algo3->HighPrecisionRandomVI(epsilon, delta);
    duration = (clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout<<"variance reduced time: "<< duration <<'\n';

    std::cout<<"algo3:\n";
    for(int i=0; i<n; i++){
        std::cout<<vpl->values[i]<<" ";
    }
    std::cout<<"\n";


    saveTimes(dataFile, inp.gamma, epsilon, delta,algo2->getTime(), duration);

    clearInputs(n,m, inp);
    return 0;
}

