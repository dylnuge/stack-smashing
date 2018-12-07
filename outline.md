# Stack Smashing For Fun And Profit

### Overview

* Stack smashing is a form of buffer overflow

### Example 1: Variable Clobbering

Concepts Needed:
* Basic C programming
* Memory and pointers
* The Stack and the Heap
* ASCII
* Endianness

### Example 2: Overriding a Return Pointer

Concepts Needed:
* C Calling Convention
* Execution pointers
* Processor registers

### Example 3: Injecting Shell Code

Concepts Needed:
* Text segments (how programs execute)
* Basic assembly programming (especially jumps)
* The NOP sled

### Modern Examples and Preventatives

Concepts worth covering:
* Code (text) and data separation in memory (DEP)
* Randomized address spaces (ASLR, PIE)
* Compiler protections against overflows (e.g. gets warnings, canaries,
  clang's "safe stack")

Examples of stack exploits or similar conceptual things in the wild:
* Heartbleed (unbounded reads of process memory from unprivileged user)
* Super Mario World Speedruns!

### Further Reading

* PoC||GTFO
* Phrack
* DEFCON and CTFs
