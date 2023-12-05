#include <iostream>
#include <vector>
#include "terminalBouncing.h"

using namespace std;

int width = 28; //Width of domain
int height = 18; //Height of domain
int iconX, iconY;
Vertical vert;
Horizontal hor;
int lastVert;
int lastHor;
vector<char> icons = { 'O','X','*','~' }; //Bouncing symbols
int i = 0;
char currentIcon = icons[i % icons.size()];

void Setup() //Initial move and position of symbol
{
    vert = Vertical::DOWN; //First direction of travel
    hor = Horizontal::RIGHT; //First direction of travel
    iconX = 1;
    iconY = 1;
}

void Draw()
{
    system("cls");//Clear screen
    for (int y = 0; y < height + 2; y++) { //Loop from top to bottom
        for (int x = 0; x < width + 2; x++) { //Loop from left to right
            if (y == 0 || y == height + 1) cout << "-"; //Print top and bottom border
            if ((x == 0 || x == width + 1) && (y != 0 && y != height + 1)) cout << "|"; //Print left and right border
            if (x == iconX && y == iconY) cout << currentIcon; //Print icon on screen
            else if ((y != 0 && y != height + 1) && (x != 0 && x != width + 1)) cout << " "; //Print space
        }
        cout << endl;
    }
    if (iconX == 1 || iconX == width || iconY == 1 || iconY == height) { //Change bouncing symbol every time symbol bounces from walls
        currentIcon = icons[i % icons.size()];
        i++;
    }
}

void Move() //Define new state - move with symbol
{
    if (iconX == 1 || iconX == width) //Change direction of travel at horizontal boundaries
        if (lastHor == 0) //0 is left
            hor = Horizontal::RIGHT;
        else
            hor = Horizontal::LEFT;

    if (iconY == 1 || iconY == height) //Change direction of travel at vertical boundaries
        if (lastVert == 0) //0 is up
            vert = Vertical::DOWN;
        else
            vert = Vertical::UP;

    //move with symbol, define next position for symbol
    if (vert == Vertical::UP) iconY--;
    else iconY++;
    if (hor == Horizontal::LEFT) iconX--;
    else iconX++;

    lastVert = static_cast<int>(vert);
    lastHor = static_cast<int>(hor);
}