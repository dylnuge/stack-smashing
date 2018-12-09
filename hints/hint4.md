What does your assembly code look like? Is it something like this?

```
mov edi,0x41424344
ret
```

If so, you're very close to there. If not, consider why that code might work.


Also now's a good point to remind you to double check your inputs. It's easy to
have a typo in your code that's hard to notice when it's just numbers. Pay extra
special attention to endianness.
