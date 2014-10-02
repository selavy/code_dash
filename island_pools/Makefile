run: a.out
	./a.out < input.in
official: a.out
	./a.out < input.official > myoutput
	diff myoutput output.offical
a.out: main.cpp
	g++ -g -std=c++11 main.cpp
.PHONY: clean
clean:
	rm -rf a.out
