#include <stdio.h>
#include <stdlib.h>
#include "../../include/sudoku_solver/sudoku_solver.h"

int isAvailable(double puzzle[], int row, int col, int num)
{
        int rowStart = (row/3) * 3;
        int colStart = (col/3) * 3;
        
        for(int i=0; i<9; ++i)
        {
                if (puzzle[row*9+i] == num)
                        return 0;
                if (puzzle[i*9+col] == num)
                        return 0;
                if (puzzle[(rowStart + (i%3))*9 + (colStart + (i/3))] == num)
                        return 0;
        }
        return 1;
}

int fillSudoku(double puzzle[], int row, int col)
{
        int i;
        if(row<9 && col<9)
        {
                if(puzzle[row*9 + col] != 0)
                {
                        if((col+1)<9) 
                                return fillSudoku(puzzle, row, col+1);
                        else if((row+1)<9) 
                                return fillSudoku(puzzle, row+1, 0);
                        else 
                                return 1;
                }
                else
                {
                        for(i=0; i<9; ++i)
                        {
                                if(isAvailable(puzzle, row, col, i+1))
                                {
                                        puzzle[row*9 + col] = i+1;
                                        if((col+1)<9)
                                        {
                                                if(fillSudoku(puzzle,row,col+1)) 
                                                        return 1;
                                                else 
                                                        puzzle[row*9 + col] = 0;
                                        }
                                        else if((row+1)<9)
                                        {
                                                if(fillSudoku(puzzle, row+1, 0)) 
                                                        return 1;
                                                else 
                                                        puzzle[row*9 + col] = 0;
                                        }
                                        else 
                                                return 1;
                                }
                        }
                }
                return 0;
        }
        else 
                return 1;
}

void printSudoku(double matrix[]) {
        
        int size = 9;
        
        for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                        printf("%g ", matrix[i*size + j]);
                }
                printf("\n");
        }
        
        printf("\n\n");
        
}


int matrix_to_file(double matrix[], int size) 
{
        FILE * fp;
        fp = fopen("filled_matrix.txt", "a");
        
        int n;
        
        for (int i = 0; i < size*size; i++)
                {
                        n = (int)matrix[i];
                        fprintf(fp, "%d\n", n);
                }
        
        fclose(fp);
        return 0;
}


void file_to_matrix(char path[], double *pointer) {
        
        
        int n;
        FILE * fp;
        fp = fopen(path, "r");
        
        //int size = 9;
        //double matrice[size*size];
        
        //for (int j = 0; j < size*size; j++)
        //        matrice[j] = 0;
        
        
        int i = 0;
        
        while (!feof(fp))
                {
                        
                        fscanf(fp, "%d", &n);
                        
                        pointer[i] = (double)n;
                        
                        i++;
                }
        fclose(fp);
        
}



int main(int argc, char *argv[])
{       
        if (argc != 2) {
                printf("main: file1");
        }
        
        int size = 9;
        
        double pointer[81];
        for (int j = 0; j < size*size; j++)
                pointer[j] = 0;

        
        file_to_matrix(argv[1], pointer);

        
        
        if(fillSudoku(pointer, 0, 0))
                matrix_to_file(pointer, 9);
        
        else
                printf("pas de solution");
        
        //free(pointer);
        
        return 0;
}
