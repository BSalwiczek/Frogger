# Frogger game implementation in C++
## Game includes:
* Platforms: logs, turtles
* Enemies: swimming crocodiles, base crocodiles, cars
* Bonuses: little frog, bee
* TODO: snakes, dogs
## Reading levels from file
To create your own level just add text file named ```etapX.txt``` where X is next level number.
### File architecture:
Lines:  
1 – Time in seconds  
2,3,4 – Procentage chance of showing entities (entity is choosing random with this probability every second)  
5,6,7,8 – Number of logs in game (W), turtles (T), cars (C), crocodiles (K)  
Next bloks are setting position of object. Firstly goes line number with Y coordinate, next there are objects followed by X position, velocity and for
* logs and turtles – number of repetitions of middle part,
* cars – direction of movement (1 - right, 0 - left),
* crocodiles – nothing (just leave it random).
