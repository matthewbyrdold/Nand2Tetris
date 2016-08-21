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
// Translation of VM class [Main]
// Defining function Main.fibonacci 0
(Main.fibonacci)
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
// push constant 2
@2
D = A
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
D = M-D
@LT_0
D;JLT
@SP
AM = M
M = 0
@LT_FIN_0
0;JMP
(LT_0)
@SP
AM = M
M = -1
(LT_FIN_0)
@SP
AM = M+1
// if go-to IF_TRUE
@SP
AM = M-1
D = M
@Main.fibonacci$IF_TRUE
D;JNE
// goto IF_FALSE
@Main.fibonacci$IF_FALSE
0;JMP
(Main.fibonacci$IF_TRUE)
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
(Main.fibonacci$IF_FALSE)
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
// push constant 2
@2
D = A
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
// Calling Main.fibonacci 1
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
@1
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Main.fibonacci
0;JMP  // Goto Main.fibonacci
(return-address1)
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
// push constant 1
@1
D = A
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
// Calling Main.fibonacci 1
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
@1
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Main.fibonacci
0;JMP  // Goto Main.fibonacci
(return-address2)
@SP
AM = M-1
D = M
@SP
AM = M-1
M = D+M
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
// push constant 4
@4
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// Calling Main.fibonacci 1
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
@1
D = D - A
@5
D = D - A
@ARG
M = D  // ARG = SP - numArgs - 5
@SP
D = M
@LCL
M = D  // LCL = SP
@Main.fibonacci
0;JMP  // Goto Main.fibonacci
(return-address3)
(Sys.init$WHILE)
// goto WHILE
@Sys.init$WHILE
0;JMP
