#ifndef VIEWER_3D_H
#define VIEWER_3D_H

#include <stdio.h>
#include <regex.h>
#include <string.h>

#define MAX_STR_LENGTH 500

#define ERROR_FALSE 0
#define ERROR_TRUE 1


typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct data {
	unsigned int count_of_vertexes;
    unsigned int count_of_facets;
    matrix_t matrix_3d;
} data;


int check_obj(char *file_name, data *viewer_struct);
int regex_compiler(char *pattern, regex_t *re);


#endif  // VIEWER_3D_H