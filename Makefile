CC = gcc
CFLAGS = -Wall

build-t1: p1.c
	$(CC) $(CFLAGS) p1.c -o p1

run-t1: p1
	./p1


build-t2: p2.c
	$(CC) $(CFLAGS) p2.c -o p2

run-t2: p2
	./p2


build-t3: p3.c
	$(CC) $(CFLAGS) p3.c -o p3

run-t3: p3
	./p3

.PHONY: clean
clean:
	rm -rf *.o p1 p2 p3
