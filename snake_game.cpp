#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>

using namespace std;

#define MAX_LENGTH 1000

const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;
    info.dwSize = 100;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void initScreen(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Point{
    int xCoord;
    int yCoord;
    Point(){}
    Point(int x, int y){
        xCoord = x;
        yCoord = y;
    }
};

class Snake{
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];
    Snake(int x, int y){
        length = 3;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    int getLength(){
        return length; 
    }

    void changeDirection(char newDirection){
        if(newDirection == DIR_UP && direction != DIR_DOWN){
            direction = newDirection;
        }
        else if(newDirection == DIR_DOWN && direction != DIR_UP){
            direction = newDirection;
        }
        else if(newDirection == DIR_LEFT && direction != DIR_RIGHT){
            direction = newDirection;
        }
        else if(newDirection == DIR_RIGHT && direction != DIR_LEFT){
            direction = newDirection;
        }
    }

    bool move(Point food){
        for(int i = length - 1; i > 0; i--){
            body[i] = body[i - 1];
        }
        switch(direction){
            case DIR_UP: body[0].yCoord--; break;
            case DIR_DOWN: body[0].yCoord++; break;
            case DIR_RIGHT: body[0].xCoord++; break;
            case DIR_LEFT: body[0].xCoord--; break;
        }

        //Snake bites itslef.
        for(int i = 1; i < length; i++){
            if(body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord){
                return false;
            }
        }
        
        //Snake touches boundary.
        if(body[0].xCoord <= 0 || body[0].xCoord >= consoleWidth - 1 || body[0].yCoord <= 0 || body[0].yCoord >= consoleHeight - 1){
            return false;
        }

        //Snake eats food.
        if(food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord){
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }
        return true;
    }
};

class Board{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const char FOOD = 'o';
    int score;

public:
    Board(){
        spawnFood();
        snake = new Snake(10, 10);
        score = 0;
    }

    ~Board(){
        delete snake;
    }

    int getScore(){
        return score;
    }

    void spawnFood(){
        int x = (rand() % (consoleWidth - 2)) + 1;
        int y = (rand() % (consoleHeight - 3)) + 2;
        food = Point(x, y);
    }

    // void displayCurrentScore(){
    //     gotoxy(consoleWidth / 2 - 7, 0);
    //     cout << "Current Score : " << score;
    // }
    void displayCurrentScore() {
        gotoxy(consoleWidth / 2 - 7, 0);
        setColor(14); // Yellow
        cout << "Current Score : " << score;
        setColor(7);  // Reset to default
    }

    // void draw(){
    //     static vector<Point> prevSnakeBody;
        
    //     // Erase the previous snake body
    //     for(Point p : prevSnakeBody){
    //         gotoxy(p.xCoord, p.yCoord);
    //         cout << " ";  // Erase previous position
    //     }
        
    //     prevSnakeBody.clear();
        
    //     // Draw new snake body
    //     for(int i = 0; i < snake->getLength(); i++){
    //         gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
    //         cout << SNAKE_BODY;
    //         prevSnakeBody.push_back(snake->body[i]);
    //     }
    
    //     // Draw food
    //     gotoxy(food.xCoord, food.yCoord);
    //     cout << FOOD;
    
    //     // Display score
    //     displayCurrentScore();
    // }
    
    void draw() {
        static vector<Point> prevSnakeBody;
    
        // Erase the previous snake body
        for (Point p : prevSnakeBody) {
            gotoxy(p.xCoord, p.yCoord);
            cout << " ";  // Erase previous position
        }
        prevSnakeBody.clear();
    
        // Draw new snake body
        setColor(10); // Green for snake
        for (int i = 0; i < snake->getLength(); i++) {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
            prevSnakeBody.push_back(snake->body[i]);
        }
        setColor(7); // Reset to default
    
        // Draw food
        setColor(12); // Red for food
        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;
        setColor(7); // Reset to default
    
        // Display score
        displayCurrentScore();
    }

    bool update(){
        bool isAlive = snake->move(food);
        if(!isAlive){
            return false;
        }
        if(food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord){
            score++;
            spawnFood();
        }
        return true;
    }

    void getInput(){
        if(kbhit()){
            int key = getch();
            if(key == 'w' || key == 'W'){
                snake->changeDirection(DIR_UP);
            }
            else if(key == 'a' || key == 'A'){
                snake->changeDirection(DIR_LEFT);
            }
            else if(key == 's' || key == 'S'){
                snake->changeDirection(DIR_DOWN);
            }
            else if(key == 'd' || key == 'D'){
                snake->changeDirection(DIR_RIGHT);
            }
        }
    }
};

void boundary() {
    setColor(9); // Light Blue for walls
    for (int i = 0; i < consoleWidth; i++) {  
        cout << static_cast<char>(219);
    }
    for (int i = 1; i < consoleHeight - 1; i++) { 
        gotoxy(0, i); cout << static_cast<char>(219);
        gotoxy(consoleWidth - 1, i); cout << static_cast<char>(219);
    }
    gotoxy(0, consoleHeight - 1);
    for (int i = 0; i < consoleWidth; i++) {  
        cout << static_cast<char>(219);
    }
    setColor(7); // Reset to default
}

// void boundary(){
//     for(int i = 0; i < consoleWidth; i++){  //^^
//         cout << static_cast<char>(219);
//     }
//     for(int i = 1; i < consoleHeight - 1; i++){ //<< >>
//         gotoxy(0, i); cout << static_cast<char>(219);
//         gotoxy(consoleWidth - 1, i); cout << static_cast<char>(219);
//     }
//     gotoxy(0, consoleHeight - 1);
//     for(int i = 0; i < consoleWidth; i++){ //vv
//         cout << static_cast<char>(219);
//     }
// }
void start(){
    system("cls");
    boundary();
    gotoxy(consoleWidth / 2 - 15, consoleHeight / 2 -5);
    cout << "=======  SNAKE GAME  =======";
    gotoxy(consoleWidth / 2 - 16, consoleHeight / 2 + 4);
    cout << "Press \"SPACE\" to start the game!!";
    gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 + 6);
    cout << "Press \"ESC\" to exit.";
    char choice = '+';
    while(choice != ' ' && choice != 27){
        choice = _getch();
    }
    int i = 3;
    if(choice == 27){
        system("cls");
        boundary();
        gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 - 1);
        cout << "Thanks for playing!!";
        while(i != -1){
            gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 + 1);
            cout << "Closing in " << i << " seconds.";
            Sleep(1000);
            i--;
        }
        system("cls");
        exit(0);
    }
}
void countdown(){
    system("cls");
    boundary();
    int n=3;
    while(n!=0){
        gotoxy(consoleWidth / 2 -8, consoleHeight / 2);
        cout << "Starting in " << n << "s";
        n--;
        Sleep(1000);
    }
    system("cls");
    boundary();
}
void end();
int hscr=0;

