#include "GA.hpp"
#include "GeneticOperators/Selection.hpp"
#include "GeneticOperators/Mutation.hpp"
#include "GeneticOperators/CrossOver.hpp"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <math.h>

//constructores y destructor
GA::GA()
{
	pob_ini = 0;
	generations = 0;
	prob_mut = 0.0;
	prob_co = 0.0;
	stop_condition = 0;
	parent_selection = 0;
	tourn_size = 0;
	type_co = 0;
	points_co = 0;
	type_mut = 0;
	elitism = 0.0;

}

GA::GA(std::vector< std::vector<int>> cb)
{
	pob_ini = 0;
	generations = 0;
	prob_mut = 0.0;
	prob_co = 0.0;
	stop_condition = 0;
	parent_selection = 0;
	tourn_size = 0;
	type_co = 0;
	points_co = 0;
	type_mut = 0;
	elitism = 0.0;

	base_case = cb;

}

GA::GA(std::vector< std::vector<int>> cb,const struct inputs in)
{

	pob_ini = in.population_size;
	generations = in.n_generations;
	prob_mut = in.prob_mut;
	prob_co = in.prob_co;
	stop_condition = in.stop_condition;
	parent_selection = in.select_parents;
	tourn_size = in.tournament_size;
	type_co = in.type_co;
	points_co = in.points_co;
	type_mut = in.mutation_type;
	elitism = in.elitism;

	base_case = cb;
}

GA::~GA()
{
	population.clear();

}

//init
void GA::init()
{
	population.clear();
	population_child.clear();
    std::vector<int> line;

	for (int i=0; i < pob_ini; i++) {
        sudoku s(base_case);
        population.push_back(s);
        population_child.push_back(s);
        population_comb.push_back(s);
        line.push_back(i);
        line.push_back(s.getFitness());
        fitness.push_back(line);
        fitness_child.push_back(line);
        line.clear();
        s.clear_grid();
	}

    //sort by fitness
    sort(fitness.begin(),fitness.end(),[](std::vector<int> f1,std::vector<int> f2)->bool{return(f1[1]<f2[1]);}  );
    sort(fitness_child.begin(),fitness_child.end(),[](std::vector<int> f1,std::vector<int> f2)->bool{return(f1[1]<f2[1]);}  );

}


//modifiers
void GA::pcross(const double p)
{
	prob_co = p;
}

void GA::pmut(const double p)
{
	prob_mut = p;
}

void GA::pini(const int p)
{
	pob_ini = p;
}

void GA::stop(const int p)
{
	stop_condition = p;
}

void GA::sel_parents(const int p)
{
	parent_selection = p;
}

void GA::tournament_size(const int p)
{
	tourn_size = p;
}

void GA::type_cover(const int p)
{
	type_co = p;
}

void GA::points_cover(const int p)
{
	points_co = p;
}

void GA::type_mutacion(const int p)
{
	type_mut = p;
}

void GA::elit(const int p)
{
	elitism = p;
}

void GA::ngenerations(const int p)
{
	generations = p;
}

