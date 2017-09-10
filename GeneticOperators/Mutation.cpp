#include "Mutation.hpp"
#include <iostream>

//constructores
Mutation::Mutation()
{
	type = 0;
}

Mutation::Mutation(const int t)
{
	type = t;
}

Mutation::Mutation(const sudoku s)
{
	type = 0;
	mut_sudoku = s;
}

Mutation::Mutation(const int t,const sudoku s)
{
	type = t;
	mut_sudoku = s;
}

//destructor
Mutation::~Mutation()
{ mut_sudoku.clear_grid();}


//selectores
int Mutation::Type()
{
	return type;
}

sudoku Mutation::getSudoku()
{
	return mut_sudoku;
}

//modificadores
void Mutation::Type(const int t)
{
	type = t;
}

void Mutation::setSudoku(const sudoku s)
{
	mut_sudoku = s;
}


void Mutation::muta()
{


	if(type == 1) {   //swap mutation E.Eiben "Into to EC" pg 45

		std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 8);

        int ran1 =  dis(gen);
        int ran2 =  dis(gen);

        int maxLOOP = 0;

        while (ran2 == ran1) { // avoid same candidate
                ran2 = dis(gen);
                maxLOOP += 1;
                if (maxLOOP > 500) 	break;

        }

        int ranRow =  dis(gen);

        std::vector<int> row = mut_sudoku.getRow(ranRow);
        std::shuffle(row.begin(), row.end(), gen);
        //swap
        //int aux = row[ran1];
        //row[ran1] = row[ran2];
        //row[ran2] = aux;

        mut_sudoku.Update(row,ranRow);
        mut_sudoku.AdjustRow(ranRow);

	}

	if (type == 2) { //insert mutation

		std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 8);

        int ran1 =  dis(gen);
        int ran2 =  dis(gen);

        int maxLOOP = 0;

		while (ran2 == ran1) { // avoid same candidate
			ran2 = dis(gen);
			maxLOOP += 1;
			if (maxLOOP > 500) 	break;

		}

		if (ran1 > ran2) { //swap
			int aux = ran1;
			ran1 = ran2;
			ran2 = aux;
		}

		int ranRow =  dis(gen);
		std::vector<int> row = mut_sudoku.getRow(ranRow);
        std::vector<int> mutated;

		for(int i = 0; i < (int) row.size();i++) {
			if(i == ran1) {
				mutated.push_back(row[i]);
				mutated.push_back(row[ran2]);
			} else {

				if(i != ran2) {
					mutated.push_back(row[i]);
				}

			}
		}

		mut_sudoku.Update(mutated,ranRow);
		mut_sudoku.AdjustRow(ranRow);

	}


}


void Mutation::muta_selective()
{


    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 8);

    std::vector<int> rows;

    int column = -1;
    int member = -1;

    int flag = 0;
    for (int col = 0; col < 9; col++) {
            for (int data =1; data <= 9; data++) {
                if (mut_sudoku.isRepeatedColumn(col,data)) {
                    rows = mut_sudoku.rowsRepeatedColumn(col,data);
                    flag = 1;
                    column = col;
                    member = data;
                    break;
                }
            }
            if (flag == 1) {
                break;
            }
    }

    if (rows.size() > 0) {

        for (int i = 0; i < (int)rows.size(); i++) {

            if (!mut_sudoku.isData(rows[i],column,member) && column != -1 && member != -1) {
                std::vector<int> f = mut_sudoku.getRow(rows[i]);
                std::shuffle(f.begin(), f.end(), gen);

                mut_sudoku.Update(f,rows[i]);
                mut_sudoku.AdjustRow(rows[i]);
            }

        }

    }
}
