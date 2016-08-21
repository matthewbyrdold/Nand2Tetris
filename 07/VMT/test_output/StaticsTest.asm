// VMTRANSLATION: BOOTSTRAP
@256
D = A
@SP
M = D
// Calling Sys.init 0
@return-address0
D = A
@SP
A = M
M = D
@SP
AM = M+1
@LCL
D = M
@SP
A = M
M = D  // push LCL
@SP
AM = M+1
@ARG
D = M
@SP
A = M
M = D  // push ARG
@SP
AM = M+1
@THIS
D = M
@SP
A = M
M = D  // push THIS
@SP
AM = M+1
@THAT
D = M
@SP
A = M
M = D  // push THAT
@SP
AM = M+1
@SP
D = M
@0
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Sys.init
0;JMP  // Goto Sys.init
(return-address0)
// Translation of VM class [Class1]
// Defining function Class1.set 0
(Class1.set)
// push argument 0
@ARG
D = M
@0
A = D+A
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// pop static 0
@SP
AM = M-1
D = M
@Class1.0
M = D
// push argument 1
@ARG
D = M
@1
A = D+A
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// pop static 1
@SP
AM = M-1
D = M
@Class1.1
M = D
// push constant 0
@0
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// Return
@LCL
D = M
@frame
M = D  // frame = LCL
@frame
D = M
@5
A = D - A
D = M
@ret
M = D  // ret = *(frame - 5)
@SP
AM = M-1
D = M
@ARG
A = M
M = D  // *ARG = pop()
@ARG
D = M + 1
@SP
M = D  // SP = ARG+1
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D  // THAT = *(frame-1)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D  // THIS = *(frame-2)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D  // ARG = *(frame-3)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D  // LCL = *(frame-4)
@ret
A = M
0;JMP  // goto ret
// Defining function Class1.get 0
(Class1.get)
// push static 0
@Class1.0
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// push static 1
@Class1.1
D = M
@SP
AM = M
M = D
@SP
AM = M+1
@SP
AM = M-1
D = M
@SP
AM = M-1
M = M-D
@SP
AM = M+1
// Return
@LCL
D = M
@frame
M = D  // frame = LCL
@frame
D = M
@5
A = D - A
D = M
@ret
M = D  // ret = *(frame - 5)
@SP
AM = M-1
D = M
@ARG
A = M
M = D  // *ARG = pop()
@ARG
D = M + 1
@SP
M = D  // SP = ARG+1
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D  // THAT = *(frame-1)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D  // THIS = *(frame-2)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D  // ARG = *(frame-3)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D  // LCL = *(frame-4)
@ret
A = M
0;JMP  // goto ret
// Translation of VM class [Class2]
// Defining function Class2.set 0
(Class2.set)
// push argument 0
@ARG
D = M
@0
A = D+A
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// pop static 0
@SP
AM = M-1
D = M
@Class2.0
M = D
// push argument 1
@ARG
D = M
@1
A = D+A
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// pop static 1
@SP
AM = M-1
D = M
@Class2.1
M = D
// push constant 0
@0
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// Return
@LCL
D = M
@frame
M = D  // frame = LCL
@frame
D = M
@5
A = D - A
D = M
@ret
M = D  // ret = *(frame - 5)
@SP
AM = M-1
D = M
@ARG
A = M
M = D  // *ARG = pop()
@ARG
D = M + 1
@SP
M = D  // SP = ARG+1
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D  // THAT = *(frame-1)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D  // THIS = *(frame-2)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D  // ARG = *(frame-3)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D  // LCL = *(frame-4)
@ret
A = M
0;JMP  // goto ret
// Defining function Class2.get 0
(Class2.get)
// push static 0
@Class2.0
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// push static 1
@Class2.1
D = M
@SP
AM = M
M = D
@SP
AM = M+1
@SP
AM = M-1
D = M
@SP
AM = M-1
M = M-D
@SP
AM = M+1
// Return
@LCL
D = M
@frame
M = D  // frame = LCL
@frame
D = M
@5
A = D - A
D = M
@ret
M = D  // ret = *(frame - 5)
@SP
AM = M-1
D = M
@ARG
A = M
M = D  // *ARG = pop()
@ARG
D = M + 1
@SP
M = D  // SP = ARG+1
@frame
D = M
@1
A = D - A
D = M
@THAT
M = D  // THAT = *(frame-1)
@frame
D = M
@2
A = D - A
D = M
@THIS
M = D  // THIS = *(frame-2)
@frame
D = M
@3
A = D - A
D = M
@ARG
M = D  // ARG = *(frame-3)
@frame
D = M
@4
A = D - A
D = M
@LCL
M = D  // LCL = *(frame-4)
@ret
A = M
0;JMP  // goto ret
// Translation of VM class [Sys]
// Defining function Sys.init 0
(Sys.init)
// push constant 6
@6
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// push constant 8
@8
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// Calling Class1.set 2
@return-address1
D = A
@SP
A = M
M = D
@SP
AM = M+1
@LCL
D = M
@SP
A = M
M = D  // push LCL
@SP
AM = M+1
@ARG
D = M
@SP
A = M
M = D  // push ARG
@SP
AM = M+1
@THIS
D = M
@SP
A = M
M = D  // push THIS
@SP
AM = M+1
@THAT
D = M
@SP
A = M
M = D  // push THAT
@SP
AM = M+1
@SP
D = M
@2
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Class1.set
0;JMP  // Goto Class1.set
(return-address1)
// pop temp 0
@5
D = A
@0
D = A+D
@R13
M = D
@SP
AM = M-1
D = M
@R13
A = M
M = D
// push constant 23
@23
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// push constant 15
@15
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// Calling Class2.set 2
@return-address2
D = A
@SP
A = M
M = D
@SP
AM = M+1
@LCL
D = M
@SP
A = M
M = D  // push LCL
@SP
AM = M+1
@ARG
D = M
@SP
A = M
M = D  // push ARG
@SP
AM = M+1
@THIS
D = M
@SP
A = M
M = D  // push THIS
@SP
AM = M+1
@THAT
D = M
@SP
A = M
M = D  // push THAT
@SP
AM = M+1
@SP
D = M
@2
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Class2.set
0;JMP  // Goto Class2.set
(return-address2)
// pop temp 0
@5
D = A
@0
D = A+D
@R13
M = D
@SP
AM = M-1
D = M
@R13
A = M
M = D
// Calling Class1.get 0
@return-address3
D = A
@SP
A = M
M = D
@SP
AM = M+1
@LCL
D = M
@SP
A = M
M = D  // push LCL
@SP
AM = M+1
@ARG
D = M
@SP
A = M
M = D  // push ARG
@SP
AM = M+1
@THIS
D = M
@SP
A = M
M = D  // push THIS
@SP
AM = M+1
@THAT
D = M
@SP
A = M
M = D  // push THAT
@SP
AM = M+1
@SP
D = M
@0
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Class1.get
0;JMP  // Goto Class1.get
(return-address3)
// Calling Class2.get 0
@return-address4
D = A
@SP
A = M
M = D
@SP
AM = M+1
@LCL
D = M
@SP
A = M
M = D  // push LCL
@SP
AM = M+1
@ARG
D = M
@SP
A = M
M = D  // push ARG
@SP
AM = M+1
@THIS
D = M
@SP
A = M
M = D  // push THIS
@SP
AM = M+1
@THAT
D = M
@SP
A = M
M = D  // push THAT
@SP
AM = M+1
@SP
D = M
@0
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Class2.get
0;JMP  // Goto Class2.get
(return-address4)
(Sys.init$WHILE)
@Sys.init$WHILE
0;JMP
