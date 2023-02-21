CC = gcc
CFLAGS = -Wall -Werror -Wextra
C11 = -std=c11

all: rebuild

build: s21_3dViewer

s21_3dViewer: 
	$(CC) $(CFLAGS) $(C11) s21_*.c -o s21_3dViewer


test: clean s21_3dViewer.a
	gcc -fsanitize=address -lcheck test.c s21_3dViewer.a -o test.out && ./test.out

# Для корректной работы установи lcov: brew install lcov
gcov_report: coverage run_coverage lcov genhtml open

coverage:
	gcc --coverage test.c  -o test -lcheck
run_coverage:
	./test
lcov:
	lcov -t "Core" -o s21_test.info -c -d .
genhtml:
	genhtml -o report s21_test.info
open:
	open ./report/index.html


s21_3dViewer.a: s21_3dViewer.o
	ar rc s21_3dViewer.a s21_*.o

# TODO: подумать, можно ли компилить в общий .o файл
s21_3dViewer.o:
	gcc -c $(FLAGS) s21_*.c


clean:
	rm -rf s21_3dViewer *.o *.a *.info *.gcda *.gcno *.out test report/

rebuild: clean build
