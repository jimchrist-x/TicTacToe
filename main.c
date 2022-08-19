#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "functions.h"
int main(int argc, char const *argv[])
{
    bool running = TRUE;
    PLAYER player1;
    PLAYER player2;
    char **board;
    int rows = 3, columns = 3;
    FILE *recordFile;
    while (running)
    {
        switch (startMenu())
        {
        case 1:
            initPlayers(&player1, &player2);
            board = malloc(rows * sizeof(unsigned char *));
            if (!board)
            {
                fprintf(stderr, "Error allocating memory!\n");
                exit(EXIT_FAILURE);
            }
            for (int row = 0; row < rows; row++)
            {
                board[row] = malloc(columns * sizeof(unsigned char));
                if (!board[row])
                {
                    fprintf(stderr, "Error allocating memory!\n");
                    exit(EXIT_FAILURE);
                }
            }
            gameloop(&player1, &player2, board, rows, columns);
            recordFile = fopen(RECORD_FILENAME, "ab");
            recordWrite(&recordFile, player1, player2);
            fclose(recordFile);
            for (int row = 0; row < rows; row++)
            {
                free(board[row]);
            }
            free(board);
            break;
        case 2:
            if (fileExists(RECORD_FILENAME))
            {
                recordFile = fopen(RECORD_FILENAME, "rb");
                while (TRUE)
                {
                    recordRead(recordFile, &player1, &player2);
                    if (feof(recordFile))
                    {
                        break;
                    }
                    printf("%s (%c) VS %s (%c) | %d : %d\n", player1.name, player1.weapon, player2.name, player2.weapon, player1.score, player2.score);
                }
                fclose(recordFile);
                pauseTerm();
            }
            else
            {
                printf("No records found!");
                pauseTerm();
            }
            break;
        case 3:
            system(web);
            break;
        case 4:
            printf("See ya!\n");
            running = FALSE;
            break;
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
}
