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
// Translation of VM class [Sys]
// Defining function Sys.init 0
(Sys.init)
// Calling Sys.main 0
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
@Sys.main
0;JMP  // Goto Sys.main
(return-address1)
// pop temp 1
@5
D = A
@1
D = A+D
@R13
M = D
@SP
AM = M-1
D = M
@R13
A = M
M = D
(Sys.init$LOOP)
@Sys.init$LOOP
0;JMP
// Defining function Sys.main 0
(Sys.main)
// push constant 123
@123
D = A
@SP
AM = M
M = D
@SP
AM = M+1
// Calling Sys.add12 1
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
@Sys.add12
0;JMP  // Goto Sys.add12
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
// push constant 246
@246
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
// Defining function Sys.add12 3
(Sys.add12)
@0
D = A
@SP
A = M
M = D
@SP
AM = M+1
@0
D = A
@SP
A = M
M = D
@SP
AM = M+1
@0
D = A
@SP
A = M
M = D
@SP
AM = M+1
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
// push constant 12
@12
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
