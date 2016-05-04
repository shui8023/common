#Makefile 

TARGET=aaaaaa

OBJECTS=$(filter-out ../test/%.cc, $(shell find ../ -name "*.cc"))

GCC=g++ -std=c++11

FLAG= -I../ -lpthread

all:
	$(GCC) $(FLAG) $(OBJECTS) $(TARGET)
