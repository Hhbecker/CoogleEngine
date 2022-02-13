
# each time search.c or hashmap.c are changed recompile the two into an executable called search
# makefile only recompiles files that have changed since the last executable was created

# the make target
all: search.o hashmap.o
	gcc search.o hashmap.o -o search -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g -lm

search.o: search.c
	gcc -c search.c -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g

hashmap.o: hashmap.c header.h
	gcc -c hashmap.c -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g
	
clean:
	rm *.o search 


