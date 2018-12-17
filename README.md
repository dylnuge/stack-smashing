# Stack Smashing (For Fun and Profit)

Slides are in the keynote file.

This repo is built for use on MacOS and was tested under MacOS Mojave (10.14)
and MacOS High Sierra (10.13). It probably works on Linux with some tweaks, but
I haven't tested it there and there might be different OS or ELF-level
protections that need to be disabled in the linker or compiler. Feel free to
ping me on Twitter and I'll check out if your changes work against my solutions.

In order to build the code, you'll need to install the Xcode CLI tools, which
should include `make`, `clang`, `ld`, and `objdump`.

To make all examples, type `make`. You can make a specific example, like ex2,
with `make ex2`.

Your goal is to get the compiled binary to print out "Exploit Succeeded." You
should not edit any of the code to accomplish this; it can be done without
changing a thing.

## Example 1 Instructions

This example reads in input from standard in until a newline is sent in. You run
it without any arguments

## Example 2 Instructions

This example is a little trickier to work with. It creates a socket file at
`socket` in the directory you run it from.

You can write to a unix (file) socket with `nc -U`, but for sending
non-printable characters, it will be easier to use the code in `socket_send.py`.
Just replace the `exploit` variable with the string you want to send.

Note that characters like `\xfe` in Python represent the byte `0xfe`. This is
useful for writing non printable characters (i.e. arbitrary bytes).

## Example 3 Instructions

This example is the most challenging, but it's equivalent to a real exploit you
might find "in the wild". Sending in data to it works the same way it did in
example 2.

Check out the online assembler here: https://defuse.ca/online-x86-assembler.htm
It will help a lot with this problem (you could also use local tools to do this,
if you prefer).

The hints directory contains some help for ex3 if you really get stuck.

## Using Objdump

`objdump` is an incredibly useful command that we can use to get information
about executable files.

These instructions are for LLVM objdump included with xcode, which differs
pretty substantially from GNU objdump. If you're using GNU objdump, you probably
want the `-d` flag to disassemble executable sections.

For LLVM objdump, running `objdump -macho -disassemble` on your executable will
show you code segments that look, for instance, like this:

```
_unsafe_bind_and_read_socket:
100000c40:  55            pushq %rbp
100000c41:  48 89 e5      movq  %rsp, %rbp
100000c44:  48 83 ec 50   subq  $80, %rsp
100000c48:  66 89 f0      movw  %si, %ax
```

The text that appears on a line of its own is a label; this allows code to say
"jump to this label" and actually mean "jump to the address immediately after
this label".  The first number (before the colon) is the address of that
instruction. The numbers after the colon is the instruction itself, and the text
following that is the disassembled machine code for that instruction. For
instance, our `_unsafe_bind_and_read_socket` begins at instruction `100000c40`
with the instruction to push the base pointer of the stack (the value in
register `%rbp`) onto the stack (`pushq`), which is represented in machine code
as `0x55`.

If you have GNU objdump instead, your output will look like this:

```
0000000100000c40 <_unsafe_bind_and_read_socket>:
   100000c40:    55                       push   %rbp
   100000c41:    48 89 e5                 mov    %rsp,%rbp
   100000c44:    48 83 ec 50              sub    $0x50,%rsp
   100000c48:    66 89 f0                 mov    %si,%ax
```

The astute will notice this is _more or less_ identical to the other. The
assembler syntax is a little different, but the addresses (which is what we care
about) should be identical.
