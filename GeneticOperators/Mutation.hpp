#ifndef MUTATION_HPP_INCLUDED
#define MUTATION_HPP_INCLUDED

#include <vector>
#include "../sudoku.hpp"

class Mutation {

private:
	int type;
	sudoku mut_sudoku;
public:

	//constructors
	Mutation();
	Mutation(const int t);
	Mutation(const sudoku s);
	Mutation(const int t, const sudoku s);

	virtual ~Mutation();

	//selectors
	int Type();
	sudoku getSudoku();

	//modifiers
	void Type(const int t);
	void setSudoku(const sudoku s);

	void muta();
	void muta_selective();

};


#endif // MUTACION_HPP_INCLUDED
