#ifndef GENERATE_INPUT
#define GENERATE_INPUT

#include <iostream>
#include <stdlib.h>

struct Inputs{
	int* S;
	int* A;
	double*** P;
	double*** R;
	double y; //gamma

};


static Inputs initialize(int n, int m, double y){
	int * states = new int[n];
	int * actions = new int[m];
	double *** probs = new double**[n];
	double *** rewards = new double**[n];
	double gamma = y;


	//initializing states and actions
	for(int i=0; i<n; i++) states[i]= i;
	for(int i=0; i<m; i++) actions[i]= i;

	//initializing probabilties and rewards
	for(int i=0; i<n; i++){
		probs[i] = new double*[m];
		rewards[i] = new double*[m];
		for(int a=0; a<m; a++){
			probs[i][a] = new double[n];
			rewards[i][a] = new double[n];
			int sum=0;
			for(int j=0; j<n; j++){
				probs[i][a][j] = rand()%10;
				sum += probs[i][a][j];
				rewards[i][a][j] = rand()%10;
			}
			for(int j=0; j<n; j++) probs[i][a][j] /= sum;
		}
	}

	Inputs in;
	in.S = states;
	in.A = actions;
	in.P = probs;
	in.R = rewards;
	in.y = gamma;
	return in;

}

#endif

/* for debugging purposes
int main(){
	int n=10;
	int m=7;
	Inputs ins = initialize(n,m);
	
	for(int i=0; i<n; i++)std::cout<<ins.S[i]<<" ";
	std::cout<<"\n";
	for(int i=0; i<m; i++)std::cout<<ins.A[i]<<" ";
	std::cout<<"\n";


	for(int i=0; i<n; i++){
		std::cout<<"i: "<<i<<"\n";
		for(int a=0; a<m; a++){
			double sum=0;
			for(int j=0; j<n; j++) {
				sum += ins.P[i][a][j];
				std::cout<<ins.P[i][a][j]<<" ";
			}
			std::cout<<sum<<"\n";
		}
	}


	for(int i=0; i<n; i++){
		std::cout<<"i: "<<i<<"\n";
		for(int a=0; a<m; a++){
			for(int j=0; j<n; j++) std::cout<<ins.R[i][a][j]<<" ";
			std::cout<<"\n";
		}
	}

	std::cout<<ins.y<<"\n";

	// make sure you free space at the end
	for(int i=0; i<n; i++){
		for(int a=0; a<m; a++){
			delete []ins.P[i][a];
			delete []ins.R[i][a];
		}
		delete []ins.P[i];
		delete []ins.R[i];
	}

	delete []ins.S;
	delete []ins.A;

	return 0;
}
*/

