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

using namespace std;

int main() {
    //for randomizing inputs
    srand(time(0));

    //line 1
    int n=4; //no. of States. |S| = n
    int m=3; //no. of Actions. |A| = m
    Inputs inp = initialize(n,m);

    double * q = new double[n];
    for(int i=0; i<n; i++) q[i] = 1.0/n;

    double Theta = 1 - inp.y;
    int T = 5;

    //line 2
    double * v = new double[n];   // v is a column matrix i think
    for(int i=0; i<n; i++) v[i]=0;

    //line 3
    double * Epsilon = new double[n];
    for(int i=0; i<n; i++) Epsilon[i] = 1.0/n;


    double ** PiI = new double*[n];
    for(int i=0; i<n; i++){
        PiI[i] = new double[m];
        for(int j=0; j<m; j++) PiI[i][j] = 1.0/m;
    }

    //line 4
    double Beta = (1-inp.y)*sqrt((log10(n*m + 1))/(2*n*m + T));
    double Alpha = (n / (2*pow(1-inp.y,2)));
    double M = (1.0/(1-inp.y));

    //line 5
    //preprocess input probabilties P = {pij(a)} for sampling done
    Samplingtree *** P = new Samplingtree**[n];
    for(int i=0; i<n; i++){
        P[i] = new Samplingtree*[m];
        for(int a=0; a<m; a++){
            P[i][a] = new Samplingtree(n, inp.P[i][a]);
        }
    }



    //line 6
    for(int t=1; t<=T; t++){
        //line 7
        //sample i with probability ((1-Theta)*Epsilon i + Theta*(q i))
        double * iProb = new double[n];
        for(int i=0; i<n; i++) iProb[i] = (1-Theta)*Epsilon[i] + Theta*q[i];

        Samplingtree *iSample = new Samplingtree(n, iProb);
        int stateI = iSample->performSampling();


        //line 8
        //sample a with probability PiI i, a
        double * aProb = new double[m];
        for(int a=0; a<m; a++) aProb[a] = PiI[stateI][a];
        Samplingtree * aTree = new Samplingtree(m, aProb);
        int actionA = aTree->performSampling();


        //line 9
        //conditioned on (i,a) sample j with probability p i,j(a)
        Samplingtree *jTree = new Samplingtree(n, inp.P[stateI][actionA]);
        int stateJ = jTree->performSampling();


        //line 10
        double delta = (inp.y*v[stateJ] - v[stateI] + inp.R[stateI][actionA][stateJ] - M);
        delta = delta/(((1-Theta)*Epsilon[stateI] + Theta*q[stateI])*PiI[stateI][actionA]);
        delta = delta*Beta;

        double tempMin = std::min((v[stateI] - Alpha*((((1-inp.y)*q[stateI])/((1-Theta)*Epsilon[stateI] + Theta*q[stateI]))-1)),(1/(1-inp.y)));
        v[stateI] = std::max(tempMin,0.0);

        tempMin = std::min((v[stateJ] - Alpha*inp.y),(1/(1-inp.y)));
        v[stateJ] = std::max(tempMin, 0.0);


        //line 11
        Epsilon[stateI] = Epsilon[stateI] + Epsilon[stateI]*PiI[stateI][actionA]*(exp(delta)-1);
        //Epsilon = Epsilon/||Epsilon||1
        PiI[stateI][actionA] = PiI[stateI][actionA]*(exp(delta));
        //PiI[stateI] = PiI[stateI]/||PiI[stateI]||1


        //freeing up space
        //line 7
        delete []iProb;
        iSample->deleteTree();
        delete iSample;

        //line 8
        delete []aProb;
        aTree->deleteTree();
        delete aTree;

        //line 9
        jTree->deleteTree();
        delete jTree;
    }



    //line 13! Output!!
    double * PiHatI = new double[n];
    for(int i=0; i<n; i++){
        PiHatI[i] = 1.0; //not complete
    }


    // Freeing up space
    //line 1
    for(int i=0; i<n; i++){
        for(int a=0; a<m; a++){
            delete []inp.P[i][a];
            delete []inp.R[i][a];
        }
        delete []inp.P[i];
        delete []inp.R[i];
    }
    delete []inp.P;
    delete []inp.R;

    delete []inp.S;
    delete []inp.A;

    delete []q;

    //line 2
    delete []v;

    //line 3
    delete []Epsilon;

    for(int i=0; i<n; i++) delete []PiI[i];
    delete []PiI;

    //line 5
    for(int i=0; i<n; i++){
        for(int a=0; a<m; a++){
            //delete tree calling P[i][a]->delete Tree
            delete []P[i][a];
        }
        delete []P[i];
    }
    delete []P;

    return 0;
}