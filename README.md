# amiralBatti
# Battleship Text Game

This project implements a simple one-sided Battleship game in C++.
The player first places ships on a 10x10 board. Then another player
enters coordinates to fire at these ships. After each shot the files
`1stships.txt` and `2ndaim.txt` are updated to show the current state
of the game.

## Building

```
g++ -std=c++17 -Wall -Wextra battleship.cpp -o battleship
```

## Running

Run the produced executable. Follow the prompts to enter coordinates.
The boards are saved to `1stships.txt` and `2ndaim.txt`.