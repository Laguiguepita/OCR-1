#include <stdio.h>
#include <stdlib.h>
#include "../../include/sudoku_solver/solver.h"

int isAvailable(int sudoku[], int row, int col, int num)
{
	int size = 9;
	int rowStart = (row/3) * 3;
	int colStart = (col/3) * 3;
	for(int i=0; i<size; ++i)
	{
		if (sudoku[row*size+i] == num)
			return 0;
		if (sudoku[i*size+col] == num)
			return 0;
		if (sudoku[(rowStart + (i%3))*size + (colStart + (i/3))] == num)
			return 0;
	}
	return 1;
}

int fillSudoku(int sudoku[], int row, int col)
{
	int size = 9;
	int i;
	if(row<size && col<size)
	{
		if(sudoku[row*size + col] != 0)
		{
			if((col+1)<size) 
				return fillSudoku(sudoku, row, col+1);
			else if((row+1)<size) 
				return fillSudoku(sudoku, row+1, 0);
			else{
				return 1;
			}
		}
		else
		{
			for(i=0; i<size; ++i)
			{
				if(isAvailable(sudoku, row, col, i+1))
				{
					sudoku[row*size + col] = i+1;
					if((col+1)<size)
					{
						if(fillSudoku(sudoku, row, col +1))
							return 1;
						else
						{
							sudoku[row*size + col] = 0;
						}
					}
					else if((row+1)<size)
					{
						if(fillSudoku(sudoku, row+1, 0)) 
							return 1;
						else{
							sudoku[row*size + col] = 0;
						}
					}
					else{
						return 1;
					}
				}
			}
		}
		return 0;
	}
	else{
		return 1;
	}
}


void printSudoku(int sudoku[]) 
{
	int size = 9;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			printf("%d ", sudoku[i*size + j]);
		}
		printf("\n");
	}
	printf("\n\n");
}


void matrix_to_file(int matrix[], char *path) 
{
	FILE * fp;
	char end[] = ".result";
	char *temp = path;
	int i =0;
	while(*(temp+i)!='\0')
	{
		i++;
	}
	i+=7;
	char final[i];
	for(int j = 0; j<i-7;j++)
	{
		final[j]= path[j];
	}
	for(int k = 0;k<7;k++)
	{
		final[i-7+k]=end[k];
	}
	fp = fopen(final, "w");
	int n=matrix[0];
	fprintf(fp,"%d",n);
		for (int i =1; i < 81; i++)
		{
			
			n = matrix[i];
			if(i==80)
			{
				fprintf(fp, "%d", n);
			}
			else if(i%27==26)
			{
				fprintf(fp, "%d\n\n", n);
			}
			else if(i%9 ==8){
				fprintf(fp, "%d\n", n);
			}
			else if(i%3==2)
			{
				fprintf(fp, "%d ", n);
			}
			else
			{
				fprintf(fp, "%d", n);
			}
		}
		fclose(fp);
	}


void file_to_matrix(char *path, int *matrice)
{
	int n=0;
	int i = 0;
	char c;
	char s[3];
	int j;
	
	FILE* fp = fopen(path,"r");
	
	
	
	for(int k = 0;k<27;k++)
	{
		fscanf(fp,"%s",s);
		j =0;
		while (*(s+j)!='\0')
		{
			c =*(s+j);
			n=-1;
			if (c>='1'&&c<='9')
			{
				n=c-48;
			}
			else if (c=='.')
			{
				n=0;
			}
			if(n>-1){
				matrice[i] = n;
				i++;
			}
			j++;
		}
	}
	fclose(fp);
}



int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("main: please input one file name\n");
	}
	else
	{
		char *path = argv[1];
		int* sudoku= calloc(81, sizeof(int));
		file_to_matrix(path, sudoku);
		
		if(fillSudoku(sudoku, 0, 0))
		{
			//matrix_to_file(sudoku,path);
			printSudoku(sudoku);
		}
		else{
			printf("Invalid Sudoku\n");
		}
		free(sudoku);
	}
	return 0;

}
