# Frogger game implementation in C++
## Game includes:
* Platforms: logs, turtles
* Enemies: swimming crocodiles, base crocodiles, cars
* Bonuses: little frog, bee
* TODO: snakes, dogs
## Reading levels from file.
To create your own level just add text file named ```etapX.txt``` where X is next level number.
### File architecture:
Lines:  
1)Time in seconds  
2,3,4) Procentage chance of showing entities (etity is choosing random with this probability every second)  
5,6,7,8) Number of logs in game (W), turtles (T), cars (C), crocodiles (K)  
Next bloks are setting position of object. Firstly goes line number with Y coordinate, next there are objects followed by X position, velocity and for
* logs and turtles - amount of middle part
* cars - direction
* crocodiles - nothing (just leave it random)
