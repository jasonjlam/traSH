all: main.o shell.o redir.o cmds.o
	gcc -o trash main.o shell.o cmds.o redir.o

main.o: main.c shell.h cmds.h redir.h cmds.h
	gcc -c -g main.c

redir.o: redir.c redir.h shell.h cmds.h
	gcc -c -g redir.c

shell.o: shell.c shell.h redir.h cmds.h
	gcc -c -g shell.c cmds.h

cmds.o: cmds.c cmds.h
	gcc -c -g cmds.c

run:
	./trash

clean:
	rm *.o
	rm *~
