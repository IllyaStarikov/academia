.PHONY: all test clean coverage
CFLAGS=-Wall -Werror

all: main

main: funcs.o main.o
	g++ ${CFLAGS} $^ -o main

test: testsuite
	@./testsuite

coverage: CFLAGS=-Wall -Werror -fprofile-arcs -ftest-coverage
coverage: clean testsuite
	@./testsuite
	gcov -r test_main.cpp test_funcs.cpp funcs.cpp test_vector.cpp

testsuite: test_main.o test_funcs.o funcs.o test_vector.o
	g++ ${CFLAGS} $^ -o testsuite

main.o: main.cpp funcs.h vector.h vector.hpp
	g++ ${CFLAGS} -c main.cpp

test_main.o: test_main.cpp
	g++ ${CFLAGS} -c test_main.cpp

funcs.o: funcs.cpp funcs.h
	g++ ${CFLAGS} -c funcs.cpp

test_funcs.o: test_funcs.cpp funcs.h
	g++ ${CFLAGS} -c test_funcs.cpp

test_vector.o: test_vector.cpp vector.h vector.hpp
	g++ ${CFLAGS} -c test_vector.cpp

clean:
	-@rm -f main testsuite
	-@rm -f *.o
	-@rm -f *.gcov *.gcno *.gcda