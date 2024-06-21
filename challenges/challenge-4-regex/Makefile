all: main

main: src/main.cc
	g++ --std=c++11 -g --coverage src/main.cc -o match_regex

clean:
	rm -rf match_regex *.gc*
