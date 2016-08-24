# Snek #
The ninth project for Nand2Tetris involves implementing a game using the Jack programming language in order to get to grips with the language in advance of writing the compiler and OS in later projects.

I decided to implement Snek, a version of the game 'Snake'. The user moves a snake around the screen, avoiding collision with its ever-larger body and collecting delishuz snacks which give points but cause the snek to grow.

(✓ means that the stage is complete)

Step 1 : *Multi-segment snek* ✓
--------
* A snake which moves around the screen in the last direction input, and which is composed of multiple segments. 

Step 2 : *Delishuz snacks* ✓
--------
* Delishuz snacks appear pseudo-randomly around the playing area. If the snek eats them it gains a segment (up to a yet-undecided maximum) is added.

Step 3 : *Teleporting Snek* ✓ 
--------
* Collision with a wall causes the Snek to appear on the other side of the playing field.

Step 4 : *Finishing touches* 
--------
* Collision with yourself causes game over. Points are awarded and tracked for eating delishuz snacks. 'NEW GAME' and 'GAME OVER' screens are shown at the beginning and end of the game.
