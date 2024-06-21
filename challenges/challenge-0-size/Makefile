all: squared_count

squared_count: src/squared_count.cpp
	g++ --std=c++11 -g -o0 --coverage src/squared_count.cpp -o squared_count

clean:
	rm -rf squared_count *.gc*
