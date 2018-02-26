#
# makefile
# cs5201 - Numerical Modeling
#
# Created by Illya Starikov on 01/28/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

CXX = g++-7
CXXFLAGS = -std=c++17 -Wpedantic -Wall -Wfloat-conversion -Wextra -Werror -lstdc++fs
CXXTESTFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage -g

OBJECTS = 	src/main.o \
			src/functions.o \
			src/exceptions/vector-exception.o \
			src/exceptions/interpolation-exception.o

TEST_OBJECTS =	tests/test-vector.o \
				tests/test-lower-triangular-matrix.o \
				src/exceptions/vector-exception.o \
				src/exceptions/interpolation-exception.o


.SUFFIXES: .cpp
.PHONY: clean run docs test


driver: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@ -lstdc++fs

test: ${TEST_OBJECTS}
	${CXX} ${CXXTESTFLAGS} ${TEST_OBJECTS} -o $@ -lstdc++fs
	./test
	gcov-7 -r -a tests/*.cpp

src/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

src/functions/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

src/exceptions/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

tests/%.o: %.cpp
	${CXX} -c ${CXXTESTFLAGS} $< -o $@


clean:
	-@rm **/*.o
	-@rm driver
	-@rm test
	-@rm core

run: driver
	./driver ${ARGS}

docs: 
	doxygen


main.o: src/main.cpp src/functions.h src/lib/lower-triangular-matrix.h src/lib/a-matrix.h src/lib/a-matrix.hpp
functions.o: src/functions.cpp src/functions.h
vector-exception.o: src/exceptions/vector-exception.cpp src/exceptions/vector-exception.h 
interpolation-exception.o: src/exceptions/interpolation-exception.cpp src/exceptions/vector-interpolation.h

test-vector.o: tests/test-vector.cpp tests/catch.hpp src/lib/vector.h src/exceptions/vector-exception.h src/exceptions/vector-exception.o
test-lower-triangular-matrix.o: tests/test-lower-triangular-matrix.cpp tests/catch.hpp src/lib/lower-triangular-matrix.h src/lib/a-matrix.h src/lib/Vector.h src/exceptions/vector-exception.h src/exceptions/vector-exception.hpp src/lib/a-matrix.hpp src/lib/vector.h
