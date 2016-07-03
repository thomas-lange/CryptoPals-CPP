CC=g++
CFLAGS=-std=c++11 -Wall

all: test1

test1: Tests/HexByteBase.cpp
	$(CC) $(CFLAGS) $< -o build/HexByteBase


clean:
	rm build/*

# %: %.c
# 	gcc $< -o $@




# CC=g++
# CFLAGS=-std=c++11

# all: tests


# tests: Tests/HexByteBase.o
# 	g++ HexByteBase.o -o tests

# HexByteBase.o: Tests/HexByteBase.cpp
# 	g++ -c Tests/HexByteBase.cpp

# clean:
# 	rm *o tests


# # %: %.cpp
# #  	g++ -std=c++11 $< -o $@

