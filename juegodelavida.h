#ifndef juegodelavida_h
#define juegodelavida_h
#include <stdio.h>
#define BOARD_WIDTH	5
#define BOARD_HEIGHT 5


/* set everthing to zero */
void initialize_board(int board[][BOARD_HEIGHT]);
/* add to a width index, wrapping around like a cylinder */
int xadd(int i, int a);
/* add to a height index, wrapping around */
int yadd(int i, int a);
/* return the number of on cells adjacent to the i,j cell */
int adjacent_to(int board[][BOARD_HEIGHT], int i, int j);
void play(int board[][BOARD_HEIGHT]);
int row_line();
/* print the life board */
void print(int board[][BOARD_HEIGHT]);
/* read a file into the life board */
void read_file(int board[][BOARD_HEIGHT], char *name);
#endif