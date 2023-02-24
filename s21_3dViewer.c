#include "s21_3dViewer.h"

/*
  make_matrix
  Что делает: создаёт матрицу; 
*/
// !! ДОБАВИТЬ ЗАЩИТУ КАЛЛОКА !!
void make_matrix(data *viewer_struct) {
  viewer_struct->matrix_3d.rows = viewer_struct->count_of_vertexes + 1;
  viewer_struct->matrix_3d.cols = 3;

  viewer_struct->matrix_3d.matrix = (double **) calloc(viewer_struct->matrix_3d.rows, sizeof(double *));
  for (int i = 0; i < viewer_struct->matrix_3d.rows; i++) {
    viewer_struct->matrix_3d.matrix[i] = (double *) calloc(viewer_struct->matrix_3d.cols, sizeof(double));
  }
}

/*
  destroy_matrix
  Что делает: удаляет матрицу; 
*/
void destroy_matrix(data *viewer_struct) {
  for (int i = 0; i < viewer_struct->matrix_3d.rows; i++) {
    free(viewer_struct->matrix_3d.matrix[i]);
  }
  free(viewer_struct->matrix_3d.matrix);
}

/*
  make_facets_arr
  Что делает: создаёт массив структур; 
*/
void make_facets_arr(data *viewer_struct) {
  viewer_struct->polygons = (polygon_t *) calloc(viewer_struct->count_of_facets + 1, sizeof(polygon_t));
}

void destroy_facets_arr(data *viewer_struct) {
  for (unsigned int i = 0; i < viewer_struct->count_of_facets + 1; i++) {
    free(viewer_struct->polygons[i].vertexes);
  }
  free(viewer_struct->polygons);
}

/*
  get_facets_count
  Что делает: считает количество граней в строке; 
  Возвращаемое значение: количество граней в строке.
*/
int get_facets_count(char *str) {
  int result = 0;
  str++;
  char temp[MAX_STR_LENGTH] = {0};
  strcat(temp, str);
  char *strtok_str = strtok(temp, " ");
  while (strtok_str != NULL) {
    result++;
    strtok_str = strtok(NULL, " ");
  }
  return result;
}

/*
  make_normal_facet
  Что делает: записывает грани в структуру (массив); 
*/
void add_facets_to_arr(polygon_t *facet, char *str) {
  facet->numbers_of_vertexes_in_facets = get_facets_count(str);
  facet->vertexes = (int *) calloc(facet->numbers_of_vertexes_in_facets, sizeof(int));

  char *temp = strtok(str, "f ");
  int count = 0;
  while (temp != NULL) {
    facet->vertexes[count++] = atoi(temp);
    temp = strtok(NULL, " ");
  }
}

/*
  s21_viewer
  Что делает: основная функция, объединяет все остальные функции; 
  Возвращаемое значение: статус.
*/
int s21_viewer(char *file_name, data *viewer_struct) {
  int status = check_obj(file_name, viewer_struct);
  if (status == ERROR_FALSE) {
    make_matrix(viewer_struct);
    make_facets_arr(viewer_struct);
    FILE *file = fopen(file_name, "r");
    char buffer[MAX_STR_LENGTH] = {0};
    int v_count = 1;
    int f_count = 1;
    while (fgets(buffer, MAX_STR_LENGTH, file) != NULL && status == ERROR_FALSE) {
      if (buffer[0] == 'v') {
        sscanf(buffer, "v %lf %lf %lf", &viewer_struct->matrix_3d.matrix[v_count][0], &viewer_struct->matrix_3d.matrix[v_count][1], &viewer_struct->matrix_3d.matrix[v_count][2]);
        v_count++;
      }
      else if (buffer[0] == 'f') {
        add_facets_to_arr(&(viewer_struct->polygons[f_count]), buffer);
        f_count++;
      }
    }
    fclose(file);
    // print_struct(viewer_struct);
  }
  return status;
}


// ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ПРИНТА ВСЕХ ВЕРШИН И ГРАНЕЙ
// УДАЛИТЬ КОГДА ЗАКОНЧИМ

// void print_struct(data *viewer_struct) {
//   printf("\n");
//     for (int i = 1; i < viewer_struct->matrix_3d.rows; i++) {
//       printf("v %lf %lf %lf\n", viewer_struct->matrix_3d.matrix[i][0], viewer_struct->matrix_3d.matrix[i][1], viewer_struct->matrix_3d.matrix[i][2]);
//     }
//     printf("\n");

//     for (unsigned int i = 1; i < viewer_struct->count_of_facets + 1; i++) {
//       printf("f ");
//       for (int j = 0; j < viewer_struct->polygons[i].numbers_of_vertexes_in_facets; j++) {
//         printf("%d ", viewer_struct->polygons[i].vertexes[j]);
//       }
//       printf("\n");
//     }
// }

int main() {
  data viewer_struct = {0};
  int status = s21_viewer("test.obj", &viewer_struct);
  if (status == ERROR_FALSE) {
    destroy_matrix(&viewer_struct);
    destroy_facets_arr(&viewer_struct);
  }
}
