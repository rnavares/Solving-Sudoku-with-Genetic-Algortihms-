#include "CrossOver.hpp"

CrossOver::CrossOver()
{
	type = 1;
	n_points = 1;
}

CrossOver::CrossOver(const int i, const int n)
{
	type = i;
	n_points = n;
}

CrossOver::~CrossOver()
{

}

void CrossOver::setParents(const sudoku p1, const sudoku p2)
{
	parent1 = p1;
	parent2 = p2;

}

sudoku CrossOver::Children(const int i)
{
	if (i == 1) {
        return child1;
	} else {
		return child2;
	}

}

void CrossOver::combine()
{


	if (type == 1 ) { //co 1 point

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 8);

        int r =  dis(gen);

        for (int i=0; i <9; i++) {

            if (i <= r) {
                child1.Update(parent1.getRow(i),i);
                child2.Update(parent2.getRow(i),i);

            } else {
                child1.Update(parent2.getRow(i),i);
                child2.Update(parent1.getRow(i),i);

            }

        }
	}

	if (type == 2 ) { //co 2 points

		std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 8);

        int r1 =  dis(gen);
        int r2 =  dis(gen);

        if (r2<r1) {
            int aux = r1;
            r1 = r2;
            r2 = aux;
        }


        for (int i=0; i <9; i++) {

            if (i>=r1 && i <= r2) {
                child1.Update(parent2.getRow(i),i);
                child2.Update(parent1.getRow(i),i);
            } else {
                child1.Update(parent1.getRow(i),i);
                child2.Update(parent2.getRow(i),i);
            }
        }

	}



}
