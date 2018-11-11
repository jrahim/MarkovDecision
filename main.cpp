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
#include "Algorithm2.h"
#include "Algo3.h"



int main() {
    srand(time(0));

    std::string dataFile, value;
    double epsilon, delta, gamma;
    int n,m;
    std::cout<<"Please enter input filename (or leave blank to generate input):\n";
    getline(std::cin, dataFile);

    std::cout<<"Epsilon:\n";
    getline(std::cin, value);
    epsilon = stod(value);

    std::cout<<"Delta:\n";
    getline(std::cin, value);
    delta = stod(value);


    Inputs inp;
    if(!getData(dataFile, inp)){
        std::cout<<"Error reading input file. Either blank or incorrect naming format. Input will be generated.\n";
        std::cout<<"Number of States:\n";
        getline(std::cin, value);
        n = stoi(value);

        std::cout<<"Number of Actions:\n";
        getline(std::cin, value);
        m = stoi(value);

        std::cout<<"Gamma:\n";
        getline(std::cin, value);
        gamma = stod(value);

        inp = initialize(n,m,gamma);
        dataFile = getCurrentTime();
        dataFile = dataFile + " - data.csv";
        saveData(dataFile, n, m, inp);
    }else{
        n = inp.N;
        m = inp.M;
        gamma = inp.gamma;
    }



    Algorithm2 *algo2 = new Algorithm2(inp, n, m);

    algo2->runAlgorithmToConverge(epsilon);

    std::cout<<"value iteration time: "<< algo2->getTime() <<'\n';
    algo2->printV();


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


    saveTimes(dataFile, n, m,  inp.gamma, epsilon, delta,algo2->getTime(), duration);

    clearInputs(n,m, inp);
    return 0;
}

