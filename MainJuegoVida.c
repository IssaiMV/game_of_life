/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbours 
 * a cell dies of loneliness, if it has less than two neighbours 
 * a cell dies of overcrowding, if it has more than three neighbours 
 * a cell survives to the next generation, if it does not die of loneliness 
 * or overcrowding 
 *
 * In my version, a 2D array of ints is used.  A 1 cell is on, a 0 cell is off.
 * The game plays 100 rounds, printing to the screen each time.  'x' printed
 * means on, space means 0.
 *
 */

//creates row boundary

#include "juegodelavida.h"
#define juegodelavida_h
//#include <unistd.h>

/* main program */

int main(int argc, char *argv[]) {
	puts(argv[1]);
	int	board[BOARD_WIDTH][BOARD_HEIGHT], i, j;

	initialize_board(board);
	read_file(board, argv[1]);

	/* play game of life 100 times */
	puts("\033[H\033[J");
	for(i=0; i<5; i++){
		print(board);
		play(board);
		/* clear the screen using VT100 escape codes */
		//sleep(2);
		//puts("\033[H\033[J");
	}
}