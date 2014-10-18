all: solution.py
	./solution.py < input.sample > myoutput
	diff myoutput output.sample
	./solution.py < input.official > myoutput
	diff myoutput output.official
clean:
	rm -rf *~ myoutput
