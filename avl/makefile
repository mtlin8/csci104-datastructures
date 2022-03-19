CXX = g++ --std=c++11
CPPFLAGS = -Wall -g

all: test

test: test.cpp  avlbst.h bst.h print_bst.h
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf test