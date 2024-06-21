all: generate

generate: src/generate.cpp
	g++ --std=c++11 -g --coverage src/generate.cpp -o generate

clean:
	rm -rf generate *.gc*
