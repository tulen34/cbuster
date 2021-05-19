CC      ?= /bin/cc
CFLAGS  = -g -Wall
LDLIBS  = -lm -pthread -lcurl

SOURCES_DIR = src
OBJECTS_DIR = obj
BINARY_DIR  = bin
BINARY      = $(BINARY_DIR)/cbuster

INCLUDES = -I./include
SOURCES  = $(wildcard $(SOURCES_DIR)/*.c)
OBJECTS  = $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
MAIN     = main.c

define status
	printf "[\033[37;2m%s\033[0m] \033[32;1m%s\033[0m\n" `date +"%T"` $1
endef

all: clean build run

build: $(OBJECTS) $(OBJECTS_DIR) $(BINARY_DIR)
	@$(call status, "Compiling binary file to $(BINARY) from $(MAIN)$(OBJECTS)")
	$(CC) $(CFLAGS) $(INCLUDES) $(MAIN) $(OBJECTS) -o $(BINARY) $(LDLIBS)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(OBJECTS_DIR)
	@$(call status, "Compiling object file from $< to $@")
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDLIBS)

$(OBJECTS_DIR):
	mkdir -p obj

$(BINARY_DIR):
	mkdir -p bin

clean:
	@$(call status, "Cleaning")
	rm -rf $(BINARY_DIR) $(OBJECTS_DIR)

run:
	@$(call status, "Running $(BINARY)")
	@./$(BINARY)
