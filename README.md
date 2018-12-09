# Stack Smashing (For Fun and Profit)

Slides are in the keynote file.

This is tested under MacOS Mojave (10.14) and MacOS High Sierra (10.13).

In order to build the code, you'll need to install the Xcode CLI tools, which
should include `make`, `clang`, `ld`, `objdump`, and `nc`.

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

You can write to a file socket using `nc -U socket`. You probably want to write
a few non-printable bytes to it; `python` is super handy for this. Here's an
example of using Python 2 to write the hex 0xfeedface to a unix socket:

```
nc -U socket <<< `python -c "print '\xfe\xed\xfa\xce'"`
```

Note the backticks around the Python part of that command. That will take the
output of the python command and send it to the shell; in turn, the `<<<` will
redirect _that_ into netcat's standard in.

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
assembler syntax is different.