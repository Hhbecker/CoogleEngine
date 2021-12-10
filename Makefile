
# each time search.c or hashmap.c are changed recompile the two into an executable called search
# makefile only recompiles files that have changed since the last executable was created

all: search.o hashmap.o
	gcc search.o hashmap.o -o search

search.o: search.c
	gcc -c search.c

hashmap.o: hashmap.c hashmap.h
	gcc -c hashmap.c

clean:
	rm *.o search 


