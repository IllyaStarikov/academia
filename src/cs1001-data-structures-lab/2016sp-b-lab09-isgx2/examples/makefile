SOURCES = $(wildcard *.cpp)
EXES = $(SOURCES:%.cpp=%)
CPP = g++
.PHONY: clean all memsan addrsan

all: clean ${EXES}

memsan: CPP=clang++-3.6 -fsanitize=memory -fsanitize-memory-track-origins
memsan: all

addrsan: CPP=clang++-3.6 -fsanitize=address
addrsan: all

% : %.cpp
	${CPP} -Wall -g $< -o $@

clean:
	-@ rm -f ${EXES}
