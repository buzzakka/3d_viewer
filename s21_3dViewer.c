#include "s21_3dViewer.h"

// void init_struct(data *viewer_struct) {
//   viewer_struct->count_of_facets = 0;
//   viewer_struct->count_of_vertexes = 0;
// }

int main() {
  data viewer_struct = {0};
  int status = check_obj("test.obj", &viewer_struct);
  if (status == ERROR_FALSE) {
    
  }
  if (!status) printf("count_of_vertexes = %u\t count_of_facets = %u\n", viewer_struct.count_of_vertexes, viewer_struct.count_of_facets);
}
