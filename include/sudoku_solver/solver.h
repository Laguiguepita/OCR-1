#ifndef SOLVER_H
#define SOLVER_H




int isAvailable(int sudoku[], int row, int col, int num);
int fillSudoku(int sudoku[], int row, int col);
void printSudoku(int sudoku[]);
void matrix_to_file(int matrix[],char *path);
void file_to_matrix(char *path, int *matrice);
void main_solver();


#endif
