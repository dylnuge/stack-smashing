If you've read the comments in the source code, by now you've probably figured
out that our goal is to call the `root_mode` function with the value 0x41424344
in the %edi register.

If you haven't been already, using `gdb` or `lldb` to watch your code execute is
extremely useful. Here's a good primer on LLDB:
https://lldb.llvm.org/tutorial.html

Something important to note on 64 bit systems is that %edi is the lower 32 bits
of the register called %rdi.

Since we know the exact location that the username buffer we're writing into
starts at, it wouldn't be too hard to jump to _that_, would it? And what would
we do once we're there?
