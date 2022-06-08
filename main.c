/**
 * Game Of Life
 *
 * Gasca Molinero Jan Mario
 * Mendoza Vazquez Issai Neftaly
 *
 * */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "game_of_life.h"
#define game_of_life_h

int main(int argc, char const *argv[]){
    
    
    Game_Of_Life game_of_life;
    game_of_life.generation = 0;
    
    game_of_life.table.columns = WIDTH;
    game_of_life.table.rows = HEIGHT;


    //int board[WIDTH][HEIGHT];
    //int num_generation = 0;
    init(&game_of_life.table);
    read_file(&game_of_life.table);
    puts("\033[H\033[J");
    print_table(&game_of_life.table, "First Generation");
    play(&game_of_life.table);
    sleep(2);
    puts("\033[H\033[J");
    //print_table(&game_of_life.table, "First Generation");
    //exit(1);

    do{
        print_table(&game_of_life.table, "Next Generation:");
        play(&game_of_life.table);
        game_of_life.generation++;
        //num_generation++;
        sleep(1);
        puts("\033[H\033[J");
    } while (isAllDead(&game_of_life.table) != 1);

    return 0;
}
