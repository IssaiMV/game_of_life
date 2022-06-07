/**
 * Game Of Life
 *
 * Gasca Molinero Jan Mario
 * Mendoza Vazquez Issai Neftaly
 *
 * */
#include <unistd.h>
#include <string.h>

#include "game_of_life.h"
#define game_of_life_h

int main(int argc, char const *argv[])
{
    int board[WIDTH][HEIGHT];
    int num_generation = 0;
    init(board);
    read_file(board);
    puts("\033[H\033[J");
    print(board, "First Generation");
    play(board);
    sleep(2);
    puts("\033[H\033[J");
    do
    {
        print(board, "Next Generation:");
        play(board);
        num_generation++;
        sleep(1);
        puts("\033[H\033[J");
    } while (isAllDead(board) != 1);

    return 0;
}
