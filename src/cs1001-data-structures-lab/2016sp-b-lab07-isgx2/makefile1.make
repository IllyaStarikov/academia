build: main.o funcs.o triangle.o
	g++ main.o funcs.o triangle.o -o build

main.o: main.cpp funcs.h TrianglePrinter.h
	g++ -c main.cpp

funcs.o: funcs.cpp funcs.h
	g++ -c funcs.cpp

triangle.o: TrianglePrinter.cpp TrianglePrinter.h
	g++ -c TrianglePrinter.cpp -o triangle.o

.PHONY: clean

clean:
	@rm -f program
	@rm -f *.o
