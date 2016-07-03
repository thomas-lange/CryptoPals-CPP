CC=g++
CFLAGS=-std=c++11 -Wall

all: test1

test1: Tests/HexByteBase.cpp
	$(CC) $(CFLAGS) $< -o build/HexByteBase


clean:
	rm build/*
