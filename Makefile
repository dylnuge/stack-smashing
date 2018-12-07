# This is a makefile for examples of EXPLOITABLE code
# That means that it does really dumb things you should NOT copy...
# ...Unless you wanna make exploit code ;)

CC = clang
BUILD_DIR = build
EXPLOITABLE_FLAGS = -fno-stack-protector

ex1: ex1.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(EXPLOITABLE_FLAGS) -o $(BUILD_DIR)/ex1 ex1.c

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)
