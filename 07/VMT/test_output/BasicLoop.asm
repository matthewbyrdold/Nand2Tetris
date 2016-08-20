@0
D = A
@SP
AM = M
M = D
@SP
AM = M+1
@LCL
D = M
@0
D = D+A
@R13
M = D
@SP
AM = M-1
D = M
@R13
A = M
M = D
($LOOP_START)
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
@SP
AM = M-1
D = M
@SP
AM = M-1
M = D+M
@SP
AM = M+1
@LCL
D = M
@0
D = D+A
@R13
M = D
@SP
AM = M-1
D = M
@R13
A = M
M = D
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
@ARG
D = M
@0
D = D+A
@R13
M = D
@SP
AM = M-1
D = M
@R13
A = M
M = D
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
@$LOOP_START
D;JNE
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
