#
# makefile
# cs5201 - Numerical Modeling
#
# Created by Illya Starikov on 01/28/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

CXX = g++-7
CXXFLAGS = -std=c++17 -Wpedantic -Wall -Wfloat-conversion -Wextra -Werror -lstdc++fs -g
CXXTESTFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage -g

OBJECTS =		src/main.o \
				src/functions.o \
				src/exceptions/gaussian-exception.o
			
LIBRARY = 		src/exceptions/vector-exception.o

TEST_OBJECTS =	tests/test-catch.o \
				tests/test-vector.o \
				tests/test-square-matrix.o


.SUFFIXES: .cpp
.PHONY: clean run docs test

driver: ${OBJECTS} ${LIBRARY}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${LIBRARY} -o $@ -lstdc++fs

test: ${TEST_OBJECTS} ${LIBRARY}
	${CXX} ${CXXTESTFLAGS} ${TEST_OBJECTS} ${LIBRARY} -o $@ -lstdc++fs
	./test

src/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

src/exceptions/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

tests/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	-@rm -rf **/*.o 2> /dev/null || true
	-@rm -rf driver 2> /dev/null || true
	-@rm -rf test   2> /dev/null || true
	-@rm -rf core   2> /dev/null || true

run: driver
	./driver ${ARGS}

docs: 
	doxygen

vector-exception.o: src/exceptions/vector-exception.cpp src/exceptions/vector-exception.h src/exceptions/vector-exception.hpp
gaussian-exception.o: src/exceptions/gaussian-exception.cpp src/exceptions/gaussian-exception.h

test-catch.o: tests/test-catch.cpp
test-vector.o: tests/test-vector.cpp tests/catch.hpp src/lib/vector.h src/exceptions/vector-exception.h src/exceptions/vector-exception.o
test-square-matrix.o: tests/test-rectangular-matrix.cpp tests/catch.hpp src/lib/vector.h src/exceptions/vector-exception.h src/lib/square-matrix.h src/lib/base-matrix.h src/lib/matrix.h src/lib/vector.h
