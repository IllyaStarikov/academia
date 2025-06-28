COMPILER = g++

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)

PRODUCTION = -std=c++11
DEBUG = -Wall --pedantic-errors -O2 -std=c++11

production: ${OBJECTS}
	${COMPILER} ${PRODUCTION} ${OBJECTS} -o build

debug: ${OBJECTS}
	${COMPILER} ${DEBUG} ${OBJECTS} -o build

%.o: %.cpp ${HEADERS}
	${COMPILER} ${PRODUCTION} -c $<

.PHONY: clean

clean:
	@rm -f program
	@rm -f *.o
