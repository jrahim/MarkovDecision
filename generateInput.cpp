#ifndef GENERATEINPUT_CPP
#define GENERATEINPUT_CPP

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <regex>

struct Inputs{
    int N, M;
	int* S;
	int* A;
	double*** P;
	double*** R;
	double gamma; //gamma
};


static void printInputs(Inputs inp){

    std::cout<<"N: "<<inp.N<<" M: "<<inp.M<<" Gamma: "<<inp.gamma<<"\n";

    std::cout<<"S: ";
    for(int i=0; i<inp.N; i++){
        std::cout<<inp.S[i]<<" ";
    }

    std::cout<<"\nA: ";
    for(int i=0; i<inp.M; i++){
        std::cout<<inp.A[i]<<" ";
    }

    std::cout<<"\nP:\n";
    for(int i=0; i<inp.N; i++){
        std::cout<<"i: "<<i<<"\n";
        for(int a=0; a<inp.M; a++){
            for(int j=0; j<inp.N; j++){
                std::cout<<inp.P[i][a][j]<<" ";
            }
            std::cout<<"\n";
        }
    }

    std::cout<<"\nR:\n";
    for(int i=0; i<inp.N; i++){
        std::cout<<"i: "<<i<<"\n";
        for(int a=0; a<inp.M; a++){
            for(int j=0; j<inp.N; j++){
                std::cout<<inp.R[i][a][j]<<" ";
            }
            std::cout<<"\n";
        }
    }


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
			double sum=0;
			for(int j=0; j<n; j++){
				probs[i][a][j] = rand()%10;  //commenting out for debugging
				//probs[i][a][j] = 1;
				sum += probs[i][a][j];
				rewards[i][a][j] = (((double)rand()/RAND_MAX));
			}
			for(int j=0; j<n; j++) probs[i][a][j] /= sum;
		}
	}
	
	Inputs in;
	in.N = n;
	in.M = m;
	in.S = states;
	in.A = actions;
	in.P = probs;
	in.R = rewards;
	in.gamma = gamma;
	return in; 

}

static void clearInputs(int n, int m, Inputs ins){
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
}

/* File format:
 *  rough idea:
 *      CSV file
 *      first line - n, m, gamma
 *      second line - n values. each value depicting a state
 *      third line - m values. each value depicting an action
 *      n*m lines of P
 *          each line containing n values for P[i][a]
 *          first m lines containing values of P[0]
 *          second m lines containing values of P[1]
 *      n*m lines of R
 *          each line containing n values for R[i][a]
 *          first m lines containing values of R[0][0,...,m-1]
 *          second m lines containing values of R[1][0,...,m-1]
 *
 *
 * fully detailed:
 * n, m, gamma
 * S[0], S[1], ..., S[n-1]
 * A[0], A[1], ..., A[m-1]
 * P[0][0][0], P[0][0][1], P[0][0][2], ..., P[0][0][n-1]
 * P[0][1][0], P[0][1][1], P[0][1][2], ..., P[0][1][n-1]
 * P[0][2][0], P[0][2][1], P[0][2][2], ..., P[0][2][n-1]
 * .
 * .
 * .
 * P[0][m-1][0], P[0][m-1][1], P[0][m-1][2], ..., P[0][m-1][n-1]
 * R[1][0][0], R[1][0][1], R[1][0][2], ..., R[1][0][n-1]
 * R[1][1][0], R[1][1][1], R[1][1][2], ..., R[1][1][n-1]
 * R[1][2][0], R[1][2][1], R[1][2][2], ..., R[1][2][n-1]
 * .
 * .
 * .
 * R[1][m-1][0], R[0][m-1][1], R[1][m-1][2], ..., R[1][m-1][n-1]
 * .
 * .
 * .
 * R[n-1][0][0], R[n-1][0][1], R[n-1][0][2], ..., R[n-1][0][n-1]
 * R[n-1][1][0], R[n-1][1][1], R[n-1][1][2], ..., R[n-1][1][n-1]
 * R[n-1][2][0], R[n-1][2][1], R[n-1][2][2], ..., R[n-1][2][n-1]
 * .
 * .
 * .
 * R[n-1][m-1][0], R[n-1][m-1][1], R[n-1][m-1][2], ..., R[n-1][m-1][n-1]
 * R[0][0][0], R[0][0][1], R[0][0][2], ..., R[0][0][n-1]
 * R[0][1][0], R[0][1][1], R[0][1][2], ..., R[0][1][n-1]
 * R[0][2][0], R[0][2][1], R[0][2][2], ..., R[0][2][n-1]
 * .
 * .
 * .
 * R[0][m-1][0], R[0][m-1][1], R[0][m-1][2], ..., R[0][m-1][n-1]
 * R[1][0][0], R[1][0][1], R[1][0][2], ..., R[1][0][n-1]
 * R[1][1][0], R[1][1][1], R[1][1][2], ..., R[1][1][n-1]
 * R[1][2][0], R[1][2][1], R[1][2][2], ..., R[1][2][n-1]
 * .
 * .
 * .
 * R[1][m-1][0], R[0][m-1][1], R[1][m-1][2], ..., R[1][m-1][n-1]
 * .
 * .
 * .
 * R[n-1][0][0], R[n-1][0][1], R[n-1][0][2], ..., R[n-1][0][n-1]
 * R[n-1][1][0], R[n-1][1][1], R[n-1][1][2], ..., R[n-1][1][n-1]
 * R[n-1][2][0], R[n-1][2][1], R[n-1][2][2], ..., R[n-1][2][n-1]
 * .
 * .
 * .
 * R[n-1][m-1][0], R[n-1][m-1][1], R[n-1][m-1][2], ..., R[n-1][m-1][n-1]
 */
