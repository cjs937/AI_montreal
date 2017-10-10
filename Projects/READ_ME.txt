Github link: https://github.com/cjs937/AI_montreal/tree/master/steering

In order to compile the project DeanLib and the directory containing the allegro5 folder need to be in the directory above of this one. After that everything should work fine.

Inputs:
A - Adds dynamic arrive entity that moves towards the player
S - Adds a wander and seek entity that wanders until player is in its range then seeks them
F - Adds a wander and flee entity that wanders until player is in its range then flees from them
D - Deletes a random unit from the scene. If the only unit left afterwards is the player the game closes
Esc - Closes and exits the game
Mouse Click - Moves the player to the click