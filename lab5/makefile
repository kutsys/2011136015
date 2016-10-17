#makefile comment

#compiler
CC=gcc

mtest: mtest.o foo.o boo.o bar.o
	$(CC) -o mtest mtest.o foo.o boo.o bar.o

main.o: mtest.c
	$(CC) -c mtest.c

foo.o: foo.c
	$(CC) -c foo.c

boo.o: boo.c
	$(CC) -c boo.c

bar.o: bar.c
	$(CC) -c bar.c

.PHONY: clean
clean:
	rm mtest *.o

.PHONY: update
update:
	touch *.c