void game(){
    system("cls");
    countdown();
    Board *board = new Board();
    while(board->update()){
        board->getInput();
        board->draw();
        Sleep(70);
    }
    int scr = board->getScore();
    if(scr>hscr){
        hscr = scr;
    }
    gotoxy(consoleWidth / 2 - 17, consoleHeight / 2);
    cout << "Final score: " << scr << " || Highest Score: " << hscr;
    end();
}

void rules(){
    system("cls");
    boundary();
    gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 -9);
    cout << "=== HOW TO PLAY ===";
    gotoxy(consoleWidth / 2 - 35, consoleHeight / 2 -7);
    cout << "Use Controls 'W' 'A' 'S' 'D' on your keyboard to change direction of snake.";
    gotoxy(consoleWidth / 2 - 7, consoleHeight / 2 - 4);
    cout << "=== RULES ===";
    gotoxy(consoleWidth / 2 - 32, consoleHeight / 2 - 2);
    cout << "1. Food will randomly appear, eat to increase your snake size. ";
    gotoxy(consoleWidth / 2 - 32, consoleHeight / 2 - 1);
    cout << "2. If the head of the snake touches the boundary, GAME OVER!!";
    gotoxy(consoleWidth / 2 - 32, consoleHeight / 2);
    cout << "3. If the snake bites itself, GAME OVER!!";

    gotoxy(consoleWidth / 2 - 22, consoleHeight / 2+7);
    cout << "Compete with your friends, who scores the MOST!!";
    gotoxy(consoleWidth / 2 - 22, consoleHeight / 2+10);
    cout << "Press \"SPACE\" when you are ready to play the game.";
    char choice = '+';
    while(choice != ' '){
        choice = _getch();
    }
}

int main(){
    hideCursor();
    srand(time(0));
    initScreen();
    start();
    rules();
    game();
    return 0;
}

void end() {
    char choice = '-';
    gotoxy(consoleWidth / 2 - 8, consoleHeight / 2 - 2);
    
    setColor(12); // Red
    cout << "!! GAME OVER !!";
    setColor(7); // Reset to default
    
    gotoxy(consoleWidth / 2 - 9, consoleHeight / 2 + 2);
    
    setColor(14); // Yellow
    cout << "Play Again? (Y/N)";
    setColor(7); // Reset to default
    
    while (choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n') {
        choice = _getch();
    }

    if (choice == 'Y' || choice == 'y') {
        system("cls");
        game();
    } else {
        system("cls");
        boundary();
        int i = 3;
        gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 - 1);
        
        setColor(11); // Light Cyan
        cout << "Thanks for playing!!";
        setColor(7); // Reset to default
        
        while (i != -1) {
            gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 + 1);
            
            setColor(14); // Yellow
            cout << "Closing in " << i << " seconds.";
            setColor(7); // Reset to default
            
            Sleep(1000);
            i--;
        }
        system("cls");
        exit(0);
    }
}
// void end(){
//     char choice = '-';
//     gotoxy(consoleWidth / 2 - 8, consoleHeight / 2 - 2);
//     cout << "!! GAME OVER !!";
//     gotoxy(consoleWidth / 2 - 9, consoleHeight / 2 + 2);
//     cout << "Play Again? (Y/N)";
//     while(choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n'){
//         choice = _getch();
//     }
//     if(choice == 'Y' || choice == 'y'){
//         system("cls");
//         game();
//     } 
//     else{
//         system("cls");
//         boundary();
//         int i = 3;
//         gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 - 1);
//         cout << "Thanks for playing!!";
//         while(i != -1){
//             gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 + 1);
//             cout << "Closing in " << i << " seconds.";
//             Sleep(1000);
//             i--;
//         }
//         system("cls");
//         exit(0);
//     }
// }