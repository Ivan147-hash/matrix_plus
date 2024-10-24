G++ = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
LINKFLAGS = -lstdc++ -lm
GCOV_LIBS = --coverage
TST_LIBS = -lgtest -lm -g

SRC = s21_matrix_oop.cpp 
TEST_SRC = test.cpp

TEST_OUTPUT = test
GCOV_OUTPUT = ./gcov/gcov_test

ifeq ($(OS), Darwin)
	GTEST_FLAGS = -I/opt/homebrew/opt/googletest/include -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread
	OPEN_CMD = open
	LCOV_FLAG = --ignore-errors inconsistent
else
	GTEST_FLAGS = -I/usr/include/gtest -L/usr/lib -lgtest -lgtest_main -pthread
	OPEN_CMD = xdg-open
	LCOV_FLAG = --ignore-errors mismatch
endif

all: clean test

s21_matrix_oop.a:
	$(G++) $(CFLAGS) -c $(SRC) -o s21_matrix_oop.o
	ar rcs libs21_matrix_oop.a s21_matrix_oop.o
	ranlib libs21_matrix_oop.a

test: s21_matrix_oop.a
	$(G++) $(CFLAGS) $(TEST_SRC) -o $(TEST_OUTPUT) $(GTEST_FLAGS) $(LINKFLAGS) -L. -ls21_matrix_oop
	./$(TEST_OUTPUT)

gcov_report: clean
	$(G++) -fprofile-arcs -ftest-coverage $(CFLAGS) -o $(TEST_OUTPUT) $(SRC) $(TEST_SRC) $(GTEST_FLAGS)
	./$(TEST_OUTPUT) # Запускаем тесты
	gcov test-s21_matrix_oop.cpp 
	geninfo --ignore-errors mismatch  -o coverage.info .
	genhtml coverage.info -o coverage_report

leaks: test
ifeq ($(OS), Darwin)
	leaks --atExit -- ./test
else
	valgrind --leak-check=full --show-leak-kinds=all ./test
endif

clang_format:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i s21_matrix_oop.cpp s21_matrix_oop.h test.cpp
	rm -f .clang-format


clang_check:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n s21_matrix_oop.cpp s21_matrix_oop.h test.cpp
	rm -f .clang-format

clean: 
	rm -rf *.o
	rm -rf *.out
	rm -rf *.a
	rm -rf test
	rm -rf *.gcno
	rm -rf *.gcda
	rm -rf *.gcov
	rm -rf *.log
	rm -rf *.html
	rm -rf *.css
	rm -rf coverage_report
	rm -rf *.dSYM
	rm -rf *.info