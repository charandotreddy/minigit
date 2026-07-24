minigit: main.o init.o
	gcc main.o init.o -o minigit

main.o: src/main.c include/init.h
	gcc -Iinclude -c src/main.c -o main.o

init.o: src/init.c include/init.h
	gcc -Iinclude -c src/init.c -o init.o

clean:
	rm -f main.o init.o minigit
