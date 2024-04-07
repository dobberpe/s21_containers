CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest -lsubunit
GFLAGS = -fprofile-arcs -ftest-coverage
TEST_SRC = $(wildcard ./tests/*.cpp)
TEST_GCDA = $(LIB_SRC:.cpp=.gcda)
TEST_GCNO = $(LIB_SRC:.cpp=.gcno)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: test

test: clean $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. $(TFLAGS)
	rm -f $(TEST_OBJ)
	./test

gcov_report: clean add_coverage $(LIB_OBJ)
	$(CC) $(CFLAGS) -o gcov_r $(TEST_SRC) -L. $(TFLAGS)
	mkdir coverage_report
	./gcov_r
	python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	open coverage_report/index.html

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)


style_check:
	find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.tpp" \) -exec clang-format -n --style=file:../materials/linters/.clang-format {} \;
	cppcheck --enable=all --suppress=missingIncludeSystem .

style_fix:
	find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.tpp" \) -exec clang-format -i --style=file:../materials/linters/.clang-format {} \;

leak_check: test
	valgrind --tool=memcheck --leak-check=yes ./test

clean:
	rm -f $(TEST_OBJ) test gcov* coverage.info tests/*.gcno $(TEST_GCDA) $(TEST_GCNO)
	rm -rf coverage_report
	rm -rf .clang-format

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

re: clean all

