#include "juegodelavida.h"
/* dimensions of the screen */

/* set everthing to zero */

void initialize_board (int board[][BOARD_HEIGHT]) {
	int	i, j;
	for (i=0; i<BOARD_WIDTH; i++) 
		for (j=0; j<BOARD_HEIGHT; j++) 
			board[i][j] = 0;
}

/* add to a width index, wrapping around like a cylinder */

int xadd (int i, int a) {
	i += a;
	while (i < 0) i += BOARD_WIDTH;
	while (i >= BOARD_WIDTH) i -= BOARD_WIDTH;
	return i;
}

/* add to a height index, wrapping around */

int yadd (int i, int a) {
	i += a;
	while (i < 0) i += BOARD_HEIGHT;
	while (i >= BOARD_HEIGHT) i -= BOARD_HEIGHT;
	return i;
}

/* return the number of on cells adjacent to the i,j cell */

int adjacent_to (int board[][BOARD_HEIGHT], int i, int j) {
	int	k, l, count;

	count = 0;

	/* go around the cell */

	for (k=-1; k<=1; k++) for (l=-1; l<=1; l++)

		/* only count if at least one of k,l isn't zero */

		if (k || l)
			if (board[xadd(i,k)][yadd(j,l)]) count++;
	return count;
}

void play (int board[][BOARD_HEIGHT]) {
/*
	(copied this from some web page, hence the English spellings...)

	1.STASIS : If, for a given cell, the number of on neighbours is 
	exactly two, the cell maintains its status quo into the next 
	generation. If the cell is on, it stays on, if it is off, it stays off.

	2.GROWTH : If the number of on neighbours is exactly three, the cell 
	will be on in the next generation. This is regardless of the cell's 		current state.

	3.DEATH : If the number of on neighbours is 0, 1, 4-8, the cell will 
	be off in the next generation.
*/
	int	i, j, a, newboard[BOARD_WIDTH][BOARD_HEIGHT];

	/* for each cell, apply the rules of Life */

	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++) {
		a = adjacent_to (board, i, j);
		if (a == 2) newboard[i][j] = board[i][j];
		if (a == 3) newboard[i][j] = 1;
		if (a < 2) newboard[i][j] = 0;
		if (a > 3) newboard[i][j] = 0;
	}

	/* copy the new board back into the old board */

	for (i=0; i<BOARD_WIDTH; i++) for (j=0; j<BOARD_HEIGHT; j++) {
		board[i][j] = newboard[i][j];
	}
}

int row_line(){
	printf("\n");
	for(int i=0; i<BOARD_WIDTH; i++){printf(" -----");}
	printf("\n");
}

/* print the life board */



void print (int board[][BOARD_HEIGHT]) {
	int	i, j;
	
	row_line();
	for(j=0; j<BOARD_HEIGHT; j++){
		printf(":");
		for(i=0;i<BOARD_WIDTH;i++){
			printf("  %c  :",board[i][j] ? '1' : '0');
		}
		row_line();
	}

	/* for each row */
	/*
	for (j=0; j<BOARD_HEIGHT; j++) {

		

		for (i=0; i<BOARD_WIDTH; i++) {
			//printf ("%c", board[i][j] ? 'x' : ' ');
			printf ("%c", board[i][j] ? 'x' : 'o');
		}

		

		printf ("\n");
	}
	*/
}


/* read a file into the life board */

void read_file (int board[][BOARD_HEIGHT], char *name) {
	FILE	*f;
	int	i, j;
	char s[100];

	f = fopen (name, "r");
	for (j=0; j<BOARD_HEIGHT; j++) {

		/* get a string */

		fgets (s, 100, f);

		/* copy the string to the life board */

		for (i=0; i<BOARD_WIDTH; i++) {
			board[i][j] = s[i] == 'x';
		}
	}
	fclose (f);
}
