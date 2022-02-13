
# each time search.c or hashmap.c are changed recompile the two into an executable called search
# makefile only recompiles files that have changed since the last executable was created

# the make target
all: driver.o training.o queryHandling.o
	gcc driver.o training.o queryHandling.o -o search -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g -lm

driver.o: driver.c
	gcc -c driver.c -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g

training.o: training.c header.h
	gcc -c training.c -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g
	
queryHandling.o: queryHandling.c header.h
	gcc -c queryHandling.c -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g
	
clean:
	rm *.o driver 


