CC      ?= /bin/cc
CFLAGS  = -ansi -g -Wall
LDLIBS  = -lm -pthread -lcurl

INCLUDES = -I./include
SOURCES  = $(wildcard src/*.c)
OBJECTS  = $(patsubst src/%.c, obj/%.o, $(SOURCES))

BINARY = bin/cbuster

all: clean build run

build: $(OBJECTS)
	mkdir -p $$(dirname $(BINARY))
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BINARY) $(OBJECTS) $(LDLIBS)

obj/%.o: src/%.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDLIBS)

clean:
	rm -rf bin obj

run:
	@./$(BINARY)
