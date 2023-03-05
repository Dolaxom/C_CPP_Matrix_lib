CC=g++ -std=c++17 -Wall -Werror -Wextra -pedantic -g
GCOV=--coverage
OUTNAME = "tests"

all: cleanall style s21_matrix_oop.a test gcov_report clean
.PHONY : all

s21_matrix_oop.a:
	$(CC) -c s21_matrix_oop.cpp -o matrix_oop.o
	ar rcs matrix_oop.a matrix_oop.o
.PHONY : s21_matrix_oop.a

test: clean
	$(CC) $(GCOV) -c s21_matrix_oop.cpp 
	$(CC) -c s21_tests.cpp -lgtest
	$(CC) $(GCOV) -o $(OUTNAME) s21_tests.o s21_matrix_oop.o -lgtest
	./$(OUTNAME)
.PHONY : clean

style_fix:
	clang-format -i *.cpp *.h
.PHONY : style_fix

style:
	clang-format -n *.cpp *.h
.PHONY : style

gcov_report: test
	lcov -t "Unit-tests of matrix_oop" -o s21_matrix_oop.info -c -d .
	genhtml -o gcov_report s21_matrix_oop.info
	open ./gcov_report/index.html
.PHONY : gcov_report

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./gcov_report *.info ./*.info report matrix_test matrix_oop
.PHONY : clean

cleanall: clean
	rm -rf $(OUTNAME)
.PHONY : cleanall

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tests
.PHONY : valgrind
