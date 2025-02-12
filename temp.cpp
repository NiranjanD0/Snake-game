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

void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct Point
{
    int xCoord;
    int yCoord;
    Point() {}
    Point(int x, int y)
    {
        xCoord = x;
        yCoord = y;
    }
};

class Snake
{
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];
    Snake(int x, int y)
    {
        length = 3;
        body[0] = Point(x, y);
        direction = DIR_RIGHT;
    }

    int getLength()
    {
        return length;
    }

    void changeDirection(char newDirection)
    {
        if (newDirection == DIR_UP && direction != DIR_DOWN)
        {
            direction = newDirection;
        }
        else if (newDirection == DIR_DOWN && direction != DIR_UP)
        {
            direction = newDirection;
        }
        else if (newDirection == DIR_LEFT && direction != DIR_RIGHT)
        {
            direction = newDirection;
        }
        else if (newDirection == DIR_RIGHT && direction != DIR_LEFT)
        {
            direction = newDirection;
        }
    }

    bool move(Point food)
    {
        for (int i = length - 1; i > 0; i--)
        {
            body[i] = body[i - 1];
        }
        switch (direction)
        {
        case DIR_UP:
            body[0].yCoord--;
            break;
        case DIR_DOWN:
            body[0].yCoord++;
            break;
        case DIR_RIGHT:
            body[0].xCoord++;
            break;
        case DIR_LEFT:
            body[0].xCoord--;
            break;
        }

        // Snake bites itslef.
        for (int i = 1; i < length; i++)
        {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord)
            {
                return false;
            }
        }

        // Snake touches boundary.
        if (body[0].xCoord <= 0 || body[0].xCoord >= consoleWidth - 1 || body[0].yCoord <= 1 || body[0].yCoord >= consoleHeight - 1)
        {
            return false;
        }

        // Snake eats food.
        if (food.xCoord == body[0].xCoord && food.yCoord == body[0].yCoord)
        {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++;
        }
        return true;
    }
};

class Board
{
    Snake *snake;
    const char SNAKE_BODY = 'O';
    Point food;
    const string FOOD = "🍎"; // Use Apple Emoji for food
    int score;

public:
    Board()
    {
        spawnFood();
        snake = new Snake(10, 10);
        score = 0;
    }

    ~Board()
    {
        delete snake;
    }

    int getScore()
    {
        return score;
    }

    void spawnFood()
    {
        int x = (rand() % (consoleWidth - 2)) + 1;
        int y = (rand() % (consoleHeight - 3)) + 2;
        food = Point(x, y);
    }

    void displayCurrentScore()
    {
        gotoxy(consoleWidth / 2 - 5, 0);
        cout << "Current Score : " << score;
    }

