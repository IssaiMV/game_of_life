#ifndef game_of_life_h
#include "game_of_life.h"
#endif

int get_random()
{
	return rand() % 2;
}
/**
 * Dashboard starts with zero values
 */
void init(Table *board, int mode)
{
	board->table_of_cell = (Cell **)(malloc(board->rows * sizeof(Cell *)));
	for (int i = 0; i < board->rows; i++)
	{
		*(board->table_of_cell + i) = (Cell *)(malloc(board->columns * sizeof(Cell)));
		for (int j = 0; j < board->columns; j++)
		{
			// board->table_of_cell[i][j].is_alive = 0;
			// board->table_of_cell[i][j].counter_neighbor = 0;
			if (mode != 1)
				(*(board->table_of_cell + i) + j)->is_alive = 0;
			else
				(*(board->table_of_cell + i) + j)->is_alive = get_random();
			(*(board->table_of_cell + i) + j)->counter_neighbor = 0;
		}
	}
}

/**
 *  add to a width index, wrapping around like a cylinder
 */
int xadd(int i, int a, int rows)
{
	i += a;
	while (i < 0)
		i += rows;
	while (i >= rows)
		i -= rows;
	return i;
}

/* add to a height index, wrapping around */

int yadd(int i, int a, int columns)
{
	i += a;
	while (i < 0)
		i += columns;
	while (i >= columns)
		i -= columns;
	return i;
}

/**
 *  return the number of on cells adjacent to the i,j cell
 */
void adjacent_to(Table *board, int i, int j)
{
	int k, l, posx, posy;

	/* go around the cell */
	for (k = -1; k <= 1; k++)
	{
		for (l = -1; l <= 1; l++)
			/* only count if at least one of k,l isn't zero */
			if (k || l)
			{
				posx = xadd(i, k, board->rows);
				posy = yadd(j, l, board->columns);
				if ((posx - i >= -1 && posx - i <= 1) && (posy - j >= -1 && posy - j <= 1))
					if (board->table_of_cell[posx][posy].is_alive)
						board->table_of_cell[i][j].counter_neighbor++;
			}
	}
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
void play(Game_Of_Life *game)
{
	Table *board = &game->table;
	Cell newboard[board->rows][board->columns];

	/* for each cell, apply the rules of Life */

	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->columns; j++)
		{
			adjacent_to(board, i, j); // MANDAMOS LA MATRIX POSX POSY
			if (board->table_of_cell[i][j].counter_neighbor == 2)
				newboard[i][j].is_alive = board->table_of_cell[i][j].is_alive;
			if (board->table_of_cell[i][j].counter_neighbor == 3)
				newboard[i][j].is_alive = 1;
			if (board->table_of_cell[i][j].counter_neighbor < 2)
				newboard[i][j].is_alive = 0;
			if (board->table_of_cell[i][j].counter_neighbor > 3)
				newboard[i][j].is_alive = 0;
		}
	}
	/* copy the new board back into the old board */

	for (int i = 0; i < board->rows; i++)
		for (int j = 0; j < board->columns; j++)
		{
			board->table_of_cell[i][j].is_alive = newboard[i][j].is_alive;
			board->table_of_cell[i][j].counter_neighbor = 0;
		}
	game->generation++;
}

/**
 * Add a line in printf
 */
int row_line(int columns)
{
	printf("\n");
	for (int i = 0; i < columns; i++)
	{
		printf(" -----");
	}
	printf("\n");
}

/**
 * print the life board
 */
void print_table(Table *board, char message[], int generation)
{
	if (generation == 0)
		printf("\n%s\n", message);
	else
		printf("\n%s %d\n", message, generation);
	row_line(board->columns);
	for (int i = 0; i < board->rows; i++)
	{
		printf(":");
		for (int j = 0; j < board->columns; j++)
		{
			printf("  %c  :", (*(board->table_of_cell + i) + j)->is_alive ? '+' : ' ');
		}
		row_line(board->columns);
	}
}

/**
 * read a file into the life board
 */
void read_file(Table *board)
{
	FILE *file;
	char s[100];

	file = fopen("data.txt", "r");
	if (file == NULL)
	{
		puts("No se pudo abrir el archivo data.txt");
	}

	for (int i = 0; i < board->rows; i++)
	{
		/* get a string */
		fgets(s, 100, file);
		/* copy the string to the life board */
		for (int j = 0; j < board->columns; j++)
		{
			(*(board->table_of_cell + i) + j)->is_alive = s[j] == 'x';
		}
	}
	fclose(file);
}

int is_all_dead(Table *board)
{
	for (int i = 0; i < board->rows; i++)
	{
		for (int j = 0; j < board->columns; j++)
		{
			if ((*(board->table_of_cell + i) + j)->is_alive == 1)
			{
				return 0;
			}
		}
	}
	return 1;
}