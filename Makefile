install: main.c functions.c
	mkdir obj
	gcc -c main.c -o obj/main.o
	gcc -c functions.c -o obj/functions.o
	gcc obj/main.o obj/functions.o -o TicTacToe
clean:
	rm -rf obj