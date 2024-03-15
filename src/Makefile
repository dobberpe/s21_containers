SHELL = /bin/sh

# Linux, Darwin or Windows_NT
OS=$(shell uname -s)

TEST_SRC=$(wildcard tests/*.cpp)
#DEV_SRC=$(wildcard dev/*.cpp)
LIB_SRC=$(wildcard list/*.cpp) # https://runebook.dev/ru/docs/gnu_make/wildcard-function
TEST_OBJS=$(TEST_SRC:.cpp=.o)
DEV_OBJS=$(DEV_SRC:.cpp=.o)
LIB_OBJS:=$(patsubst %.cpp,%.o,$(LIB_SRC) $(DEV_SRC))
DIR_BUILD=build/
OS_MAC_UX=-lsubunit

CC=gcc
FLAGS=-Wall -Wextra -std=c++17# -Werror
CFLAGS:=$(FLAGS) -c
GCOV=

.PHONY: clean test gcov_report control ext1_flag

all: 

clean:
	-rm -rf report/ s21_containers.a $(DIR_BUILD)*.* $(DIR_BUILD)test_s21_containers

test: $(TEST_OBJS) s21_containers.a
ifeq ($(OS),Darwin)
	$(eval OS_MAC_UX=-L/opt/homebrew/lib)
endif
	c++ $(FLAGS) $(GCOV) $(DIR_BUILD)*.o s21_containers.a -o $(DIR_BUILD)test_s21_containers -lgtest $(OS_MAC_UX) -L.
	$(DIR_BUILD)test_s21_containers

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $(DIR_BUILD)$(notdir $@)

s21_containers.a: $(LIB_OBJS) 
	ar r $@ $(DIR_BUILD)*.o
	ranlib $@

$(LIB_OBJS): $(LIB_SRC) $(DEV_SRC) 
	$(CC) $(CFLAGS) $(GCOV) $(patsubst %.o,%.cpp,$@) -o $(DIR_BUILD)$(notdir $@)


gcov_report: clean ext1_flag s21_containers.a test
	geninfo $(DIR_BUILD) -o $(DIR_BUILD)s21_matrix_report.info
	genhtml -o report $(DIR_BUILD)s21_matrix_report.info
	open report/index.html

ext1_flag:
	$(eval GCOV=-fprofile-arcs -ftest-coverage)


control:
	-cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem --error-exitcode=1 *.cpp *.h tests/*.cpp tests/*.h~ dev/*.cpp dev/*.h
	-clang-format --Werror -n --style=file:../materials/linters/.clang-format tests/*.cpp tests/*.h *.cpp *.h dev/*.cpp dev/*.h
	-valgrind --tool=memcheck --leak-check=yes -s $(DIR_BUILD)test_s21_containers

clang:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i --style=file:../materials/linters/.clang-format {} \;