    void draw()
    {
        system("cls");
        displayCurrentScore();
        gotoxy(0, 1);
        for (int i = 0; i < consoleWidth; i++)
        {
            cout << "#";
        }
        for (int i = 2; i < consoleHeight - 1; i++)
        {
            gotoxy(0, i);
            cout << "#";
            gotoxy(consoleWidth - 1, i);
            cout << "#";
        }
        gotoxy(0, consoleHeight - 1);
        for (int i = 0; i < consoleWidth; i++)
        {
            cout << "#";
        }
        for (int i = 0; i < snake->getLength(); i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }
        class Board
        {
            Snake *snake;
            const char SNAKE_BODY = 'O';
            Point food;
            const string FOOD = "🍎"; // Use Apple Emoji
            int score;

        public:
            Board()
            {
                snake = new Snake(10, 10);
                score = 0;
                spawnFood();
            }

            ~Board()
            {
                delete snake;
            }

            void spawnFood()
            {
                int x = (rand() % (consoleWidth - 2)) + 1;
                int y = (rand() % (consoleHeight - 3)) + 2;
                food = Point(x, y);
            }

            void displayCurrentScore()
            {
                gotoxy(consoleWidth / 2 - 5, 0);
                cout << "Current Score : " << score;
            }

            void draw()
            {
                system("cls");
                displayCurrentScore();

                gotoxy(0, 1);
                for (int i = 0; i < consoleWidth; i++)
                {
                    cout << "#";
                }
                for (int i = 2; i < consoleHeight - 1; i++)
                {
                    gotoxy(0, i);
                    cout << "#";
                    gotoxy(consoleWidth - 1, i);
                    cout << "#";
                }
                gotoxy(0, consoleHeight - 1);
                for (int i = 0; i < consoleWidth; i++)
                {
                    cout << "#";
                }

                for (int i = 0; i < snake->getLength(); i++)
                {
                    gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
                    cout << SNAKE_BODY;
                }

                gotoxy(food.xCoord, food.yCoord);
                cout << FOOD; // Display Apple Emoji 🍎
            }
        };

    public:
        Board()
        {
            spawnFood();
            snake = new Snake(10, 10);
            score = 0;
        }

        void draw()
        {
            system("cls");
            displayCurrentScore();
            gotoxy(0, 1);
            for (int i = 0; i < consoleWidth; i++)
            {
                cout << "#";
            }
            for (int i = 2; i < consoleHeight - 1; i++)
            {
                gotoxy(0, i);
                cout << "#";
                gotoxy(consoleWidth - 1, i);
                cout << "#";
            }
            gotoxy(0, consoleHeight - 1);
            for (int i = 0; i < consoleWidth; i++)
            {
                cout << "#";
            }
            for (int i = 0; i < snake->getLength(); i++)
            {
                gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
                cout << SNAKE_BODY;
            }
            gotoxy(food.xCoord, food.yCoord);
            cout << FOOD; // Displays Apple Emoji 🍎
        }
    };

}

bool
update()
{
    bool isAlive = snake->move(food);
    if (!isAlive)
    {
        return false;
    }
    if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
    {
        score++;
        spawnFood();
    }
    return true;
}

void getInput()
{
    if (kbhit())
    {
        int key = getch();
        if (key == 'w' || key == 'W')
        {
            snake->changeDirection(DIR_UP);
        }
        else if (key == 'a' || key == 'A')
        {
            snake->changeDirection(DIR_LEFT);
        }
        else if (key == 's' || key == 'S')
        {
            snake->changeDirection(DIR_DOWN);
        }
        else if (key == 'd' || key == 'D')
        {
            snake->changeDirection(DIR_RIGHT);
        }
    }
}
}
;

void end();
int hscr = 0;

int main()
{
    srand(time(0));
    initScreen();
    Board *board = new Board();
    while (board->update())
    {
        board->getInput();
        board->draw();
        Sleep(80);
    }
    int scr = board->getScore();
    if (scr > hscr)
    {
        hscr = scr;
    }
    gotoxy(consoleWidth / 2 - 17, consoleHeight / 2);
    cout << "Final score: " << scr << " || Highest Score: " << hscr;
    end();
    return 0;
}

void end()
{
    char choice = '-';
    gotoxy(consoleWidth / 2 - 8, consoleHeight / 2 - 2);
    cout << "!! GAME OVER !!";
    gotoxy(consoleWidth / 2 - 9, consoleHeight / 2 + 2);
    cout << "Play Again? (Y/N)";
    while (choice != 'y' && choice != 'Y' && choice != 'N' && choice != 'n')
    {
        choice = _getch();
    }
    if (choice == 'Y' || choice == 'y')
    {
        system("cls");
        main();
    }
    else
    {
        system("cls");
        for (int i = 0; i < consoleWidth; i++)
        { //^^
            cout << "#";
        }
        for (int i = 1; i < consoleHeight - 1; i++)
        { //<< >>
            gotoxy(0, i);
            cout << "#";
            gotoxy(consoleWidth - 1, i);
            cout << "#";
        }
        gotoxy(0, consoleHeight - 1);
        for (int i = 0; i < consoleWidth; i++)
        { // vv
            cout << "#";
        }
        int i = 3;
        gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 - 1);
        cout << "Thanks for playing!!";
        while (i != -1)
        {
            gotoxy(consoleWidth / 2 - 10, consoleHeight / 2 + 1);
            cout << "Closing in " << i << " seconds.";
            Sleep(1000);
            i--;
        }
        system("cls");
        exit(0);
    }
}