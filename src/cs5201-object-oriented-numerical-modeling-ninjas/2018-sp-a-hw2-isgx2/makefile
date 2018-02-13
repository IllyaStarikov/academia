#
# makefile
# cs5201 - Numerical Modeling
#
# Created by Illya Starikov on 01/28/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

CXX = g++-7
CXXFLAGS = -std=c++17 -Wpedantic -Wall -Wfloat-conversion -Wextra -Werror -lstdc++fs
CXXTESTFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage

OBJECTS = 	src/main.o \
			src/functions/functions.o

TEST_OBJECTS = 	tests/test-polarpair.o \
				tests/test-norm.o


.SUFFIXES: .cpp
.PHONY: clean run test


driver: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@

test: ${OBJECTS} ${TEST_OBJECTS}
	${CXX} ${CXXTESTFLAGS} ${TEST_OBJECTS} -o $@
	./test
	gcov-7 -r -a tests/*.cpp

src/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

src/functions/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

tests/%.o: %.cpp
	${CXX} -c ${CXXTESTFLAGS} $< -o $@

clean:
	-@rm core   > /dev/null 2>&1
	-@rm driver > /dev/null 2>&1
	-@rm test   > /dev/null 2>&1
	-@rm **/*.o > /dev/null 2>&1

run: driver
	./driver ${ARGS}


main.o: src/main.cpp src/functions/functions.h src/functions/functions.hpp src/lib/norm.h src/lib/polarpair.h src/lib/polarpair.hpp src/lib/polarpair.h
functions.o: src/functions/functions.cpp src/functions/functions.h src/functions/functions.hpp

polarpair.o: tests/polarpair.cpp src/lib/polarpair.h
norm.o: tests/norm.cpp src/lib/norm.h