static void saveData(std::string fileName, int n, int m, Inputs inp) {
    std::ofstream outfile;
    outfile.open(fileName);

    outfile << n << "," << m << "," << inp.gamma << "\n";

    for (int i = 0; i < n - 1; i++) {
        outfile << inp.S[i] << ",";
    }
    outfile << inp.S[n - 1] << "\n";

    for (int i = 0; i < m - 1; i++) {
        outfile << inp.A[i] << ",";
    }
    outfile << inp.A[m - 1] << "\n";

    for(int i = 0; i < n; i++){
        for (int a = 0; a < m; a++) {
            for (int j = 0; j < n - 1; j++) {
                outfile << inp.P[i][a][j] << ",";
            }
            outfile << inp.P[i][a][n - 1] << "\n";
        }
    }

    for(int i = 0; i < n; i++){
        for (int a = 0; a < m; a++) {
            for (int j = 0; j < n - 1; j++) {
                outfile << inp.R[i][a][j] << ",";
            }
            outfile << inp.R[i][a][n - 1] << "\n";
        }
    }


    outfile.close();
}

static bool getData(std::string fileName, Inputs & inp){
    std::ifstream infile;

    std::regex e("((.*\\/|)(0[1-9]|[12]\\d|3[01])-(0[1-9]|1[0-2])-[12]\\d{3} (0\\d|1\\d|2[0-3]):([0-5]\\d):([0-5]\\d) - data.csv)");
    if(!std::regex_match(fileName, e))
        return false;

    infile.open(fileName);
    if (infile.fail()) return false;

    std::string val;
    getline(infile, val, ',');
    inp.N = stoi(val);
    getline(infile, val, ',');
    inp.M = stoi(val);
    getline(infile, val);
    inp.gamma = stod(val);

    inp.S = new int[inp.N];
    for(int i=0; i<inp.N-1; i++){
        getline(infile, val, ',');
        inp.S[i] = stoi(val);
    }
    getline(infile, val);
    inp.S[inp.N-1] = stoi(val);

    inp.A = new int[inp.M];
    for(int a=0; a<inp.M-1; a++){
        getline(infile, val, ',');
        inp.A[a] = stoi(val);
    }
    getline(infile, val);
    inp.A[inp.M-1] = stoi(val);

    inp.P = new double**[inp.N];
    for(int i=0; i<inp.N; i++){
        inp.P[i] = new double*[inp.M];
        for(int a=0; a<inp.M; a++){
            inp.P[i][a] = new double[inp.N];
            for(int j=0; j<inp.N-1; j++){
                getline(infile, val, ',');
                inp.P[i][a][j] = stod(val);
            }
            getline(infile, val);
            inp.P[i][a][inp.N-1] = stod(val);
        }
    }

    inp.R = new double**[inp.N];
    for(int i=0; i<inp.N; i++){
        inp.R[i] = new double*[inp.M];
        for(int a=0; a<inp.M; a++){
            inp.R[i][a] = new double[inp.N];
            for(int j=0; j<inp.N-1; j++){
                getline(infile, val, ',');
                inp.R[i][a][j] = stod(val);
            }
            getline(infile, val);
            inp.R[i][a][inp.N-1] = stod(val);
        }
    }

    infile.close();
    return true;
}

static std::string getCurrentTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
    std::string str(buffer);

    return str;
}

/* File format:
 * filename: data file - output.csv
 * each line: |S|,|A|,epsilon,delta,gamma,valueIteration_time,varianceReducedVI_time
 *
 */
static void saveTimes(std::string filename, int n, int m, double gamma, double epsilon, double delta, double valueIteration_time, double varianceReducedVI_time){
    std::string timeBit = filename.substr(0, filename.find(" - data.csv"));

    std::string outputName = timeBit+" - output.csv";

    std::ofstream outfile;
    outfile.open(outputName, std::ofstream::out | std::ofstream::app);

    outfile<<n<<","<<m<<","<<epsilon<<","<<delta<<","<<gamma<<","<<valueIteration_time<<","<<varianceReducedVI_time<<"\n";

    outfile.close();

}


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

	std::cout<<ins.gamma<<"\n";

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

#endif //GENERATEINPUT_CPP

