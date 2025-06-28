all: recursive_gp recursive list vector array

recursive_gp: recursive.cpp
	g++ -pg -g  recursive.cpp -o recursive_gp

recursive: recursive.cpp
	g++ -g recursive.cpp -o recursive

list: list.cpp
	g++ -g list.cpp -o list

vector: vector.cpp
	g++ -g vector.cpp -o vector

array: array.cpp
	g++ -g array.cpp -o array

clean:
	-@rm -rf recursive recursive_gp list vector
	-@rm -rf callgrind.out.* massif.out.* gmon.out