CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cpp src/busgraph.h src/busgraph.cpp
	${CXX} ${CXX_FLAGS} src/main.cpp src/busgraph.cpp -o bin/exec

bin/tests: tests/test.cc src/busgraph.h src/busgraph.cpp
	${CXX} ${CXX_FLAGS} tests/test.cc src/busgraph.cpp -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*
