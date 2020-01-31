#include "board.h"

// PRIVATE

void Board::deleteRows()
{
    // traverse game board
	int height = BOARD_HEIGHT - 1;
	for (int y = height; y >= 0; y--)
	{	
		int x;
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			if (boardState[x][y] != FULL)
				break;
		}

        // remove full rows
		if (x == BOARD_WIDTH)
		{
			for (int y2 = y; y2 < BOARD_HEIGHT - 1; y2++)
			{
				for (int x2 = 0; x2 < BOARD_WIDTH; x2++)
				{
					boardState[x2][y2] = boardState[x2][y2 + 1];
                    boardFruits[x2][y2] = boardFruits[x2][y2 + 1];
				}
			}	
		}
	}
}

void Board::deleteHorizFruits()
{
    //traverse game board
	int height = BOARD_HEIGHT - 1;
    for (int y = height; y >= 0; y--)
	{	
		for (int x = 0; x < BOARD_WIDTH - 2; x++)
		{
			if (boardFruits[x][y] != FRUITS_TOTAL &&
				boardFruits[x][y] == boardFruits[x + 1][y] &&
                boardFruits[x][y] == boardFruits[x + 2][y])
            {
                // determine how many consective same-colour fruits there are
				int fruitsInARow = 3;
				for (int x2 = x + 2; x2 < BOARD_WIDTH; x2++)
				{
					if (boardFruits[x2][y] == boardFruits[x2 + 1][y])
						fruitsInARow++;
					else 
						break;
				}

				// delete the n consecutive fruits
				for (int x2 = x; x2 < x + fruitsInARow; x2++)
                {
                	for (int y2 = y; y2 < BOARD_HEIGHT - 1; y2++)
                	{
                        boardState[x2][y2] = boardState[x2][y2 + 1];
                        boardFruits[x2][y2] = boardFruits[x2][y2 + 1];
                    }
                }
            }
		}
	}
}

void Board::deleteVertFruits()
{
	// traverse game board
	int height = BOARD_HEIGHT - 1;
    for (int y = height; y >= 2; y--)
	{	
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (boardFruits[x][y] != FRUITS_TOTAL &&
				boardFruits[x][y] == boardFruits[x][y - 1] &&
                boardFruits[x][y] == boardFruits[x][y - 2])
            {
                // determine how many consective same-colour fruits there are
				int fruitsInACol = 3;
				for (int y2 = y - 2; y2 >= 0; y2--)
				{
					if (boardFruits[x][y2] == boardFruits[x][y2 - 1])
						fruitsInACol++;
					else 
						break;
				}

				// delete the n consecutive fruits
				for (int i = 0; i < fruitsInACol; i++)
                {
					for (int y2 = y - (fruitsInACol - 1); y2 < BOARD_HEIGHT - 1; y2++)
					{
                    	boardState[x][y2] = boardState[x][y2 + 1];
                    	boardFruits[x][y2] = boardFruits[x][y2 + 1];
                	}
				}
            }
		}
	}
}

void Board::deleteRDiagFruits()
{
    //traverse game board
	int height = BOARD_HEIGHT - 1;
	for (int y = height; y >= 2; y--)
	{
		for (int x = 0; x < BOARD_WIDTH - 2; x++)
		{
			if (boardFruits[x][y] != FRUITS_TOTAL &&
				boardFruits[x][y] == boardFruits[x + 1][y - 1] &&
                boardFruits[x][y] == boardFruits[x + 2][y - 2])
            {
				// determine how many consecutive same-colour fruits there are
				int fruitsInALine = 3;
				for (int x2 = x + 2, y2 = y - 2; (x2 < BOARD_WIDTH) && (y2 >= 0); x2++, y2--)
				{
					if (boardFruits[x2][y2] == boardFruits[x2 + 1][y2 - 1])
						fruitsInALine++;
					else
						break;
				}

				// delete n consecutive fruits
				for (int x2 = x, y2 = y; x2 < x + fruitsInALine; x2++, y2--)
                {
					for (int y3 = y2; y3 < BOARD_HEIGHT - 1; y3++)
					{
						boardState[x2][y3] = boardState[x2][y3 + 1];
                    	boardFruits[x2][y3] = boardFruits[x2][y3 + 1];	
					}
				}
			}
		}
	}
}

