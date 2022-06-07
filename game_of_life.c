#ifndef game_of_life_h
#include "game_of_life.h"
#endif

/**
 * Dashboard starts with zero values
 */
void init(int board[][HEIGHT])
{
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			*(*(board + i) + j) = 0;
}

/**
 *  add to a width index, wrapping around like a cylinder
 */
int xadd(int i, int a)
{
	i += a;
	while (i < 0)
		i += WIDTH;
	while (i >= WIDTH)
		i -= WIDTH;
	return i;
}

/* add to a height index, wrapping around */

int yadd(int i, int a)
{
	i += a;
	while (i < 0)
		i += HEIGHT;
	while (i >= HEIGHT)
		i -= HEIGHT;
	return i;
}

/**
 *  return the number of on cells adjacent to the i,j cell
 */
int adjacent_to(int board[][HEIGHT], int i, int j)
{
	int k, l, count, posx, posy;
	count = 0;

	/* go around the cell */
	for (k = -1; k <= 1; k++)
	{
		for (l = -1; l <= 1; l++)
			/* only count if at least one of k,l isn't zero */
			if (k || l)
			{
				posx = xadd(i, k);
				posy = yadd(j, l);
				if ((posx - i >= -1 && posx - i <= 1) && (posy - j >= -1 && posy - j <= 1))
					if (board[posx][posy])
						count++;
			}
	}

	return count;
}

/**
 * 1.STASIS : If, for a given cell, the number of on neighbours is
 * exactly two, the cell maintains its status quo into the next
 * generation. If the cell is on, it stays on, if it is off, it stays off.
 *
 * 2.GROWTH : If the number of on neighbours is exactly three, the cell
 * will be on in the next generation. This is regardless of the cell's
 * current state.
 *
 * 3.DEATH : If the number of on neighbours is 0, 1, 4-8, the cell will
 * be off in the next generation.
 */
void play(int board[][HEIGHT])
{
	int newboard[WIDTH][HEIGHT];

	/* for each cell, apply the rules of Life */

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			int a = adjacent_to(board, i, j); // MANDAMOS LA MATRIX POSX POSY
			if (a == 2)
				newboard[i][j] = board[i][j];
			if (a == 3)
				newboard[i][j] = 1;
			if (a < 2)
				newboard[i][j] = 0;
			if (a > 3)
				newboard[i][j] = 0;
		}
	}
	/* copy the new board back into the old board */

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
		{
			board[i][j] = newboard[i][j];
		}
}

/**
 * Add a line in printf
 */
int row_line()
{
	printf("\n");
	for (int i = 0; i < WIDTH; i++)
	{
		printf(" -----");
	}
	printf("\n");
}

/**
 * print the life board
 */
void print(int board[][HEIGHT], char message[])
{
	printf("\n%s\n", message);
	row_line();
	for (int i = 0; i < HEIGHT; i++)
	{
		printf(":");
		for (int j = 0; j < WIDTH; j++)
		{
			printf("  %c  :", *(*(board + i) + j) ? '+' : ' ');
		}
		row_line();
	}
}

/**
 * read a file into the life board
 */
void read_file(int board[][HEIGHT])
{
	FILE *file;
	char s[100];

	file = fopen("data.txt", "r");
	if (file == NULL)
	{
		puts("No se pudo abrir el archivo data.txt");
	}

	for (int i = 0; i < HEIGHT; i++)
	{
		/* get a string */
		fgets(s, 100, file);
		/* copy the string to the life board */
		for (int j = 0; j < WIDTH; j++)
		{
			*(*(board + i) + j) = s[j] == 'x';
		}
	}
	fclose(file);
}

int isAllDead(int board[][HEIGHT])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (*(*(board + i) + j) == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}