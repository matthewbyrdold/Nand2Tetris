// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

//	PSEUDOCODE
//
//	LOOP:
//	if KBD == 0, jump to LOOP
//	set every pixel to black
//	BLACKLOOP
//	if KBD != 0, jump to BLACKLOOP
//	set every pixel to white
//	jump to LOOP

(LOOP)

	//	if KBD == 0, jump to LOOP
	@KBD
	D = M
	@LOOP
	D;JEQ

	//	set every pixel to black
	// write 8192 blocks of black, starting from SCREEN
	@8192		// number of blocks to fill
	D = A
	@tofill
	M = D
	
	@SCREEN		// filler position
	D = A
	@fillpos
	M = D
	
	(BLACKFILL)
		@tofill		// exit loop if fill complete
		D = M
		@BLACKLOOP
		D;JEQ
	
		@fillpos	// set the next 16 pixels to black
		A = M
		M = -1
		
		@fillpos	// increment filler position
		D = M + 1
		M = D
		
		@tofill		// decrement fill counter
		M = M - 1
		
		@BLACKFILL
		0;JMP

	(BLACKLOOP)

		//	if KBD != 0, jump to BLACKLOOP
		@KBD
		D = M
		@BLACKLOOP
		D;JNE

		//	set every pixel to white
			// write 8192 blocks of white, starting from SCREEN
			@8192		// number of blocks to fill
			D = A
			@tofill
			M = D
	
			@SCREEN		// filler position
			D = A
			@fillpos
			M = D
	
			(WHITEFILL)
				@tofill		// exit loop if fill complete
				D = M
				@LOOP
				D;JEQ
	
				@fillpos	// set the next 16 pixels to black
				A = M
				M = 0
		
				@fillpos	// increment filler position
				D = M + 1
				M = D
		
				@tofill		// decrement fill counter
				M = M - 1
				
				@WHITEFILL
				0;JMP


