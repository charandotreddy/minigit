.PHONY: clean

minigit: main.o init.o status.o sha1.o object.o hash_object.o object_store.o add.o index.o tree.o commit.o
	gcc main.o init.o status.o sha1.o object.o hash_object.o object_store.o add.o index.o tree.o commit.o -o minigit -lcrypto -lz

main.o: src/main.c include/init.h include/status.h include/common.h include/hash_object.h include/add.h include/tree.h
	gcc -Iinclude -c src/main.c -o main.o

init.o: src/init.c include/init.h include/common.h
	gcc -Iinclude -c src/init.c -o init.o

status.o: src/status.c include/status.h include/common.h
	gcc -Iinclude -c src/status.c -o status.o

sha1.o: src/sha1.c include/sha1.h include/common.h
	gcc -Iinclude -c src/sha1.c -o sha1.o

object.o: src/object.c include/object.h include/common.h
	gcc -Iinclude -c src/object.c -o object.o

hash_object.o: src/hash_object.c include/hash_object.h include/object.h include/sha1.h include/object_store.h include/common.h
	gcc -Iinclude -c src/hash_object.c -o hash_object.o

object_store.o: src/object_store.c include/object_store.h include/common.h
	gcc -Iinclude -c src/object_store.c -o object_store.o

add.o: src/add.c include/add.h include/hash_object.h include/index.h include/common.h
	gcc -Iinclude -c src/add.c -o add.o

index.o: src/index.c include/index.h include/common.h
	gcc -Iinclude -c src/index.c -o index.o

tree.o: src/tree.c include/tree.h include/sha1.h include/object_store.h include/common.h
	gcc -Iinclude -c src/tree.c -o tree.o

commit.o: src/commit.c include/commit.h include/tree.h include/object_store.h include/sha1.h include/common.h
	gcc -Iinclude -c src/commit.c -o commit.o

clean:
	rm -f main.o init.o status.o sha1.o object.o hash_object.o object_store.o add.o index.o tree.o commit.o minigit
