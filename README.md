# Snake Game

## Introduction
This is a simple console-based Snake game implemented in C++. The game runs in the Windows terminal, where the player controls a snake using the `W`, `A`, `S`, and `D` keys to navigate and eat food while avoiding collisions with itself and the game boundary.

## Features
- Uses Windows-specific functions to control the console cursor and screen size.
- Implements a dynamic snake movement with the ability to change direction.
- Includes food spawning and score tracking.
- Ends when the snake collides with itself or the boundary.
- Displays the final and highest score, with an option to replay.

## Code Breakdown

### Libraries Used
```cpp
#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
```
- `#include <bits/stdc++.h>`: Includes all standard C++ libraries.
- `#include <conio.h>`: Used for detecting keypresses (`getch()` and `kbhit()`).
- `#include <windows.h>`: Provides Windows-specific functions like `Sleep()` and `SetConsoleCursorPosition()`.

### Global Variables & Constants
```cpp
#define MAX_LENGTH 1000
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';
int consoleWidth, consoleHeight;
```
- `MAX_LENGTH`: The maximum length of the snake.
- `DIR_*`: Constants for snake movement directions.
- `consoleWidth`, `consoleHeight`: Store console dimensions.
## Functions
- `initScreen()`: Initializes the console dimensions using `GetConsoleScreenBufferInfo()`.

- `gotoxy(int x, int y)`: Moves the cursor to a specific `(x, y)` position in the console using `SetConsoleCursorPosition()`.

### Struct: `Point`
```cpp
struct Point{
    int xCoord, yCoord;
    Point() {}
    Point(int x, int y) {
        xCoord = x;
        yCoord = y;
    }
};
```
- Represents a coordinate (x, y) used for snake segments and food.

### Class: `Snake`
```cpp
class Snake{
    int length;
    char direction;
    Point body[MAX_LENGTH];
```
- Stores the snake's length, direction, and body segments.
- Methods:
- - `changeDirection()`: Changes movement direction while preventing 180-degree turns.
- - `move()`: Updates snake position, checks for collisions, and handles food consumption.

### Class: `Board`
```cpp
class Board{
    Snake *snake;
    Point food;
    int score;
```
- Manages game logic, drawing, and food spawning.
- Methods:
- - `spawnFood()`: Generates random food locations.
- - `draw()`: Clears and redraws the game board.
- - `update()`: Moves the snake, checks for collisions, and updates the score.
- - `getInput()`: Detects user keypresses.

### `main()` Function
```cpp
int main(){
    srand(time(0));
    initScreen();
    Board *board = new Board();
    while(board->update()){
        board->getInput();
        board->draw();
        Sleep(80);
    }
    end();
    return 0;
}
```
- Initializes the game.
- Runs a loop that updates the snake's movement and checks for game-over conditions.
- Calls end() to display the final score and ask if the user wants to play again.

### `end()` Function
- Displays the game-over message, handles replay, and exits the program.