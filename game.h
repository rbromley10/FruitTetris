#ifndef _GAME_H_
#define _GAME_H_

#include <stdlib.h>
#include <time.h>
#include "shape.h"
#include "board.h"

class Game
{
    private:
        int screenHeight;
        int nextType, nextRotation, nextX, nextY;
        //fruits boardFruits[BOARD_WIDTH][BOARD_HEIGHT];
        fruits nextFruits[4];

        Board *board;
        Shape *shape;

        int genRandNum(int floor, int ceiling);
        void setFruits(fruits shapeFruits[]);

        void initGame(void);

        void drawShape(int type, int rotation, int x, int y);
        void drawSquare(int x1, int y1, int x2, int y2, fruits f);
        void drawBoard(void);
        void clearScreen(void);

    public:
        // current shape data
        int curType, curRotation, curX, curY; 
        fruits curFruits[4];

        Game(Board *pBoard, Shape *pShape, int pScreenHeight);
        
        void drawGame(void);
        void nextShape(void);
        
        void restartGame(void);
};

#endif