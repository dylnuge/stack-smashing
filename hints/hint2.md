What's the distance from the start of the username buffer to the return pointer?
If you said 20 bytes, you're right! It's 8 bytes for the frame pointer and 12
bytes for our username buffer.

But don't forget, _some_ of those bytes contain your assembly code. So subtract
out the length of your assembly code when adding your padding.
