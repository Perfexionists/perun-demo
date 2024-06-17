CC=g++
CFLAGS=-gdwarf -std=c++11 -pedantic -Wall -Wextra

main: src/sort_file.cpp src/sorts.h
	$(CC) $(CFLAGS) -o sort_file src/sort_file.cpp

clean:
	rm -f quicksorts *.o

run:
	quicksorts
