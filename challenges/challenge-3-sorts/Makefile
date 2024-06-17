CC=g++
CFLAGS=-gdwarf -std=c++11 -pedantic -Wall -Wextra

main: tst.cpp sorts.h
	$(CC) $(CFLAGS) -o quicksorts tst.cpp

clean:
	rm -f quicksorts *.o

run:
	quicksorts
