run:
	flex main.l
	g++ -std=c++14 lex.yy.c -o driver
	cat input/input.txt | ./driver
	cat input/input.txt | ./driver > output.txt

clean:
	/bin/rm -f lex.yy.c   > /dev/null
	/bin/rm -f driver     > /dev/null
	/bin/rm -f output.txt > /dev/null
