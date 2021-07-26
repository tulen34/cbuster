CC      ?= /bin/cc
CFLAGS  = -g -Wall -Wextra -Wconversion -Wstrict-prototypes
LDLIBS  = -lcurl

INCLUDES = -I./src
SOURCES  = $(wildcard src/*.c)
OBJECTS  = $(patsubst src/%.c, obj/%.o, $(SOURCES))
BINARY   = bin/cbuster

.PHONY: all build clean run

all: clean build run

obj:
	mkdir -p obj

bin:
	mkdir -p bin

obj/%.o: src/%.c obj
	@echo 'Compiling object file to $@ from $<'
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDLIBS)

build: $(OBJECTS) bin
	@echo 'Compiling binary file'
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(OBJECTS) -o $(BINARY) $(LDLIBS)

clean:
	@echo 'Cleaning'
	rm -rf bin obj

run:
	@echo 'Running $(BINARY)'
	@./$(BINARY)
