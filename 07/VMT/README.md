# Virtual Machine Part 1#
Part 1 of the VM translator implementation. Represents Week 7's project for the NAND2Tetris course (see repo root for more info).

(✓ means that the test stage has been passed)

# Test-driven Development Process #

Dev Phase 1 : Stack Arithmetic
--------
Implement nine stack arithmetic and logical commands of the VM language and the 'push constant x' command.

Test file 1 (SimpleAdd): pushes and adds two constants. ✓

Test file 2 (StackTest): Executes a series of arithmetic and logical operations on the stack. ✓

Dev Phase 2 : Memory Access
--------
Full implementation of the VM language's push and pop commands and handling of all eight memory segments.

Test file 1 (BasicTest) : Executes pop and push operations using the virtual memory segments. ✓

Test file 2 (PointerTest) : Executes pop and push operations using the 'pointer', 'this' and 'that' segments. ✓

Test file 3 (Static Test) : Executes pop and push operations using the static segment. ✓ 