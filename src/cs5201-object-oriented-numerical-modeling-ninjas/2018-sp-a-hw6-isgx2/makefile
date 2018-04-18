#
# makefile
# cs5201 - Numerical Modeling Created by Illya Starikov on 01/28/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

CXX = g++-7
CXXFLAGS = -std=c++17 -Wpedantic -Wall -Wfloat-conversion -Wextra -Werror -lstdc++fs -g -fprofile-arcs -ftest-coverage --coverage

OBJECTS =		src/main.o                          \
				src/functions.o                     \
			
LIBRARY = 		lib/exceptions/vector-exception.o   \
				lib/exceptions/matrix-exception.o   \

TEST_OBJECTS =	tests/test-catch.o                  \
				tests/test-vector.o                 \
				tests/test-rectangular-matrix.o     \
				tests/test-diagonal-matrix.o        \
				tests/test-banded-matrix.o          \
				tests/test-symmetric-matrix.o       \


.SUFFIXES: .cpp
.PHONY: clean run docs test coverage

driver: ${LIBRARY} ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIBRARY} -o $@ -lstdc++fs

test: ${LIBRARY} ${TEST_OBJECTS}
	${CXX} ${CXXFLAGS} ${TEST_OBJECTS} ${LIBRARY} -o $@ -lstdc++fs
	./test

src/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

lib/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

lib/exceptions/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

tests/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	-@rm -rf **/*.o       2> /dev/null || true
	-@rm -rf **/**/*.o    2> /dev/null || true 
	-@rm -rf *.gcov       2> /dev/null || true
	-@rm -rf **/*.gcno    2> /dev/null || true
	-@rm -rf **/**/*.gcno 2> /dev/null || true
	-@rm -rf **/*.gcda    2> /dev/null || true
	-@rm -rf **/**/*.gcda 2> /dev/null || true
	-@rm -rf driver.dSYM  2> /dev/null || true
	-@rm -rf test.dSYM    2> /dev/null || true
	-@rm -rf driver       2> /dev/null || true
	-@rm -rf test         2> /dev/null || true
	-@rm -rf core         2> /dev/null || true

run: driver
	./driver ${ARGS}

docs:
	doxygen

coverage: test
	gcov-7 -r tests/test-*.cpp

main.o: 					src/main.cpp src/functions.h lib/eigen.h                  \
							lib/vector.h lib/exceptions/exceptions.h                  \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/matrix-base.h src/../lib/matrix.h \
							lib/diagonal-matrix.h lib/rectangular-matrix.h            \
							lib/rectangular-matrix.hpp lib/symmetric-matrix.h         \
							src/steepest-descent-solver.h                             \
							src/exceptions/steepest-descent-exception.h               \
							exceptions/steepest-descent-exception.h


vector-exception.o: 		lib/exceptions/vector-exception.cpp                       \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/vector-exception.hpp

matrix-exception.o: 		lib/exceptions/matrix-exception.cpp                       \
							lib/exceptions/matrix-exception.h                         \
							lib/exceptions/vector-exception.h


test-catch.o: 				tests/test-catch.cpp

test-vector.o: 				tests/test-vector.cpp tests/catch.hpp lib/eigen.h         \
							lib/vector.h lib/exceptions/exceptions.h                  \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/matrix-base.h                     \
							lib/matrix.h lib/diagonal-matrix.h                        \
							lib/rectangular-matrix.h lib/rectangular-matrix.hpp       \
							lib/symmetric-matrix.h

test-rectangular-matrix.o: 	tests/test-rectangular-matrix.cpp                         \
							tests/catch.hpp lib/eigen.h lib/vector.h                  \
							lib/exceptions/exceptions.h                               \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/matrix-base.h                     \
							lib/matrix.h lib/diagonal-matrix.h                        \
							lib/rectangular-matrix.h lib/rectangular-matrix.hpp       \
							lib/symmetric-matrix.h

test-diagonal-matrix.o: 	tests/test-diagonal-matrix.cpp tests/catch.hpp            \
							lib/eigen.h lib/vector.h                                  \
							lib/exceptions/exceptions.h                               \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/matrix-base.h                     \
							lib/matrix.h lib/diagonal-matrix.h                        \
							lib/rectangular-matrix.h lib/rectangular-matrix.hpp       \
							lib/symmetric-matrix.h

test-diagonal-matrix.o: 	tests/test-diagonal-matrix.cpp tests/catch.hpp            \
							lib/eigen.h lib/vector.h                                  \
							lib/exceptions/exceptions.h                               \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/matrix-base.h                     \
							lib/matrix.h lib/diagonal-matrix.h                        \
							lib/diagonal-matrix.hpp                                   \
							lib/rectangular-matrix.h lib/rectangular-matrix.hpp       \
							lib/symmetric-matrix.h

test-banded-matrix.o: 		tests/test-banded-matrix.cpp tests/catch.hpp              \
							lib/eigen.h lib/vector.h                                  \
							lib/exceptions/exceptions.h                               \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/banded-matrix.hpp                 \
							lib/matrix-base.h                                         \
							lib/matrix.h lib/diagonal-matrix.h                        \
							lib/rectangular-matrix.h lib/rectangular-matrix.hpp       \
							lib/symmetric-matrix.h

test-symmetric-matrix.o: 	tests/test-symmetric-matrix.cpp tests/catch.hpp           \
							lib/eigen.h lib/vector.h                                  \
							lib/exceptions/exceptions.h                               \
							lib/exceptions/vector-exception.h                         \
							lib/exceptions/matrix-exception.h lib/vector.hpp          \
							lib/banded-matrix.h lib/matrix-base.h                     \
							lib/matrix.h lib/diagonal-matrix.h                        \
							lib/rectangular-matrix.h lib/rectangular-matrix.hpp       \
							lib/symmetric-matrix.h lib/symmetric-matrix.h
