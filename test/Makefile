#Makefile 

TARGET=test.c

OBJECTS=$(filter-out ../test/%.cc, $(shell find ../ -name "*.cc"))

GCC=g++

FLAG= -I../ -lpthread

all:
	$(GCC) $(FLAG) $(OBJECTS) $(TARGET)
