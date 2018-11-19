# Stack Smashing For Fun And Profit

### Example 1: Variable Clobbering

Concepts Needed:
* Basic C programming
* Memory and pointers
* The Stack and the Heap
* ASCII

### Example 2: Overriding a Return Pointer

Concepts Needed:
* C Calling Convention
* Execution pointers
* Processor registers

### Example 3: Injecting Shell Code

Concepts Needed:
* Basic Assembly programming (especially jumps)

### Modern Preventatives

Concepts worth covering:
* Code (text) and data separation in memory
* Randomized address spaces (ASLR, PIE)
* Compiler protections against overflows (e.g. gets warnings, using heap instead
  of stack for larger pre-allocated buffers)
