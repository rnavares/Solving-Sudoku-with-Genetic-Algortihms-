#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>

class sudoku
{

private:
    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> board_initial;

public:

    //constructs
    sudoku();
    sudoku(std::vector<std::vector<int>> t);
    sudoku(const sudoku& s);

    //destructor
    virtual ~sudoku();

    //selectors
    std::vector<int> getRow(int i);
    std::vector<int> getColumn(int i);
    std::vector<std::vector<int>> getBoardInitial();
    std::vector<std::vector<int>> getBoard();
    int getFitness();

    //modifiers
    void Update(std::vector<int> r, const int i);
    void AdjustRow(int i);
    void SetBoard(std::vector<std::vector<int>> t);


    //auxiliary functions
    bool isData(int row, int column, int n);
    bool isRepeatedRow(int row, int n);
    bool isRepeatedColumn(int column, int n);
    bool isRepeatedBox(int row, int column, int n);
    bool isDataRow(int row, int n);
    bool isDataColumn(int column, int n);

    std::vector<int> rowsRepeatedColumn(int column, int n); //return rows where repeated elements exist
    int sumRow(int i);
    int sumColumn(int i);


    void CheckBox(int row, int column);

    void clear_grid();
    void print();
    void print_file();
    void print_initial();

};


#endif // SUDOKU_HPP_INCLUDED
