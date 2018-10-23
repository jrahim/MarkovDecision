//
// Created by Saad Ghani on 18/10/2018.
//

#include "Algorithm1.h"
#include <iostream>
#include <cmath>

void Algorithm1::initializeAlgorithm(int n, int m, Inputs inp, int T){

    //line 1
    noOfStates = n;
    noOfActions = m;
    inputs = inp;

    q = new double[n];
    for(int i=0; i<n; i++) q[i] = 1.0/n;

    Theta = 1 - inp.y;
    Time = T;

    //line 2
    v = new double[n]();

    //line 3
    Epsilon = new double[n];
    for(int i=0; i<n; i++) Epsilon[i] = 1.0/n;


    PiI = new double*[n];
    PiISum = new double[n];
    for(int i=0; i<n; i++){
        PiI[i] = new double[m];
        PiISum[i] = 0.0;
        for(int j=0; j<m; j++) {
            PiI[i][j] = 1.0/m;
            PiISum[i] += 1.0/m;
        }
    }

    //line 4
    Beta = (1-inp.y)*sqrt((log(n*m + 1))/(2*n*m*T)); //
    Alpha = (n / (2*pow(1-inp.y,2)))*Beta;
    M = (1.0/(1-inp.y));

    //line 5
    //preprocess input probabilties P = {pij(a)} for sampling done
    P = new Samplingtree**[n];
    for(int i=0; i<n; i++){
        P[i] = new Samplingtree*[m];
        for(int a=0; a<m; a++){
            P[i][a] = new Samplingtree(n, inp.P[i][a]);
        }
    }

    PiT = new double**[T];
    iProb = new double[n];
    for(int i=0; i<n; i++) iProb[i] = (1-Theta)*Epsilon[i] + Theta*q[i];
    iSample = new Samplingtree(n, iProb);

    aSample = new Samplingtree*[n];
    for(int i=0; i<n; i++){
        aSample[i] = new Samplingtree(m, PiI[i]);
    }

}

void Algorithm1::run() {

    //line 6
    for(int t=0; t<Time; t++){
        //line 7
        //sample i with probability ((1-Theta)*Epsilon i + Theta*(q i))
        for(int i=0; i<noOfStates; i++) iProb[i] = (1-Theta)*Epsilon[i] + Theta*q[i];


        iSample->updateProb(iProb);
        int stateI = iSample->performSampling();
        //Samplingtree *IS = new Samplingtree(noOfStates, iProb);
        //int stateI = IS->performSampling();
        //IS->deleteTree();
        //delete IS;

        //line 8
        //sample a with probability PiI i
        int actionA = aSample[stateI]->performSampling();


        //line 9
        //conditioned on (i,a) sample j with probability p i,j(a)
        int stateJ = P[stateI][actionA]->performSampling();

        //std::cout<<"stateI: "<<stateI<<" stateJ: "<<stateJ;

        //line 10
        double delta = (inputs.y*v[stateJ] - v[stateI] + inputs.R[stateI][actionA][stateJ] - M);
        delta = delta/(((1-Theta)*Epsilon[stateI] + Theta*q[stateI])*(PiI[stateI][actionA])/PiISum[stateI]);
        delta = delta*Beta;

        double tempVal = ((1-inputs.y)*q[stateI]);
        tempVal = tempVal / (((1-Theta)*Epsilon[stateI] + Theta*q[stateI]));
        double tempMin = std::min((v[stateI] - Alpha*(tempVal-1)), M);
        v[stateI] = std::max(tempMin,0.0);
        //std::cout<<" tempMinI: "<<v[stateI];

        tempMin = std::min((v[stateJ] - Alpha*inputs.y), M);
        v[stateJ] = std::max(tempMin, 0.0);
        //std::cout<<" tempMinJ: "<<v[stateJ]<<"\n";

        //line 11
        Epsilon[stateI] = Epsilon[stateI] + Epsilon[stateI]*(PiI[stateI][actionA]/PiISum[stateI])*(exp(delta)-1);
        //ask if correct
        double sum =0;
        for(int i=0; i<noOfStates; i++) sum += std::abs(Epsilon[i]);
        for(int i=0; i<noOfStates; i++) Epsilon[i] = Epsilon[i]/sum;

        double prevPiIVal = PiI[stateI][actionA];
        PiI[stateI][actionA] = PiI[stateI][actionA]*(exp(delta));
        PiISum[stateI] = PiISum[stateI] + PiI[stateI][actionA] - prevPiIVal;

        //aSample[stateI]->updateSingleProb(actionA, PiI[stateI][actionA]); you have to update one leaf node only. not entire row



        PiT[t] = new double*[noOfStates];
        for(int i=0; i<noOfStates; i++) {
            PiT[t][i] = new double[noOfActions]; //till what the code says
            for(int a=0; a<noOfActions; a++) PiT[t][i][a] = 1.0/noOfActions;
        }

        for(int a=0; a<noOfActions; a++)  PiT[t][stateI][a] = PiI[stateI][a];

        //debugging
        if((t+1)%1000 == 0){
            for(int i=0; i<noOfStates; i++)std::cout<<v[i]<<" ";
            std::cout<<"\n";
        }
    }
}

void Algorithm1::outputPiHat() {
    //line 13 Output!!
    PiHat = new double*[noOfStates];
    for(int i=0; i<noOfStates; i++){
        PiHat[i]= new double[noOfActions];
        for(int a=0; a<noOfActions; a++){
            double sum = 0.0;
            for(int t=0; t<Time; t++){
                sum += PiT[t][i][a];
            }
            PiHat[i][a] = sum/Time;
        }
    }

    for(int i=0; i<noOfStates; i++){
        std::cout<<"i: "<<i<<'\n';
        for(int a=0; a<noOfActions; a++){
            std::cout<<PiHat[i][a]<<" ";
        }
        std::cout<<"\n";
    }

    //line 13 (piHat)
    for(int i=0; i<noOfStates; i++) delete []PiHat[i];
    delete []PiHat;


}

void Algorithm1::outputV(){
    for(int i=0; i<noOfStates; i++) std::cout<<v[i]<<" ";
    std::cout<<"\n";
}
void Algorithm1::clearData() {


    delete []q;

    //line 2
    delete []v;

    //line 3
    delete []Epsilon;

    for(int i=0; i<noOfStates; i++) delete []PiI[i];
    delete []PiI;

    //line 5
    for(int i=0; i<noOfStates; i++){
        for(int a=0; a<noOfActions; a++){
            //delete tree calling P[i][a]->delete Tree
            delete []P[i][a];
        }
        delete []P[i];
    }
    delete []P;

    //line 11 (PiT)
    for(int t=0; t<Time; t++){
        for(int i=0; i<noOfStates; i++) delete []PiT[t][i];
        delete []PiT[t];
    }
    delete []PiT;


    //line 7
    delete []iProb;
    iSample->deleteTree();
    delete iSample;

    //line 8
    for(int i=0; i<noOfStates; i++) aSample[i]->deleteTree();
    delete []aSample;
}