void GA::evolve(){

  double counter = 0.0;
  int i = 0;
  int control_parameter = 1;
  int control_mutationSelective = 0;
  int control_generation = 0;

  while(1) {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, 1);
        int k=0;
        while (k<pob_ini-1) {

            double p =  dis(gen);

            if (p <= prob_co) {

			//
			//CrossOver
			CrossOver CO(type_co,points_co);
			CO.setParents(population[k], population[k+1]);
			CO.combine();											//CO parents

            population_child[k].SetBoard(CO.Children(1).getBoard());
            population_child[k+1].SetBoard(CO.Children(2).getBoard());


			//
			//Mutation
			p = dis(gen);
			if (p <= prob_mut) {					//mutate with probability

                if (control_mutationSelective == 0) {
                    for (int l=1; l<= control_parameter;l++){
                        Mutation mut(type_mut,population_child[k]);  // mutate children 1
                        mut.muta();
                        population_child[k].SetBoard(mut.getSudoku().getBoard());

                        Mutation mut2(type_mut,population_child[k+1]);  // mutate child 2
                        mut.muta();
                        population_child[k+1].SetBoard(mut2.getSudoku().getBoard());
                    }

				} else { // selective mutation

                        Mutation mut(type_mut,population[0]);  // mutamos el primer hijo
                        mut.muta_selective();
                        population_child[k].SetBoard(mut.getSudoku().getBoard());
                        Mutation mut2(type_mut,population[1]);  // mutamos el segundo hijo
                        mut.muta_selective();
                        population_child[k+1].SetBoard(mut2.getSudoku().getBoard());

				}
			}


            //check children
            for (int l=1; l<= control_parameter;l++){
                for (int box_X = 0; box_X <= 6; box_X = box_X+3) {
                    for (int box_Y = 0; box_Y <= 6; box_Y = box_Y+3) {
                        population_child[k].CheckBox(box_X,box_Y);
                        population_child[k+1].CheckBox(box_X,box_Y);
                    }

                }
            }




            fitness_child[k][1] = population_child[k].getFitness();
            fitness_child[k+1][1] = population_child[k+1].getFitness();

            fitness_child[k][0] = k;
            fitness_child[k+1][1] = k+1;

             k= k+2;

            }else{ //direct generation

                population_child[k].SetBoard(population[k].getBoard());
                fitness_child[k][1] = population_child[k].getFitness();
                fitness_child[k][1] = k;
                k=k+1;

            }// end crossover

        }



        //sort by fitness
        sort(fitness_child.begin(),
        		fitness_child.end(),
				[](std::vector<int> f1,std::vector<int> f2)->bool{return(f1[1]<f2[1]);}  );


        k=0;
        int j = 0;
        //new population
        for (int i=0; i <pob_ini; i++) {

             if (i%2 == 0) {
                population_comb[i].SetBoard(population[fitness[k][0]].getBoard());
                k=k+1;

             } else {
                population_comb[i].SetBoard(population_child[fitness_child[j][0]].getBoard());
                j=j+1;

             }
        }

        for (int i=0; i <pob_ini; i++) {
             population[i].SetBoard(population_comb[i].getBoard());
             fitness[i][0] = i;
             fitness[i][1] = population[i].getFitness();
        }

        //sort by fitness
        sort(fitness.begin(),
        		fitness.end(),
				[](std::vector<int> f1,std::vector<int> f2)->bool{return(f1[1]<f2[1]);}  );

		best_fit.push_back(fitness[0][1]);

		//control mutation parameter
        int cont_control = 0;
        if ( i > 50 && i > (control_generation+50)  && control_parameter < 5) {
            for (int k=1; k<=50; k++) {
                if (best_fit[best_fit.size()-1] == best_fit[best_fit.size()-k]) {
                    cont_control ++;
                }
            }
            if (cont_control == 50) {
                    control_generation = i;
                    control_parameter++;

                    if (print_on) {
                        std::cout << "\n** control mutation "<< control_parameter << " **\n";
                    }
            }
        }


        int cont_control_sel = 0;
        if ( i > 300 && control_mutationSelective== 0) {
            for (int k=1; k<=200; k++) {
                if (best_fit[best_fit.size()-1] == best_fit[best_fit.size()-k]) {
                    cont_control_sel ++;
                }
            }
            if (cont_control_sel == 200) {
                    control_mutationSelective=1;
                    if (print_on) {
                        std::cout << "\n** control mutation selective **\n";
                    }
            }
        }


        if (print_on) {
            std::cout << "Generation "<< i + 1 <<":  ";
            std::cout << " Fitness.... " << fitness[0][1] << std::endl;
        }


		//condiciones de parada
		if (stop_condition == 2) {
			if (best_fit[best_fit.size()-1] == best_fit[best_fit.size()-2]) {
				counter += 1;
			} else {
				counter = 0;
			}
			if ( counter == generations ) {
				break;
			}
		} else {
			counter +=1;
			if ( fitness[0][1] == 0 ) {
                gen_sol = i;
				if (print_on) {
                    std::cout << "\nINITIAL SUDOKU: \n";
                    population[fitness[0][0]].print_initial();
                    std::cout << "\nSolution: \n";
                    population[fitness[0][0]].print();
                    std::cout << "\n***Output can be found in solution.txt\n";
                    population[0].print_file();
				}
				break;
			}

			if (i >= generations) {
                if (print_on) {
                    std::cout << "\nINITIAL SUDOKU: \n";
                    population[fitness[0][0]].print_initial();
                    std::cout << "\n Solution: \n";
                    population[0].print();
                    std::cout << "\n***Output can be found in solution.txt\n";
                    population[0].print_file();
                }
                gen_sol = i;
				break;

			}
		}

        i++;

  }



}

std::vector<int> GA::get_bestFit(){
        return best_fit;
}

//selectores
inputs GA::parameters()
{
	inputs parameters;

	parameters.population_size = pob_ini;
	parameters.n_generations = generations;
	parameters.stop_condition = stop_condition;
	parameters.select_parents = parent_selection;
	parameters.tournament_size = tourn_size;
	parameters.type_co = type_co;
	parameters.prob_co = prob_co;
	parameters.points_co = points_co;
	parameters.mutation_type = type_mut;
	parameters.prob_mut = prob_mut;
	parameters.elitism = elitism;

	return parameters;
}

sudoku GA::individual(const int i)
{
	return population[i];
}

int GA::fitness_i(const int i){
	return population[i].getFitness();
}

void GA::set_print_off(){
    print_on = false;
}

void GA::set_print_on(){
    print_on = true;
}

int GA::get_generations() {
        return gen_sol;
}
