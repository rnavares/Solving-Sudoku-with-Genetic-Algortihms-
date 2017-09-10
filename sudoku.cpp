#include "sudoku.hpp"
#include <fstream>

sudoku::sudoku() { // default constructor

    std::vector<int> row;

    // build a vector with 0..9 ints
    for (int i=0;i<9;i++) {
         row.push_back(i+1);
    }

    std::random_device rd;
    std::mt19937 g(rd());


   for (int i = 0; i < 9; i++) {
       std::shuffle(row.begin(), row.end(), g); // shuffle randomly the row
       board.push_back(row);
   }

}

sudoku::sudoku(const sudoku& s) { // copy constructor

    board = s.board;
    board_initial = s.board_initial;
}

sudoku::sudoku(std::vector<std::vector<int>> t){ // build from a initial board

    board_initial = t;

    std::vector<int> row;

    for (int i=0;i<9;i++) {
         row.push_back(i+1);
    }

    std::random_device rd;
    std::mt19937 g(rd());


   for (int i = 0; i < 9; i++) {
        std::shuffle(row.begin(), row.end(), g);
        board.push_back(row);
        AdjustRow(i);

   }

}

sudoku::~sudoku() {}; // destructor


// SELECTORS

std::vector<int> sudoku::getRow(int i){

    std::vector<int> v;

    for (int j = 0 ; j < 9; j++) {
        v.push_back(board[i][j]);
    }

    return v;
}


std::vector<int> sudoku::getColumn(int i){
    std::vector<int> v;

    for (int j = 0 ; j < 9; j++) {
        v.push_back(board[j][i]);
    }

    return v;
}

std::vector<std::vector<int>> sudoku::getBoardInitial(){
    return board_initial;
}

std::vector<std::vector<int>> sudoku::getBoard(){
    return board;
}

int sudoku::getFitness() {

    int fit_col=0;
    for (int i = 0; i<9 ; i++) {
        std::vector<int> v = getColumn(i);
        std::sort(v.begin(),v.end());
        auto last = std::unique(v.begin(),v.end());
        v.erase(last,v.end());
        fit_col = fit_col + std::abs(9 - v.size());
        v.clear();

    }

    int fit_row=0;
    for (int i = 0; i<9 ; i++) {
        std::vector<int> v = getRow(i);
        std::sort(v.begin(),v.end());
        auto last = std::unique(v.begin(),v.end());
        v.erase(last,v.end());
        fit_row = fit_row + std::abs(9 - v.size());
        v.clear();

    }

    int fit_square = 0;
    for (int i=0; i <=6; i=i+3){
        for (int j=0; j <=6; j=j+3) {
            std::vector<int> v {board[i][j], board[i+1][j], board[i+2][j],
            	board[i][j+1], board[i+1][j+1], board[i+2][j+1], board[i][j+2],
				board[i+1][j+2],board[i+2][j+2]};
            auto last = std::unique(v.begin(),v.end());
            v.erase(last,v.end());
            fit_square = fit_square + std::abs(9 - v.size());
            v.clear();
        }

    }

    return fit_col + fit_row + fit_square;
}


// MODIFIERS


void sudoku::AdjustRow(int i){

    for (int j = 0; j<9; j++){
        if(board_initial[i][j] != 0) {
            int member = board[i][j];

            for(int k=0; k<9; k++) {
                if (board[i][k] == board_initial[i][j]) {
                    board[i][k] = member;
                    break;
                }
            }

            board[i][j] = board_initial[i][j];
        }

    }

}

void sudoku::Update(std::vector<int> r,const int i){

    for (int j=0; j<9; j++) {
        board[i][j] = r[j];
    }

}

void sudoku::SetBoard(std::vector<std::vector<int>> t){

    for (int i = 0; i < 9 ; i++) {
        for (int j=0; j<9; j++) {
            board[i][j] = t[i][j];
        }
    }

}



// AUXILIARY FUNCTIOND
bool sudoku::isData(int row, int column, int n){

    if (board_initial[row][column] == n) {
        return true;
    } else {
        return false;
    }
}

bool sudoku::isDataRow(int row, int n){

    int flag = 0;

    for (int i = 0; i<9; i++) {
            if(board_initial[row][i] == n) {
                flag = 1;
            }
    }

    if (flag == 1) {
        return true;
    } else {
        return false;
    }
}

bool sudoku::isDataColumn(int column, int n){

    int flag = 0;

    for (int i = 0; i<9; i++) {
            if(board_initial[i][column] == n) {
                flag = 1;
            }
    }

    if (flag == 1) {
        return true;
    } else {
        return false;
    }
}


