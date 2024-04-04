CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest -lsubunit
GFLAGS = -fprofile-arcs -ftest-coverage
LIB_NAME = s21_containers.a
LIB_SRC = $(wildcard ./map/*.cpp)
LIB_OBJ = $(LIB_SRC:.cpp=.o)
TEST_SRC = $(wildcard ./tests/*.cpp)
TEST_GCDA = $(LIB_SRC:.cpp=.gcda)
TEST_GCNO = $(LIB_SRC:.cpp=.gcno)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: test

test: clean $(TEST_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -l:$(LIB_NAME) $(TFLAGS)
	rm -f $(TEST_OBJ)
	./test

gcov_report: clean add_coverage $(LIB_OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -o gcov_r $(TEST_SRC) -L. -l:$(LIB_NAME) $(TFLAGS)
	mkdir coverage_report
	./gcov_r
	python3 -m gcovr -r . --html --html-details -o coverage_report/index.html --exclude test
	open coverage_report/index.html

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

$(LIB_NAME): $(LIB_OBJ)
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	ranlib $(LIB_NAME)
	rm -f $(LIB_OBJ)

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h tests/* list/* queue/* set/*
	cppcheck --enable=all --suppress=missingIncludeSystem .

style_fix:
	cp ../materials/linters/.clang-format .
	clang-format -i *.h tests/* list/* queue/* set/*

leak_check: test
	valgrind --tool=memcheck --leak-check=yes ./test

clean:
	rm -f $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) test gcov* coverage.info tests/*.gcno $(TEST_GCDA) $(TEST_GCNO)
	rm -rf coverage_report
	rm -rf .clang-format

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

re: clean all
