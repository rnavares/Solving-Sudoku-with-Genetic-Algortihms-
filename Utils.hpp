#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

//#include "sudoku.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>

struct inputs {

	int population_size;
	int n_generations;
	int stop_condition;
	int initialize;
	int select_parents;
	int tournament_size;
	int type_co;
	double prob_co;
	int points_co;
	int mutation_type;
	double prob_mut;
	double elitism;

	void print() {

		std::cout <<"\nGA PARAMETERS";
		std::cout << "\nPopulation size       :\t" << population_size;
		std::cout << "\nGenerations           :\t" << n_generations;
		std::cout << "\nStop Condition        :\t" << stop_condition;
		std::cout << "\nParents Selection     :\t" << select_parents;
		std::cout << "\nTournament type       :\t" << tournament_size;
		std::cout << "\nType Cross Over       :\t" << type_co;
		std::cout << "\nProb. Cross Over      :\t" << prob_co;
		std::cout << "\nPoints Cross Over     :\t" << points_co;
		std::cout << "\nTypeo Mutation        :\t" << mutation_type;
		std::cout << "\nProb. Mutation        :\t" << prob_mut;
		std::cout << "\nElitism               :\t" << elitism;
	};
};


// Read file which contains the sudoku
std::vector< std::vector<int>> read_file(std::string F);
// Read the parameters file
inputs read_parameters(std::string F);




#endif // UTILS_HPP_INCLUDED
