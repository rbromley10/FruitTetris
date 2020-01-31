#include <GL/gl.h>
#include <GL/glut.h>
#include <unistd.h>
#include <time.h>
#include "board.h"
#include "game.h"
#include "shape.h"

#define K_MILLISECONDS 300
clock_t time1, time2;

Shape shape;
Board board(&shape, SCREEN_HEIGHT);
Game game(&board, &shape, SCREEN_HEIGHT);

void display(void) 
{
	// update board
    game.drawGame();
	glFlush();
	glutSwapBuffers();

	time2 = (clock() - time1);

	// game logic
	if (time2 > K_MILLISECONDS * 1000)
	{
		if (board.willCollide(game.curType, game.curRotation, game.curX, game.curY - 1))
		{
			board.saveShape(game.curType, game.curRotation, game.curX, game.curY);

			if (!board.canContinueGame())
				exit(0);

			game.nextShape();
		}
		else
		{
			game.curY--;
		}

		board.removeSquares();

		time1 = clock();
	}
}

void specialKeys(int key, int x, int y)
{
	int tmpRot;

	switch (key)
	{
		// move shape down one position
		case GLUT_KEY_DOWN:
			if (board.willCollide(game.curType, game.curRotation, game.curX, game.curY - 1))
			{
				board.saveShape(game.curType, game.curRotation, game.curX, game.curY);
				game.nextShape();
			}
			else
			{
				game.curY--;
			}
			break;

		// move shape left one position
		case GLUT_KEY_LEFT:
			if (!board.willCollide(game.curType, game.curRotation, game.curX - 1, game.curY))
			{
				game.curX--;
			}
			break;

		// move shape right one position
		case GLUT_KEY_RIGHT:
			if (!board.willCollide(game.curType, game.curRotation, game.curX + 1, game.curY))
			{
				game.curX++;
			}
			break;

		// rotation shape 90 degrees CCW
		case GLUT_KEY_UP:
			tmpRot = game.curRotation;
			if (tmpRot == 3)
			{
				tmpRot = 0;
			}
			else
			{
				tmpRot++;
			}

			if (!board.willCollide(game.curType, tmpRot, game.curX, game.curY) &&
				board.canRotateShape(game.curType, tmpRot, game.curX, game.curY))
			{
				if (game.curRotation == 3)
				{
					game.curRotation = 0;
				}
				else
				{
					game.curRotation++;
				}
			}
			break;
	}
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
		// quit the game
		case 'q':
			exit(0);
			break;

		// restart the game
		case 'r':
			game.restartGame();
			break;
	}
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);

	// init window
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition (200, 200);
	glutInitWindowSize (400, 800);
	glutCreateWindow ("Riley's Tetris Game");

	// init viewspace
    glClearColor (0.0, 0.0, 0.0, 0.0);
	glMatrixMode (GL_PROJECTION);
	gluOrtho2D (0.0, ((BOARD_WIDTH * SQUARE_SIZE) + (BOARD_BORDER * 2)), 
				0.0, ((BOARD_HEIGHT * SQUARE_SIZE) + (BOARD_BORDER * 2)));
	
	time1 = clock();

	// start game-loop
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keys);
	glutIdleFunc(display);
	glutMainLoop ();
	return 0;

}