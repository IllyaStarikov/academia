#
# makefile
#  cs5201 - Numerical Modeling
#
# Created by Illya Starikov on 01/28/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

CXX = g++-7
CXXFLAGS = -std=c++17 -Wpedantic -Wall -Wextra -Wfloat-conversion -Werror -lstdc++fs

OBJECTS = 	src/main.o \
			src/functions/functions.o

.SUFFIXES: .cpp
.PHONY: clean run

driver: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o $@

src/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

src/functions/%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@

clean:
	-@rm core > /dev/null 2>&1
	-@rm driver > /dev/null 2>&1
	-@rm **/*.o > /dev/null 2>&1

run: driver
	./driver ${ARGS}

main.o: src/main.cpp src/functions/functions.h
functions.o: src/functions/functions.cpp src/functions/functions.h
