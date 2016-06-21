# A simple makefile for CSE 100 P3

CC=g++
CXXFLAGS=-std=c++11 -g -Wall
LDFLAGS=-g

all: benchtrie benchdict test util.o 

benchtrie: util.o DictionaryTrie.o DictionaryBST.o DictionaryHashtable.o

DictionaryTrie.o: DictionaryTrie.hpp

DictionaryBST.o: DictionaryBST.hpp

DictionaryHashtable.o: DictionaryHashtable.hpp

util.o: util.hpp

benchdict: util.o DictionaryTrie.o DictionaryBST.o DictionaryHashtable.o

test: DictionaryHashtable.o DictionaryBST.o DictionaryTrie.o

clean:
	rm -f benchtrie test *.o core* *~

