.PHONY: clean

minigit: main.o init.o status.o sha1.o
	gcc main.o init.o status.o sha1.o -o minigit -lcrypto

main.o: src/main.c include/init.h include/status.h include/common.h include/sha1.h
	gcc -Iinclude -c src/main.c -o main.o

init.o: src/init.c include/init.h include/common.h
	gcc -Iinclude -c src/init.c -o init.o

status.o: src/status.c include/status.h include/common.h
	gcc -Iinclude -c src/status.c -o status.o

sha1.o: src/sha1.c include/sha1.h include/common.h
	gcc -Iinclude -c src/sha1.c -o sha1.o

clean:
	rm -f main.o init.o status.o sha1.o minigit
