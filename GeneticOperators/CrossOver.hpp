#ifndef CROSSOVER_HPP_INCLUDED
#define CROSSOVER_HPP_INCLUDED

#include <vector>
#include <iostream>
#include "../sudoku.hpp"

class CrossOver
{

private:
	int type;
	int n_points;

	sudoku child1;
	sudoku child2;
	sudoku parent1;
	sudoku parent2;

public:
	CrossOver();
	CrossOver(const int i, const int n);

	virtual ~CrossOver();

	void setParents(const sudoku p1, const sudoku p2);

	sudoku Children(const int i);

	void combine();

};


#endif // CROSSOVER_HPP_INCLUDED
