#include "s21_3dViewer.h"

// void init_struct(data *viewer_struct) {
//   viewer_struct->count_of_facets = 0;
//   viewer_struct->count_of_vertexes = 0;
// }

// ДОБАВИТЬ ЗАЩИТУ КАЛЛОКА
void make_matrix(data *viewer_struct) {
  viewer_struct->matrix_3d.rows = viewer_struct->count_of_vertexes + 1;
  viewer_struct->matrix_3d.cols = 3;

  viewer_struct->matrix_3d.matrix = (double **) calloc(viewer_struct->matrix_3d.rows, sizeof(double *));
  for (int i = 0; i < viewer_struct->matrix_3d.rows; i++) {
    viewer_struct->matrix_3d.matrix[i] = (double *) calloc(viewer_struct->matrix_3d.cols, sizeof(double));
  }
}

void destroy_matrix(data *viewer_struct) {
  viewer_struct->matrix_3d.rows = 0;
  viewer_struct->matrix_3d.cols = 0;
  for (int i = 0; i < viewer_struct->matrix_3d.rows; i++) {
    free(viewer_struct->matrix_3d.matrix[i]);
  }
}

int main() {
  data viewer_struct = {0};
  int status = check_obj("test.obj", &viewer_struct);
  if (status == ERROR_FALSE) {

  }
  if (!status) printf("count_of_vertexes = %u\t count_of_facets = %u\n", viewer_struct.count_of_vertexes, viewer_struct.count_of_facets);
}
