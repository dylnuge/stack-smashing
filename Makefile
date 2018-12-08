# This is a makefile for examples of EXPLOITABLE code
# That means that it does some really dumb things you should NOT copy...
# ...Unless you wanna make exploit code ;)

CC = clang
BUILD_DIR = build
# Adding -arch i386 here will build 32-bit code instead of 64-bit code
# This can make addresses look more manageable, and help match the slide decks
# more closely, but it won't work on OSX Mojave (10.14) or later.
EXPLOITABLE_FLAGS = -fno-stack-protector

all: ex1 ex2

ex1: src/ex1.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(EXPLOITABLE_FLAGS) -o $(BUILD_DIR)/ex1 src/ex1.c

ex2: src/ex2.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(EXPLOITABLE_FLAGS) -o $(BUILD_DIR)/ex2 src/ex2.c

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)
