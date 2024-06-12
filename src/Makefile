CC=g++
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra -pedantic -g --coverage
HEADERS=$(wildcard containers/*.hpp)
TESTS=$(wildcard tests/*.cpp)
CHECKFLAGS=-lgtest -lgtest_main -pthread
REPORTDIR=gcov_report
IGNORE=--ignore-errors source,no_function,gcov,unexecuted_branch,inconsistent --no-external

all: clean test

test: clean
	$(CC) $(CXXFLAGS) $(GCOV) -c $(HEADERS) $(TESTS)
	$(CC) $(CXXFLAGS) $(GCOV) -o containers_test *.o $(CHECKFLAGS)
	./containers_test

check:
	cppcheck $(HEADERS) && cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ *.h

style: 
	cp ../materials/linters/.clang-format .
	clang-format -i $(HEADERS) $(TESTS) tests/*.hpp *hpp
	rm .clang-format

style_check:
	cp ../materials/linters/.clang-format .
	clang-format -n $(HEADERS) $(TESTS) tests/*.hpp *hpp
	rm .clang-format

gcov_report: test
	lcov -t "Unit-tests of s21_containers" -o s21_containers.info -c -d . --rc lcov_branch_coverage=1 $(IGNORE) --ignore-errors inconsistent
	genhtml -o $(REPORTDIR) s21_containers.info --ignore-errors inconsistent
	open ./$(REPORTDIR)/index.html

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./$(REPORTDIR) *.info ./*.info report containers_test containers/*.gch
