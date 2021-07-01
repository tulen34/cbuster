CC      ?= /bin/cc
CFLAGS  = -g -Wall -Wextra -Wconversion -Wstrict-prototypes
LDLIBS  = -lcurl

INCLUDES = -I./src
SOURCES  = $(wildcard src/*.c)
OBJECTS  = $(patsubst src/%.c, obj/%.o, $(SOURCES))
BINARY   = bin/cbuster

define status
	printf "  \033[32;1m%s\033[0m\n" $1
endef

.PHONY: all build clean run

all: clean build run

obj:
	mkdir -p obj

bin:
	mkdir -p bin

obj/%.o: src/%.c obj
	@$(call status, "Compiling object file to $@ from $<")
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDLIBS)

build: $(OBJECTS) obj bin
	@$(call status, "Compiling binary file")
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(OBJECTS) -o $(BINARY) $(LDLIBS)

clean:
	@$(call status, "Cleaning")
	rm -rf bin obj

run:
	@$(call status, "Running $(BINARY)")
	@./$(BINARY)
