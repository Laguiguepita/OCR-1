#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

int isAvailable(double puzzle[], int row, int col, int num);
int fillSudoku(double puzzle[], int row, int col);
int matrix_to_file(double matrix[], int size);
void file_to_matrix(char path[], double *pointer);


#endif