#ifndef VIEWER_3D_H
#define VIEWER_3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STR_LENGTH 500

#define ERROR_FALSE 0
#define ERROR_TRUE 1


typedef struct Matrix {
	double **matrix;
	int rows;
	int cols;
} matrix_t;

typedef struct facets {
	int *vertexes;
	int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
	unsigned int count_of_vertexes;
    unsigned int count_of_facets;
    matrix_t matrix_3d;
	polygon_t *polygons;
} data;


int check_obj(char *file_name, data *viewer_struct);
int regex_compiler(char *pattern, regex_t *re);

void make_matrix(data *viewer_struct);
void destroy_matrix(data *viewer_struct);
void make_facets_arr(data *viewer_struct);
void add_facets_to_arr(polygon_t *facet, char *str);
int s21_viewer(char *file_name, data *viewer_struct);
// void print_struct(data *viewer_struct);


#endif  // VIEWER_3D_H