#ifndef SELECTION_HPP_INCLUDED
#define SELECTION_HPP_INCLUDED

#include <vector>

class Selection
{
private:
	int type;
	double elitism;
	int parent1; // parent indices
	int parent2;
	int child1;
	int child2;
	int tournament_size;


public:
	//constructors
	Selection();
	Selection(const int t, const double e, const int size);

	virtual ~Selection();

	//selectors
	int parent(const int i);
	int child(const int i);

	void select(std::vector<std::vector<int>> f);

};


#endif // SELECCION_HPP_INCLUDED