bool sudoku::isRepeatedRow(int row, int n) {

    std::vector<int> hit{0,0,0,0,0,0,0,0,0};

    for(int j=0; j < 9; j++) {
         int member = board[row][j];
         hit[member-1] = hit[member-1] + 1;
    }

    if (hit[n-1] > 1) {
        return true;
    } else {
        return false;
    }
}

bool sudoku::isRepeatedColumn(int column, int n) {

    std::vector<int> hit{0,0,0,0,0,0,0,0,0};

    for(int j=0; j < 9; j++) {
         int member = board[j][column];
         hit[member-1] = hit[member-1] + 1;
    }

    if (hit[n-1] > 1) {
        return true;
    } else {
        return false;
    }
}

bool sudoku::isRepeatedBox(int row, int column, int n){

    std::vector<int> hit{0,0,0,0,0,0,0,0,0};

    for (int i = row ; i < (row+3); i++) {
        for (int j = column; j < (column+3); j++) {
            int member = board[i][j];
            hit[member-1] = hit[member-1] + 1;
        }
    }

    if (hit[n-1] > 1) {
        return true;
    } else {
        return false;
    }

}


std::vector<int> sudoku::rowsRepeatedColumn(int column, int n) {

    std::vector<int> rows;

    for(int j=0; j < 9; j++) {
         if(board[j][column] == n) {
            rows.push_back(j);
         }
    }
    return rows;
}


int sudoku::sumRow(int i){

    int sum=0;

    for (int j = 0 ; j < 9; j++) {
       sum = sum + board[i][j];
    }

    return sum;
}

int sudoku::sumColumn(int i){
    int sum=0;

    for (int j = 0 ; j < 9; j++) {
       sum = sum + board[j][i];
    }

    return sum;
}



void sudoku::CheckBox(int row, int column) {


   for (int i = row; i < (row+3); i++) {
        for (int j = column; j < (column+3); j++) {
            int member = board[i][j];

             if (!isData(i,j,member)) {


                  if(isRepeatedColumn(i,member)) {
                        for(int candidate=1;candidate<=9;candidate++) {

                                 if(!isRepeatedColumn(j,candidate)  && !isRepeatedBox(row,column,candidate) ){

                                    if(!isDataRow(i,candidate) && !isDataColumn(j,candidate)) {

                                        for (int k=0; k<9;k++) { //swap
                                            if(candidate == board[i][k]) {
                                                board[i][k] = member;
                                                board[i][j] = candidate;
                                                break;
                                            }

                                        }
                                        break;
                                    }


                                }
                        }
                  }

                  if(isRepeatedBox(row,column,member)) {
                        for(int candidate=1;candidate<=9;candidate++) {

                               if(!isRepeatedColumn(j,candidate)  && !isRepeatedBox(row,column,candidate) ){

                                     if(!isDataRow(i,candidate) && !isDataColumn(j,candidate)) {

                                        for (int k=0; k<9;k++) { //swap
                                            if(candidate == board[i][k]) {
                                                board[i][k] = member;
                                                board[i][j] = candidate;
                                                break;
                                            }

                                        }
                                        break;
                                    }

                                }
                        }
                  }

            }

        }
    }


}

void sudoku::clear_grid(){
    board.clear();
}

void sudoku::print() {

    std::cout<<"\n\n";
    for (int i=0; i < 9; i++ ) {
        for (int j=0; j< 9; j++) {
            std::cout<< board[i][j] <<" ";
            if ((j+1)%3 == 0) {std::cout<<" ";}
        }
        std::cout<<"\n";
        if ((i+1)%3 == 0) {std::cout<<"\n";}
    }
    std::cout<<"\n";
}

void sudoku::print_file() {

   std::ofstream fid;
   fid.open("solucion.txt");


   for (int i=0; i < 9; i++ ) {
        for (int j=0; j< 9; j++) {
            fid<< board[i][j] <<" ";
            if ((j+1)%3 == 0) {fid<<" ";}
        }
        fid<<"\n";
        if ((i+1)%3 == 0) {fid<<"\n";}
    }
    fid<<"\n";

   fid.close();
}



void sudoku::print_initial() {

    std::cout<<"\n\n";
    for (int i=0; i < 9; i++ ) {
        for (int j=0; j< 9; j++) {
            std::cout<< board_initial[i][j] <<" ";
            if ((j+1)%3 == 0) {std::cout<<" ";}
        }
        std::cout<<"\n";
         if ((i+1)%3 == 0) {std::cout<<"\n";}
    }
    std::cout<<"\n";
}
