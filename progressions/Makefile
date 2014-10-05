all: a.out
	./a.out < input.sample > output.me
	diff output.me output.sample
test: a.out
	./a.out < input.sample
official: a.out
	./a.out < input.official > output.me
	diff output.me output.official
a.out: main.cpp
	g++ -std=c++11 main.cpp -o a.out
clean:
	rm -rf a.out *~
