all: main.o shell.o cmds.o
	gcc -o trash main.o shell.o cmds.o

main.o: main.c shell.h cmds.h
	gcc -c -g main.c

shell.o: shell.c
	gcc -c -g shell.c

cmds.o: cmds.c
	gcc -c -g cmds.c
	
run:
	./trash

clean:
	rm *.o
	rm *~
