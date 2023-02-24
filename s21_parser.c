#include "s21_3dViewer.h"

/*
    - НАДО ДОБАВИТЬ ПРОВЕРКУ ЧТО ЭТО .obj ФАЙЛ
    - В ПАРСЕРЕ ИСПРАВИТЬ РЕГУЛЯРКУ ДЛЯ ГРАНЕЙ
*/

/*
  parser
  Что делает: проходит по файлу, проверяет его на корректность и записывает в структуру количеств вершин и граней; 
  Возвращаемое значение: status - корректен ли файл или нет;
*/
int check_obj(char *file_name, data *viewer_struct) {
  int status = ERROR_FALSE;
  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    status = ERROR_TRUE;
  } else {
    char buffer[MAX_STR_LENGTH] = {0};
    while (fgets(buffer, MAX_STR_LENGTH, file) != NULL && status == ERROR_FALSE) {
      regex_t re;
      char pattern[50] = {0};
      if (buffer[0] == 'v') {
        strcat(pattern, "^v( -?[0-9]+\\.?[0-9]*){3}\n?$");
        regex_compiler(pattern, &re);
        status = regexec(&re, buffer, 0, NULL, 0);
        if (status == ERROR_FALSE) viewer_struct->count_of_vertexes += 1;
      }
      else if (buffer[0] == 'f') {
        strcat(pattern, "^f( -?[0-9]+\\.?[0-9]*){3,}\n?$");   // Надо доработать для файлов со слэшем
        regex_compiler(pattern, &re);
        status = regexec(&re, buffer, 0, NULL, 0);
        if (status == ERROR_FALSE) viewer_struct->count_of_facets += 1;
      }
      else {
        status = ERROR_TRUE;
      }
      regfree(&re);
    }
    fclose(file);
  }
  return status;
}

/*
  regex_compiler
  Что делает: компилирует регулярку; 
  Возвращаемое значение: status - успешна ли компиляция или нет;
*/

int regex_compiler(char *pattern, regex_t *re) {
  int status = regcomp(re, pattern, REG_EXTENDED|REG_ICASE);
  return (status = (status == 0) ? ERROR_FALSE : ERROR_TRUE);
}