#Makefile 

TARGET=aaaaaa

OBJECTS=$(filter-out ../test/%.cc, $(shell find ../ -name "*.cc"))

GCC=g++ -std=c++0x

FLAG= -I../ -lpthread

all:
	$(GCC) $(FLAG) $(OBJECTS) $(TARGET)
