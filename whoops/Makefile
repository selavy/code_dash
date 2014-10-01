all: a.out
	./a.out < input.in > output.me
	diff output.me output.solution
official: a.out
	./a.out < input.official > mysolution
	diff mysolution output.official
a.out: main.cpp
	g++ -std=c++11 main.cpp
