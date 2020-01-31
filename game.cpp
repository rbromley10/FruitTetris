
#include <GL/gl.h>
#include <GL/glut.h>
#include "game.h"
#include "shape.h"
#include "board.h"

// PRIVATE

int Game::genRandNum(int floor, int ceiling)
{
    // generate a random number between floor and ceiling
    return rand() % (ceiling - floor + 1) + floor;
}

void Game::setFruits(fruits shapeFruits[])
{
    // generate 4 random fruits for a shape
    for (int i = 0; i < FRUITS_TOTAL; i++)
    {
        shapeFruits[i] = (fruits)genRandNum(0, 4);
    }
}

void Game::initGame(void)
{
    srand(time(NULL));
    glClear (GL_COLOR_BUFFER_BIT);

    // current shape
    curType = genRandNum(0, 5);
    curRotation = genRandNum(0, 3);
    curX = genRandNum(shape->getXMinPos(curType, curRotation), 
                        shape->getXMaxPos(curType, curRotation));
    curY = shape->getYInitPos(curType, curRotation);
    setFruits(curFruits);

    // next shape
    nextType = genRandNum(0, 5);
    nextRotation = genRandNum(0, 3);
    setFruits(nextFruits);
}

void Game::drawShape(int type, int rotation, int x, int y)
{
    fruits squareFruit;

    int screenPosX = board->getXScreenPos(x);
    int screenPosY = board->getXScreenPos(y);

    // traverse all 16 squares of the 4x4 shape matrix
    for (int y = 0; y < SQUARES_IN_SHAPE; y++)
    {
        for (int x = 0; x < SQUARES_IN_SHAPE; x++) 
        {
            // set the fruits of the shape
            switch (shape->getShape(curType, curRotation, x, y))
            {
                case 1: 
                    squareFruit = curFruits[0];
                    break;
                case 2:
                    squareFruit = curFruits[1];
                    break;
                case 3:
                    squareFruit = curFruits[2];
                    break;
                case 4:
                    squareFruit = curFruits[3];
                    break;
            }

            // draw square
            if (shape->getShape(curType, curRotation, x, y) != 0)
            {
                drawSquare(screenPosX + (y * SQUARE_SIZE), 
                            screenPosY + (x * SQUARE_SIZE), 
                            (screenPosX + (y * SQUARE_SIZE)) + SQUARE_SIZE, 
                            (screenPosY + (x * SQUARE_SIZE)) + SQUARE_SIZE, 
                            squareFruit);
            }
        }
    }
}

void Game::drawSquare(int x1, int y1, int x2, int y2, fruits fruit)
{
    // set the fruit colour for the square
    switch (fruit) 
    {
		case APPLE:
			glColor3f (1.0, 0.0, 0.0);
			break;
    	case PEAR:
			glColor3f (0.0, 1.0, 0.0);
			break;
		case BANANA:
			glColor3f (1.0, 1.0, 0.0);
			break;
		case GRAPE:
			glColor3f (0.5, 0.0, 1.0);
			break;
        case ORANGE:
			glColor3f (1.0, 0.5, 0.0);
			break;
        case FRUITS_TOTAL: // this shouldn't ever happen, just satisfying compile warning
            glColor3f (0.0, 0.0, 0.0);
            break;
	}

    // draw the square
    glBegin (GL_POLYGON);
        glVertex2i (x1, y1);
        glVertex2i (x1, y2);
        glVertex2i (x2, y2);	
        glVertex2i (x2, y1);	
    glEnd ();
}

void Game::drawBoard()
{
    // draw saved shapes
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (!board->isPosEmpty(x, y))
            {
                drawSquare(BOARD_BORDER + (x * SQUARE_SIZE), 
                            BOARD_BORDER + (y * SQUARE_SIZE), 
                            BOARD_BORDER + (x * SQUARE_SIZE) + SQUARE_SIZE, 
                            BOARD_BORDER + (y * SQUARE_SIZE) + SQUARE_SIZE, 
                            board->getBoardFruits(x, y));
            }
        }
    }

    // draw baord's grid
	glColor3f (0.5, 0.5, 0.5);
	for (int i = BOARD_BORDER; i <= (BOARD_WIDTH * SQUARE_SIZE + SQUARE_SIZE - BOARD_BORDER); i += SQUARE_SIZE)
    {
		glBegin (GL_LINES);
			glVertex2i (i, BOARD_BORDER);
			glVertex2i (i, BOARD_HEIGHT * SQUARE_SIZE + SQUARE_SIZE - BOARD_BORDER);
		glEnd ();
	}
	for (int i = BOARD_BORDER; i <= (BOARD_HEIGHT * SQUARE_SIZE + SQUARE_SIZE - BOARD_BORDER); i += SQUARE_SIZE) 
    {
		glBegin (GL_LINES);
			glVertex2i (BOARD_BORDER, i);					
			glVertex2i (BOARD_WIDTH * SQUARE_SIZE + SQUARE_SIZE - BOARD_BORDER, i);						
		glEnd ();
	}	
}

void Game::clearScreen()
{
    // set the screen to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// PUBLIC

Game::Game(Board *pBoard, Shape *pShape, int pScreenHeight)
{
    // prepare game object
    board = pBoard;
    shape = shape;
    screenHeight = pScreenHeight;

    initGame();
}

void Game::drawGame()
{
    // clear and redraw the entire board state
    clearScreen();
    drawShape(curType, curRotation, curX, curY);
    drawBoard();
}

void Game::nextShape()
{
    // update saved fruits in board
    for (int i = 0; (curY + i) < (curY + SQUARES_IN_SHAPE); i++)
	{
		for (int j = 0; (curX + j) < (curX + SQUARES_IN_SHAPE); j++)
		{
			if (shape->getShape(curType, curRotation, i, j) != 0)
				board->setBoardFruits(curX + j, curY + i, curFruits[shape->getShape(curType, curRotation, i, j) - 1]);
		}
    }

    // set values of the new current shape
    curType = nextType;
    curRotation = nextRotation;
    curX = genRandNum(shape->getXMinPos(curType, curRotation), 
                        shape->getXMaxPos(curType, curRotation));
    curY = shape->getYInitPos(curType, curRotation);

    // check for possible next shape
    while (board->willCollide(curType, curRotation, curX, curY))
    {
        curType = nextType;
        curRotation = nextRotation;
        curX = genRandNum(shape->getXMinPos(curType, curRotation), 
                        shape->getXMaxPos(curType, curRotation));
        curY = shape->getYInitPos(curType, curRotation);
    }

    for (int i = 0; i < SQUARES_IN_SHAPE; i++)
    {
        curFruits[i] = nextFruits[i];
    }

    // prepare next shape
    nextType = genRandNum(0, 5);
    nextRotation = genRandNum(0, 3);
    setFruits(nextFruits);
}

void Game::restartGame()
{
    // restart the game
    clearScreen();
    initGame();
    board->initBoard();
}