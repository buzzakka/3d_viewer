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

// УДАЛЕНИЕ МАТРИЦЫ
void destroy_matrix(data *viewer_struct) {
  viewer_struct->matrix_3d.rows = 0;
  viewer_struct->matrix_3d.cols = 0;
  for (int i = 0; i < viewer_struct->matrix_3d.rows; i++) {
    free(viewer_struct->matrix_3d.matrix[i]);
  }
}

// СОЗДАНИЕ МАССИВА СТРУКТУР
void make_struct_arr(data *viewer_struct) {
  viewer_struct->polygons = (polygon_t *) calloc(viewer_struct->count_of_facets + 1, sizeof(polygon_t));
}

int get_facets_count(char *str) {
  int result = 0;
  char *strtok_str = strtok(str, "f ");
  while (strtok_str != NULL) {
    result++;
    strtok_str = strtok(NULL, " ");
  }
  return result;
}

int main() {
  data viewer_struct = {0};
  int status = check_obj("test.obj", &viewer_struct);
  if (status == ERROR_FALSE) {
    make_matrix(&viewer_struct);
    make_struct_arr(&viewer_struct);
    FILE *file = fopen("test.obj", "r");
    char buffer[MAX_STR_LENGTH] = {0};
    int v_count = 1;
    // int f_count = 1;
    while (fgets(buffer, MAX_STR_LENGTH, file) != NULL && status == ERROR_FALSE) {
      if (buffer[0] == 'v') {
        sscanf(buffer, "v %lf %lf %lf", &viewer_struct.matrix_3d.matrix[v_count][0], &viewer_struct.matrix_3d.matrix[v_count][1], &viewer_struct.matrix_3d.matrix[v_count][2]);
        v_count++;
      }
      else if (buffer[0] == 'f') {
        viewer_struct.polygons->numbers_of_vertexes_in_facets = get_facets_count(buffer);
        viewer_struct.polygons->vertexes = (int *) calloc(viewer_struct.polygons->numbers_of_vertexes_in_facets + 1, sizeof(int));
      }
    }
  }
  if (!status) {
    for (int i = 1; i < viewer_struct.matrix_3d.rows; i++) {
      printf("%lf %lf %lf\n", viewer_struct.matrix_3d.matrix[i][0], viewer_struct.matrix_3d.matrix[i][1], viewer_struct.matrix_3d.matrix[i][2]);
    }
    printf("%d", viewer_struct.polygons->numbers_of_vertexes_in_facets);
  }
}
