// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively)

//	PSEUDOCODE:
//	Initialise variable 'multiplier', and set it as a copy of R1
//	Initialise result (R2) to 0
//	LOOP: 
//		if multiplier <= 0: jump to END
//		R[2] += R0
//		multiplier--
//		jump to LOOP
//	END:
//		jump to END


//		Initialise variable 'multiplier', and set it as a copy of R1
@R1
D = M
@multiplier
M = D

//		Initialise product (R2) to 0
@R2
M = 0

(LOOP)
//		if multiplier == 0: jump to END
@multiplier
D = M
@END
D;JLE

//		R[2] += R0
@R0
D = M
@R2
M = M + D

//		multiplier--
@multiplier
M = M - 1

//		jump to LOOP
@LOOP
0;JMP


(END)
//		jump to END
@END
0;JMP