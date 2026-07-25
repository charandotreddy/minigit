.PHONY: clean

minigit: main.o init.o status.o
	gcc main.o init.o status.o -o minigit

main.o: src/main.c include/init.h include/status.h
	gcc -Iinclude -c src/main.c -o main.o

init.o: src/init.c include/init.h
	gcc -Iinclude -c src/init.c -o init.o

status.o: src/status.c include/status.h
	gcc -Iinclude -c src/status.c -o status.o

clean:
	rm -f main.o init.o status.o minigit
