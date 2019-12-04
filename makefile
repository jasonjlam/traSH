all: shell.o
	gcc -o trash shell.o

shell.o: shell.c
	gcc -c -g shell.c

run:
	./trash

clean:
	rm *.o
	rm *~
