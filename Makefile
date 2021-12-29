dev:
	g++ -c main.cpp -o main.o
	g++ main.o -lsfml-graphics -lsfml-window -lsfml-system -o main
	./main -s triangle -h 600 -c red

build:
	g++ -c main.cpp -o main.o
	g++ main.o -lsfml-graphics -lsfml-window -lsfml-system -o main