#ifndef game_of_life_h
#define game_of_life_h
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct struct_cell
{
    int is_alive;
    int counter_neighbor;

} Cell;

typedef struct struct_table
{
    Cell **table_of_cell;
    int rows;
    int columns;

} Table;

typedef struct struct_game
{
    Table table;
    int generation;
} Game_Of_Life;

int get_random();
/**
 * Dashboard starts with zero values
 */
void init(Table *board, int mode);
/**
 *  add to a width index, wrapping around like a cylinder
 */
int xadd(int i, int a, int rows);
/**
 *  add to a height index, wrapping around
 */
int yadd(int i, int a, int columns);
/**
 *  count the number of on cells adjacent to the i,j cell
 */
void adjacent_to(Table *board, int i, int j);
/**
 * Play game of life
 */
void play(Game_Of_Life *game);
/**
 * Add a line in printf
 */
int row_line(int columns);
/**
 * print the life board
 */
void print_table(Table *board, char message[], int generation);
/**
 * read a file into the life board
 */
void read_file(Table *board);

int is_all_dead(Table *board);
#include "game_of_life.c"
#endif
