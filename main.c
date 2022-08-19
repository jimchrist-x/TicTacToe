#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "functions.h"
#include "colors.h"
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
                fprintf(stderr, RED_BOLD);
                fprintf(stderr, "Error allocating memory!\n");
                exit(EXIT_FAILURE);
            }
            for (int row = 0; row < rows; row++)
            {
                board[row] = malloc(columns * sizeof(unsigned char));
                if (!board[row])
                {
                    fprintf(stderr, RED_BOLD);
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
                    printf("%s%s %s(%s%c%s) %sVS %s%s %s(%s%c%s) | %s%d : %s%d\n", GREEN_BOLD,player1.name, RESET_COLORS, PURPLE_BOLD,player1.weapon, RESET_COLORS, YELLOW_BOLD, GREEN_BOLD, player2.name, RESET_COLORS, PURPLE_BOLD, player2.weapon, RESET_COLORS, RED_BOLD, player1.score, RED_BOLD, player2.score);
                }
                fclose(recordFile);
                printf(RESET_COLORS);
                pauseTerm();
            }
            else
            {
                printf(RED_BOLD);
                printf("No records found!");
                printf(RESET_COLORS);
                pauseTerm();
            }
            break;
        case 3:
            system(web);
            break;
        case 4:
            printf(CYAN_BOLD);
            printf("See ya!\n");
            printf(RESET_COLORS);
            running = FALSE;
            break;
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
}
