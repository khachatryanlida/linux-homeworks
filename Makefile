all: read

read:read_file.o
	 g++ read_file.o -o read

read_file.o: read_file.cpp
	g++ -c read_file.cpp
clean:
	rm *.o read
