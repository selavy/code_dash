all: a.out
	./a.out < input.txt
	./a.out < input2.txt > my_output
	diff my_output output2.txt
a.out: main.cpp
	g++ -std=c++11 main.cpp
clean:
	rm -rf a.out
