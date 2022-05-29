#ifndef FROM_N_TO_S_H
#define FROM_N_TO_S_H


struct list
{
	char name[6];
};




struct list *cell_to_list(char path[]);
double* auxiliaire(char path[]);
void matrix_to_file(int matrix[], char *path);
void list_to_file(struct list *list, int matrix[]);
void main_from();

#endif
