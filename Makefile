all:
	g++ -std=c++11 src/*.cpp -o bin/scheme

clean:
	rm bin/*
