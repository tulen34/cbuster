CC       := /bin/gcc
CFLAGS   := -g -Wall
TARGET 	 := cbuster

INCLUDES :=
LIBS     := -lm -pthread -lcurl

all: build run

build:
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) main.c $(LIBS)

run:
	@./$(TARGET)
