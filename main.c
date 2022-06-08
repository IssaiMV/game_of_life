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

    if (argc < 4)
    {
        printf("Recuerda que debes de mandar los siguientes parametros './eject tam_filas tam_columnas modo'\n");
        printf("1.- Tamaño de filas\n");
        printf("2.- Tamaño de columnas\n");
        printf("3.- Modo de operación\n");
        printf("\t1.-Células aleatorias\n");
        printf("\t2.-Células cargadas por archivo data.txt\n");
        return 0;
    }
    int rows, columns, mode;
    rows = atoi(argv[1]);
    columns = atoi(argv[2]);
    mode = atoi(argv[3]);
    if (rows <= 0 && columns <= 0)
    {
        printf("Dimensiones del tablero no permitidas");
        return 0;
    }
    if (mode < 1 || mode > 2)
    {
        printf("Modo de operación incorrecto, solo permite 1 o 2");
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
    sleep(2);
    puts("\033[H\033[J");
    do
    {
        print_table(&game_of_life.table, "Next Generation:", game_of_life.generation);
        play(&game_of_life);
        sleep(1);
        puts("\033[H\033[J");
    } while (is_all_dead(&game_of_life.table) != 1);

    return 0;
}
