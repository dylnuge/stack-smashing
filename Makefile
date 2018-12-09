# This is a makefile for examples of EXPLOITABLE code
# That means that it does some really dumb things you should NOT copy...
# ...Unless you wanna make exploit code ;)

CC = clang
BUILD_DIR = build

# Adding -arch i386 here will build 32-bit code instead of 64-bit code
# This can make addresses look more manageable, and help match the slide decks
# more closely, but it won't work on OSX Mojave (10.14) or later.
#
# Here's what the options we do have do:
#     -fno-stack-protector: Compile our code without stack canaries. If we don't
#         use this option, then we'd have a stack canary after a 12-character
#         buffer which would segfault when written into. Fun fact: if the
#         buffer was 7 characters or less, this _wouldn't matter_ (at least on
#         64-bit Mojave where I tested it).
#     -Wl: Passes the comma separated args to the linker. The next two args are
#         for the linker.
#     -allow_stack_execute: Sets the stack as executable for example 3. Doesn't
#         matter for the other two examples, but otherwise when we try to jump
#         to our stack we'd segfault.
#     -no_pie: Turns off position independent executable builds, which are
#         default. This matters for example 2: without it, we would not be able
#         to know the exact address `root_mode` is at when we run.
EXPLOITABLE_FLAGS = -fno-stack-protector -Wl,-allow_stack_execute,-no_pie

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
