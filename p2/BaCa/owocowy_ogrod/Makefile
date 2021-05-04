GTEST_HOME=/home/me/usr/gtest
CC=g++
LDFLAGS=-g -I $(GTEST_HOME)/include -L $(GTEST_HOME)/lib -lgtest -lgtest_main
p: main.cpp source.cpp
	$(CC) $(LDFLAGS) $< -o $@
