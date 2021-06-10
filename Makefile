CC      ?= /bin/cc
CFLAGS  = -g -Wall -Wextra -Wconversion -Wstrict-prototypes
LDLIBS  = -lcurl

SOURCES_DIR = src
OBJECTS_DIR = obj
BINARY_DIR  = bin
BINARY      = $(BINARY_DIR)/cbuster

INCLUDES = -I./include
SOURCES  = $(wildcard $(SOURCES_DIR)/*.c)
OBJECTS  = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
MAIN     = main.c

define status
	printf "  \033[32;1m%s\033[0m\n" $1
endef

.PHONY: all build clean run

all: clean build run

$(OBJECTS_DIR):
	mkdir -p obj

$(BINARY_DIR):
	mkdir -p bin

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(OBJECTS_DIR)
	@$(call status, "Compiling object file to $@ from $<")
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDLIBS)

build: $(OBJECTS) $(OBJECTS_DIR) $(BINARY_DIR)
	@$(call status, "Compiling binary file to $(BINARY) from $(MAIN)$(OBJECTS)")
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(OBJECTS) -o $(BINARY) $(LDLIBS)

clean:
	@$(call status, "Cleaning")
	rm -rf $(BINARY_DIR) $(OBJECTS_DIR)

run:
	@$(call status, "Running $(BINARY)")
	@./$(BINARY)
