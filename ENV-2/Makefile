all: main
main: main.o Complex.o
        g++ main.o Complex.o -o main
Complex.o: Complex.cpp Complex.h
        g++ -c Complex.cpp
main.o: main.cpp
        g++ -c main.cpp
clean:
        rm *.o main




