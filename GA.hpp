#ifndef GA_HPP_INCLUDED
#define GA_HPP_INCLUDED

#include "Utils.hpp"
#include "sudoku.hpp"

class GA
{

	int pob_ini;
	double prob_mut;
	double prob_co;
	int stop_condition;
	int parent_selection;
	int tourn_size;
	int type_co;
	int points_co;
	int type_mut;
	double elitism;
	int generations;

    bool print_on = true;
    int gen_sol = 0;

    std::vector< std::vector<int>> base_case;

	std::vector<sudoku> population;
	std::vector<sudoku> population_child;
	std::vector<sudoku> population_comb;

	std::vector<std::vector<int>> fitness;
    std::vector<std::vector<int>> fitness_child;


	std::vector<int> best_fit;

public:
	//constructors
	GA();
	GA(std::vector< std::vector<int>> cb);
	GA(std::vector< std::vector<int>> cb,const struct inputs in);


	//destructor
	virtual ~GA();

	//random population init
	void init();


	//algorithm
	void evolve();

	//
	// class interface
	//
	//modificadores
	void pmut(const double p);
	void pcross(const double p);
	void pini(const int p);
	void stop(const int p);
	void sel_parents(const int p);
	void tournament_size(const int p);
	void type_cover(const int p);
	void points_cover(const int p);
	void type_mutacion(const int p);
	void elit(const int p);
	void ngenerations(const int p);
	void set_print_off();
	void set_print_on();



	//selectors
	inputs parameters();
	sudoku individual(const int i);
	int fitness_i(const int i);
	int get_generations();
	std::vector <int> get_bestFit();

};


#endif // GA_HPP_INCLUDED
