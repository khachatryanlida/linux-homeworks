all: do_command

do_command: do_command.o
	g++ do_command.o -o do_command

do_command.o: do_command.cpp
	g++ do_command.cpp

clean:
	rm *.o do_command
