/**
 * Game Of Life
 *
 * Gasca Molinero Jan Mario
 * Mendoza Vazquez Issai Neftaly
 *
 * */
#include <unistd.h>

#include "game_of_life.h"
#define game_of_life_h

int main(int argc, char const *argv[])
{

    if (argc < 6){
        menu();
        return 0;
    }
    int rows, columns, mode, view, times;
    rows = atoi(argv[1]);
    columns = atoi(argv[2]);
    mode = atoi(argv[3]);
    view = atoi(argv[4]);
    times = atoi(argv[5]);
    if (rows <= 0 && columns <= 0){
        printf("Dimensiones del tablero no permitidas");
        return 0;
    }

    if (mode < 1 || mode > 2){
        printf("Modo de operación incorrecto, solo permite 1 o 2");
        return 0;
    }

    if (view < 1 || view > 2){
        printf("Visualizacion de los instantes incorrecto, solo permite 1 o 2");
        return 0;
    }

    if (times < 0){
        printf("Numero de instantes incorrecto, solo permite numeros mayor o igual a 0");
        return 0;
    }

    srand(time(NULL));
    Game_Of_Life game_of_life;
    game_of_life.generation = 0;
    game_of_life.table.rows = rows;
    game_of_life.table.columns = columns;

    init(&game_of_life.table, mode);

    if (mode != 1)
        read_file(&game_of_life.table);

    puts("\033[H\033[J");
    print_table(&game_of_life.table, "First Generation", game_of_life.generation);
    play(&game_of_life);
    
    if (view == 2){
    pause_game();
    }else{
        sleep(2);
    }
    puts("\033[H\033[J");
    do{
        puts("\033[H\033[J");
        print_table(&game_of_life.table, "Next Generation:", game_of_life.generation);
        play(&game_of_life);
        if (view == 2){
            pause_game();
        }else{
            sleep(2);
        }

        
    } while (is_all_dead(&game_of_life.table) != 1 && is_all_moments(&game_of_life, times) != 0);

    return 0;
}
