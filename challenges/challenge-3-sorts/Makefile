CC=g++
CFLAGS=-O0 -g -std=c++17 -pedantic -Wall -Wextra -fno-omit-frame-pointer

main: src/sort_file.cpp src/sorts.h
	$(CC) $(CFLAGS) -o sort_file src/sort_file.cpp

clean:
	rm -f quicksorts *.o

run:
	quicksorts
