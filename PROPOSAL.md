# Proposal: Spaceshooting

## Synopsis

###Elements
My game will have 3 elements:
- A square spaceship at the bottom that moves horizontally by the user and constantly shoots missiles upward,
- Rectangular enemies that appear from the top of the screen and emit missiles in a random downward direction, and
- Circular missiles emitted by spaceship (green color) and enemies (red color). Enemies get destroyed when spaceship's missile collides with them while spaceship gets destroyed when enemies' missile collides with it. 

###Goal
The player's goal is to control the spaceship without colliding with enemies and enemies' missiles.  

###Game Play
The spaceship starts out at the center of the bottom of the screen. It is launched by the space key and then can be moved horizontally by the mouse.
As soon as the spaceship is launched, the enemies start to appear from the top of the screen; spaceship's vertical movement is reflected
by the enemies' downward movement. The spaceship fires missiles automatically at a constant speed until it collides with enemies 
or enemies' missiles. Once spaceship is destroyed, it will be sent back to original position, from which 
it can be launched again; all the enemies will be cleared from the screen as well. Throughout the game, the time 
that spaceship has travelled is displayed real-time on the top-right corner of the screen.


## Functional requirements
1.  The spaceship is placed at the center of the bottom of the screen and can't be moved until it is launched.
2.  The spaceship is launched by pressing the space key, after which the enemies will start to appear from the top of the screen.
3.  The spaceship starts to fire green missiles upward at a constant speed right after it is launched. 
5.  The spaceship's x-coordinate follows the mouse, while its y-coordinate is fixed. 
6.  The enemies appear from the top of the screen and keep moving down the screen. 
7.  Each enemy emits 5 red missiles downward with a random horizontal boost at a given y-coordinate on the screen. 
8.  All missiles disappear when they touch the four edges of the screen. 
9.  All enemies disappear when they touch the bottom of the screen. 
10. When missiles with the same color collide, they bounce off - velocity is reflected horizontally. 
11. When two missiles with different colors collide, they both disappear from the screen. 
12. When enemies collide with green missiles, it disappears from the screen.
13. When spaceship collides with red missiles or enemies, the screen becomes empty and spaceship will be reset to its starting position. 
14. The time will be displayed real-time at the top right corner of the screen. It freezes when spaceship gets destroyed and 
restarts from zero when the spaceship is launched again. 


## Open questions
1. How to make enemies keep appearing from the top?
 (the amount of them appearing, their initial positions)
2. How to display time on the screen and store time in the program? 
3. What rate of spaceship and enemies firing the missiles work the best? 
4. How to make enemies shoot missiles at a random angle downward?
5. How to initialize and update vector<missiles> and vector<enemies>? 


