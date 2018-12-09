So what does our stack look like when we're writing in?

```
|------- 4 bytes -------|
| username (0x00000000) |
|-----------------------|
| username (0x00000000) |
|-----------------------|
| username (0x00000000) |
|-----------------------|
|     frame pointer     |
|-----------------------|
|     frame pointer     |
|-----------------------|
|     return pointer    |
|-----------------------|
|     return pointer    |
|-----------------------|
```

By now you've hopefully figured out how to jump back to the top of the username
buffer. You might even be successfully putting the right value in %edi (you're
checking with `lldb` or `gdb`, right?).

So the final task and the trickiest part is to then call our `root_mode`
function.

Something worth ruminating on: Even though we've clobbered the frame pointer,
our stack pointer will actually still be immediately below the return pointer.
It's only the base pointer that contains garbage, and the x86 `ret` instruction
doesn't care about the base pointer.
