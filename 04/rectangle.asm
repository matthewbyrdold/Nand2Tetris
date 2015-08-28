// file: rectangle.asm
// draws a 16-pixel wide, RAM[0] pixel tall rectangle
// (preload the height in RAM[0])

@SCREEN		// addr = SCREEN
D = A
@addr
M = D

@R0			// n = RAM[0]
D = M
@n
M = D

@i			// i = 0
M = 0

(LOOP)
// if i > n goto END
@i
D = M
@n
D = M - D
@END
D;JLT

// RAM[addr] = -1
@addr
A = M
M = -1

// advance to next row: addr = addr+32
D = A
@32
D = D + A
@addr
M = D

// i = i + 1
@i
M = M + 1

@LOOP
0;JMP

(END)
// goto END
@END
0;JMP