# Virtual Machine #
Implementation of a VM which translates from an intermediary VM language to the HACK assembly language. Represents the projects for Week 7 and 8 of the NAND2Tetris course (see repo root for more info).

(✓ means that the test stage has been passed)

# Test-driven Development Process #

Dev Phase 1 : *Stack Arithmetic* ✓
--------
*Implement nine stack arithmetic and logical commands of the VM language and the 'push constant x' command.*

* Test file 1 (SimpleAdd): pushes and adds two constants. ✓

* Test file 2 (StackTest): Executes a series of arithmetic and logical operations on the stack. ✓

Dev Phase 2 : *Memory Access* ✓
--------
*Full implementation of the VM language's push and pop commands and handling of all eight memory segments.*

* Test file 1 (BasicTest) : Executes pop and push operations using the virtual memory segments. ✓

* Test file 2 (PointerTest) : Executes pop and push operations using the 'pointer', 'this' and 'that' segments. ✓

* Test file 3 (Static Test) : Executes pop and push operations using the static segment. ✓ 

Dev Phase 3 : *Program Flow*
--------
*Implementation of program flow commands.*

* Test file 1 (BasicLoop) : Computes 1 + 2 + ... + n, to test implementation of goto and if-goto commands. ✓

* Test file 2 (Fibonacci) : Computes the first n elements of the Fibonacci series. More intensive testing of branching commands. ✓

Dev Phase 4 : *Function Calling*
--------
*Implementation of function call processing (setting up stack frames, return values, bootstrapping, etc.).*

* Test file 1 (SimpleFunction) : Calls a simple math function and returns the result. ✓

* Test file 2 (FibonacciElement) : A full test of the function calling, bootstrap section, and most other VM commands. Split into multiple .vm files to test the translation of multiple .vm files to one .asm file.

* Test file 3 (StaticsTest) : A full test of the VM implementation's handling of static variables. Again split into multiple .vm files.
