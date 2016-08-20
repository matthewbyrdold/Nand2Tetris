// Defining function SimpleFunction.test 2
(SimpleFunction.test)
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
// push local 0
@LCL
D = M
@0
A = D+A
D = M
@SP
AM = M
M = D
@SP
AM = M+1
// push local 1
@LCL
D = M
@1
A = D+A
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
M = D+M
@SP
AM = M+1
@SP
AM = M-1
D = M
M = !D
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
@SP
AM = M-1
D = M
@SP
AM = M-1
M = D+M
@SP
AM = M+1
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
@FRAME
M = D  // FRAME = LCL
@FRAME
D = M
@5
A = D - A
D = M
@RET
M = D  // RET = *(FRAME - 5)
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
@FRAME
D = M
@1
A = D - A
D = M
@THAT
M = D  // THAT = *(FRAME-1)
@FRAME
D = M
@2
A = D - A
D = M
@THIS
M = D  // THIS = *(FRAME-2)
@FRAME
D = M
@3
A = D - A
D = M
@ARG
M = D  // ARG = *(FRAME-3)
@FRAME
D = M
@4
A = D - A
D = M
@LCL
M = D  // LCL = *(FRAME-4)
@RET
A = M
0;JMP  // GOTO RET
