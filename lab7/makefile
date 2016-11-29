CC = gcc

myapp: subproc mproc1

mproc1: mproc1.c
	$(CC) -o mproc1 mproc1.c

subproc: subproc.c
	$(CC) -o subproc subproc.c

.PHONY: clean
clean:
	rm *.o

.PHONY: update
update: 
	touch mproc1.c subproc.c

