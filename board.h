#ifndef _BOARD_H_
#define _BOARD_H_

#include "shape.h"

#define SQUARE_SIZE 10	
#define SQUARES_IN_SHAPE 5
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20	
#define SCREEN_HORIZ_CENTER 55
#define SCREEN_HEIGHT 210
#define BOARD_BORDER ((SCREEN_HEIGHT - (BOARD_HEIGHT * SQUARE_SIZE)) / 2)

enum posStates {FULL, EMPTY};

class Board 
{
    private:
        int boardState[BOARD_WIDTH][BOARD_HEIGHT];
        fruits boardFruits[BOARD_WIDTH][BOARD_HEIGHT];
        int screenHeight;
        Shape *shape;

        void deleteRows(void);
        void deleteHorizFruits(void);
        void deleteVertFruits(void);
        void deleteRDiagFruits(void);
        void deleteLDiagFruits(void);

    public:
        Board(Shape *pShape, int pScreenHeight);

        void initBoard(void);

        int getXScreenPos(int x);
        int getYScreenPos(int y);

        int getBoardState(int x, int y);
        void setBoardState(int x, int y, int state);
        fruits getBoardFruits(int x, int y);
        void setBoardFruits(int x, int y, fruits fruit);

        void saveShape(int type, int rotation, int x, int y);
        void removeSquares(void);

        bool isPosEmpty(int x, int y);
        bool willCollide(int type, int rotation, int x, int y);
        bool canRotateShape(int type, int rotation, int x, int y);
        bool canContinueGame(void);
};

#endif