OUTDIR = $(shell cd ../build && pwd)
UNAME = $(shell uname -s)
CC = gcc -Wall -Werror -Wextra -std=c11
SOURCES_LIB = matrix_lib.o
SOURCES_TEST = matrix_tests.o
OUTNAME = "tests"


ifeq ($(UNAME),Darwin)
	FLAGSS = -lcheck -lm -lpthread -fprofile-arcs
endif
ifeq ($(UNAME),Linux)
	FLAGSS = -lcheck -lsubunit -lrt -lm -lpthread -fprofile-arcs
endif


all: cleanall build clean

build: style s21_matrix.a test gcov_report

rebuild: all

gcov_report:
	gcov -b -l -p -c *.gcno
	gcovr -g -k -r . --html --html-details -o coverage_report.html
##	firefox "coverage_report.html"
##	gcov -a -f *.gcno
##	gcovr --html-details -o coverage_report.html

test: s21_matrix_tests.c $(SOURCES_TEST)
	$(CC) s21_matrix_tests.c $(SOURCES_TEST) $(FLAGSS) -o $(OUTNAME)
	./$(OUTNAME)

s21_matrix.a: $(SOURCES_LIB) s21_matrix.h
	ar -rcs s21_matrix.a $(SOURCES_LIB) s21_matrix.h
	ranlib s21_matrix.a

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c
	clang-format -i *.h

valgrind:
	valgrind --leak-check=full ./tests

clean:
	rm -rf *.o *.a *.so coverage* *.gcno *.gcda *.gcov *.dSYM *.cfg *.py a.out
## ".clang-format"

cleanall: clean
	rm -rf $(OUTNAME) 


#### object files

matrix_lib.o: s21_matrix.c
	$(CC) -c s21_matrix.c -o matrix_lib.o

matrix_tests.o: s21_matrix.c
	$(CC) -c --coverage s21_matrix.c -o matrix_tests.o

app:
	gcc -Wall -Werror -Wextra main.c s21_matrix.c
