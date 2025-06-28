SOURCES=$(wildcard *.cpp)
TARGETS=$(SOURCES:%.cpp=%)

.PHONY: all clean

all: ${TARGETS}

%: %.cpp
	g++ -std=c++11 $< -o $@

clean:
	-@rm -f ${TARGETS}