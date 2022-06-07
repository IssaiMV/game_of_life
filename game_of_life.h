#ifndef game_of_life_h
#define game_of_life_h
#include <stdio.h>

#define WIDTH 5
#define HEIGHT 5

/**
 * Dashboard starts with zero values
 */
void init(int board[][HEIGHT]);
/**
 *  add to a width index, wrapping around like a cylinder
 */
int xadd(int i, int a);
/**
 *  add to a height index, wrapping around
 */
int yadd(int i, int a);
/**
 *  return the number of on cells adjacent to the i,j cell
 */
int adjacent_to(int board[][HEIGHT], int i, int j);
/**
 * Play game of life
 */
void play(int board[][HEIGHT]);
/**
 * Add a line in printf
 */
int row_line();
/**
 * print the life board
 */
void print(int board[][HEIGHT], char message[]);
/**
 * read a file into the life board
 */
void read_file(int board[][HEIGHT]);

int isAllDead(int board[][HEIGHT]);
#include "game_of_life.c"
#endif
