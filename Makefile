install: main.c functions.c
	mkdir -v obj
	gcc -c -v main.c -o obj/main.o
	gcc -c -v functions.c -o obj/functions.o
	gcc -v obj/main.o obj/functions.o -o TicTacToe
clean:
	rm -rvf -v obj 