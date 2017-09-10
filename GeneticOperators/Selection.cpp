#include "Selection.hpp"
#include <algorithm>
#include <iostream>
#include <ctime>

//constructors
Selection::Selection() {
	type = 1; //random selection
	elitism = 0.5;
	tournament_size = 100;

}

Selection::Selection(const int t,const double e,const int size) {
	type = t;
	elitism = e;
	tournament_size = size;

}


//destructor
Selection::~Selection() {}

int Selection::parent(const int i)
{
	if (i == 1) {
		return parent1;
	} else {
		return parent2;
	}
}

int Selection::child(const int i)
{
	if (i == 1) {
		return child1;
	} else {
		return child2;
	}
}

void Selection::select(std::vector<std::vector<int>> f)
{

	child1 = -1;
	child2 = -1;

	if (type == 1) { // selection based on fitness

		parent1 = f[0][0]; // best candidates
		parent2 = f[1][0];
		int h = f.size();
		child1 = f[h-1][0];
		child2 = f[h-2][0];

	}

	if (type == 2) { // roulette selection

		double aggregation = 0;
		std::vector<double> cum_prob;
		for(int i = 0; i < (int) f.size(); i++ ) {
            if (i == 0) {
                cum_prob.push_back(f[i][1]);
            } else {
                cum_prob.push_back(cum_prob.back()+f[i][1]);
            }
            aggregation += f[i][1];
		}




		std::reverse(cum_prob.begin(),cum_prob.end());
		for (int i=0; i < (int) cum_prob.size(); i++) {
            cum_prob[i] = cum_prob[i]/aggregation;
		}


        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);

        double roulette1 = dis(gen);
      	// check where the ball is in the roulette
		for(int i = 0 ; i <= (int) cum_prob.size()-1; i++) {

            if (cum_prob[i] >= roulette1 && roulette1 >= cum_prob[i+1]) {
                parent1 = f[i][0];
                break;
            }

			if (i== (int) (cum_prob.size()-1)){
                parent1 = f[i+1][0];
                break;
            }

		}



        double roulette2 = dis(gen);

	    for(int i = 0 ; i <= (int) cum_prob.size()-1; i++) {

            if (cum_prob[i] >= roulette2 && roulette2 >= cum_prob[i+1]) {
                parent2 = f[i][0];
                break;
            }

			if (i==(int) (cum_prob.size()-1)){
                parent2 = f[i+1][0];
                break;
            }

		}



		for(int i = f.size() - 1 ; i > 0; i--){
			if((f[i][0] != parent1) && (f[i][0] != parent2) && (child2 != f[i][0])){
				child1 = f[i][0];
				child2 = f[i-1][0];

			}
			if ((child1 != -1) && (child2 != -1))	break;
		}



	}

	if (type == 3) { //selection by tournament

		// percentage of candidates which enter the tourna,enmt
		int n_candidates = std::floor((double)f.size() * tournament_size / 100);

		// random selection of candidates
		int i1 = std::rand()%n_candidates;
		int i2 = std::rand()%n_candidates;

		parent1 = f[i1][0];
		parent2 = f[i2][0];


		int N = f.size() - 1;
		for(int i = N ; i > 0; --i){
			if((f[i][0] != parent1) && (f[i][0] != parent2)){
				child1 = f[i][0];
				child2 = f[i-1][0];
				break;
			}



		}


	}
}
