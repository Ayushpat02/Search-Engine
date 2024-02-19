build:
	g++ -std=c++20 -Wall main.cpp -o program.out
	
run:
	./program.out

clean:
	rm -f ./program.out