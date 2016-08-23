##### [ ] Horizontal redrawing issue
Currently, each segment undraws itself as it moves from one position to another. 
This causes graphical issues. As the leading segment moves to x=110,y=100 it attempts 
to undraw a 10x10 block in x=100,y=100. But this is precisely the block which the next 
segment wants to draw itself into.
The solution is fairly simple: only the tail segment needs to undraw itself, as every 
other segment will (hopefully) be moving into the space of every segment other than 
the tail.
As a happy consequence, only the head needs to draw itself. 
Really, if it weren't for the need to track collision between the head and the rest 
of the Snek, we wouldn't need to track anything but the head and the tail...