void Board::deleteLDiagFruits()
{
    //traverse game board
	int height = BOARD_HEIGHT - 1;
	for (int y = height; y >= 2; y--)
	{
		for (int x = 2; x < BOARD_WIDTH; x++)
		{
			if (boardFruits[x][y] != FRUITS_TOTAL &&
				boardFruits[x][y] == boardFruits[x - 1][y - 1] &&
                boardFruits[x][y] == boardFruits[x - 2][y - 2])
            {
				// determine how many consecutive same-colour fruits there are
				int fruitsInALine = 3;
				for (int x2 = x - 2, y2 = y - 2; (x2 >= 0) && (y2 >= 0); x2--, y2--)
				{
					if (boardFruits[x2][y2] == boardFruits[x2 - 1][y2 - 1])
						fruitsInALine++;
					else
						break;
				}

				// delete n consecutive fruits
				for (int x2 = x, y2 = y; x2 > x - fruitsInALine; x2--, y2--)
                {
					for (int y3 = y2; y3 < BOARD_HEIGHT - 1; y3++)
					{
						boardState[x2][y3] = boardState[x2][y3 + 1];
                    	boardFruits[x2][y3] = boardFruits[x2][y3 + 1];	
					}
				}
			}
		}
	}
}

// PUBLIC

Board::Board (Shape *pShape, int pScreenHeight)
{
	// prepare board object
	screenHeight = pScreenHeight;
	shape = pShape;

	initBoard();
}

void Board::initBoard()
{
	// set all squares in board as empty
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			boardState[x][y] = EMPTY;
			boardFruits[x][y] = FRUITS_TOTAL;
		}
	}
}

int Board::getXScreenPos(int x)
{
	// get the pixel coordinate of corresponding to x on the board
    return ((SCREEN_HORIZ_CENTER - (SQUARE_SIZE * (BOARD_WIDTH / 2))) 
				+ (x * SQUARE_SIZE));
}

int Board::getYScreenPos(int y)
{
	// get the pixel coordinate of corresponding to y on the board
    return ((SCREEN_HEIGHT - (SQUARE_SIZE * BOARD_HEIGHT)) 
				+ (y * SQUARE_SIZE));
}

int Board::getBoardState(int x, int y)
{
	// get current state of the board at (x, y)
	return boardState[x][y];
}

void Board::setBoardState(int x, int y, int state)
{
	// set state of (x, y)
	boardState[x][y] = state;
}

fruits Board::getBoardFruits(int x, int y)
{
	// get fruit at (x, y)
	return boardFruits[x][y];
}

void Board::setBoardFruits(int x, int y, fruits fruit)
{
	// set fruit at (x, y)
	boardFruits[x][y] = fruit;
}

void Board::saveShape(int type, int rotation, int x, int y)
{
	// traverse every square in the 4x4 matrix that is each shape
	for (int i = 0; (y + i) < (y + SQUARES_IN_SHAPE); i++)
	{
		for (int j = 0; (x + j) < (x + SQUARES_IN_SHAPE); j++)
		{
			// set the squares in the board that are part of the shape to filled
			if (shape->getShape(type, rotation, i, j) != 0)
				boardState[x + j][y + i] = FULL;
		}
	}
}

void Board::removeSquares()
{
	// all deletion functions
	deleteHorizFruits();
	deleteVertFruits();
	deleteRDiagFruits();
	deleteLDiagFruits();
	deleteRows();
}

bool Board::isPosEmpty(int x, int y)
{
	// check if the square is empty
	return (bool)boardState[x][y];
}

bool Board::willCollide(int type, int rotation, int x, int y)
{
	// traverse every square in the 4x4 matrix that is each shape
	for (int i = 0; (y + i) < (y + SQUARES_IN_SHAPE); i++)
	{
		for (int j = 0; (x + j) < (x + SQUARES_IN_SHAPE); j++)
		{
			// check for possible out of bounds (left, right, or bottom)
			if (((x + j) < 0 || (x + j) > (BOARD_WIDTH - 1) || (y + i) < 0) && 
				(shape->getShape(type, rotation, i, j) != 0)) 
			{
				return true;
			}

			// check for shape collision
			if ((y + i)	<= shape->getYInitPos(type, rotation))
				if ((shape->getShape(type, rotation, i, j) != 0) && !isPosEmpty((x + j), (y + i)))
					return true;
		}
	}
	// No collision
	return false;
}

bool Board::canRotateShape(int type, int rotation, int x, int y)
{
	// traverse every square in the 4x4 matrix that is each shape
	for (int i = 0; (y + i) < (y + SQUARES_IN_SHAPE); i++)
	{
		for (int j = 0; (x + j) < (x + SQUARES_IN_SHAPE); j++)
		{
			// check for possible out of bounds (left, right, or bottom)
			if (((y + i) > BOARD_HEIGHT - 1) && 
				(shape->getShape(type, rotation, i, j) != 0)) 
			{
				return false;
			}
		}
	}
	// No collision
	return true;
}

bool Board::canContinueGame()
{
	for (int x = 0; x < BOARD_WIDTH; x++)
	{
		if (boardState[x][BOARD_HEIGHT - 2] == FULL)
			return false;
	}
	return true;
}





