GTEST_HOME=$(HOME)/usr/gtest
CC=g++
LDFLAGS=-g -I $(GTEST_HOME)/include -L $(GTEST_HOME)/lib -lgtest -lgtest_main
p: source.cpp
	$(CC) $(LDFLAGS) $< -o $@
