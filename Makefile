CC = gcc
CFLAGS = -g -Wall

build: minimax.o task1.o task2.o task3.o utility12.o utility3.o
	$(CC) $(CFLAGS) minimax.o task1.o task2.o task3.o utility12.o utility3.o -o minimax

minimax.o: minimax.c

task1.o: task1.c task1.h

task2.o: task2.c task2.h

task3.o: task3.c task3.h

utility12.o: utility12.c utility12.h

utility3.o: utility3.c utility3.h

run:
	./minimax

.PHONY: clean

memcheck:
	valgrind --leak-check=full ./minimax

clean:
	rm -f *.o minimax