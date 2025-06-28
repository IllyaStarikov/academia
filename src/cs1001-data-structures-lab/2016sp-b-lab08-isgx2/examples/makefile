SOURCES = $(wildcard *.cpp)
EXES = $(SOURCES:%.cpp=%)

all: ${EXES}

% : %.cpp
	g++ -g $< -o $@

.PHONY: clean
clean:
	-@ rm -f ${EXES}
