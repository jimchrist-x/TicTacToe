#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "functions.h"
#include "colors.h"
bool initPlayers(PLAYER *player1, PLAYER *player2)
{
    system(clear);
    do
    {
        printf(PURPLE_BOLD);
        printf("Player 1 name: ");
        printf(GREEN);
        fgets(player1->name, PLAYER_NAME_SIZE, stdin);
        printf(PURPLE_BOLD);
        printf("Player 2 name: ");
        printf(GREEN);
        fgets(player2->name, PLAYER_NAME_SIZE, stdin);
        if (!strcmp(player1->name, player2->name))
        {
            printf(RED_BOLD);
            printf("Names must be different!\n");
            printf(RESET_COLORS);
        }
    } while (!strcmp(player1->name, player2->name));
    removeNewline(player1->name, PLAYER_NAME_SIZE);
    removeNewline(player2->name, PLAYER_NAME_SIZE);
    printf(PURPLE_BOLD);
    printf("%s choose your weapon, X or 0:", player1->name);
    printf(GREEN);
    scanf("%c", &player1->weapon);
    clear_stdin();
    printf(RESET_COLORS);
    player1->weapon = upper(player1->weapon);
    if (player1->weapon == 'X')
    {
        player2->weapon = '0';
    }
    else
    {
        player1->weapon = '0';
        player2->weapon = 'X';
    }
    player1->score = 0;
    player2->score = 0;
    return TRUE;
}

bool removeNewline(unsigned char *buffer, int size)
{
    for (short int elem = 0; elem < size; elem++)
    {
        if (buffer[elem] == '\n')
        {
            buffer[elem] = '\0';
            return TRUE;
        }
        if (buffer[elem] == '\0')
        {
            return FALSE;
        }
    }
    return FALSE;
}
void clear_stdin(void)
{
    char character;
    while ((character = getchar()) != EOF && character != '\n')
        ;
}
char upper(char c)
{
    if (c > 'a' && c < 'z')
        return c - 32;
}
unsigned short int startMenu(void)
{
    unsigned short int option;
    system(clear);
    printf(BLUE_BACKGROUND);
    printf(WHITE_BOLD);
    printf("  ___                 ___  \n");
    printf(" (o o)               (o o) \n");
    printf("(  V  ) Tic Tac Toe (  V  )\n");
    printf("--m-m-----------------m-m--\n");
    printf(RESET_COLORS);
    printf(YELLOW);
    printLine(LINE_SIZE);
    printf(PURPLE_BOLD);
    printf("1.PLAY\n");
    printf("2.GAME RECORD\n");
    printf("3.HELP\n");
    printf("4.EXIT\n");
    do
    {
        printf("?");
        printf(GREEN);
        scanf("%hu", &option);
        clear_stdin();
        printf(RESET_COLORS);
    } while (option > USHRT_MAX || option < 0);
    return option;
}
void printLine(int size)
{
    for (int num = 0; num < size; num++)
        printf("═");
    printf("\n");
}
unsigned short int gameloop(PLAYER *player1, PLAYER *player2, char **board, int rows, int columns)
{
    bool runningMain = TRUE, running;
    int turn, previousTurn;
    int option, total_turns = 0;
    int *used_options;
    char play_again;
    while (runningMain)
    {
        system(clear);
        running = TRUE;
        turn = 1;
        total_turns = 0;
        used_options = malloc(sizeof(int) * (rows * columns));
        if (!used_options)
        {
            fprintf(stderr, RED_BOLD);
            fprintf(stderr, "Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        board[0][0] = '1';
        board[0][1] = '2';
        board[0][2] = '3';
        board[1][0] = '4';
        board[1][1] = '5';
        board[1][2] = '6';
        board[2][0] = '7';
        board[2][1] = '8';
        board[2][2] = '9';
        while (running)
        {
            printBoard(board);
            if (turn == 1)
            {
                do
                {
                    if (player1->weapon == 'X')
                    {
                        printf("It is %s's turn: ", player1->name);
                        scanf("%d", &option);
                        clear_stdin();
                    }
                    else
                    {
                        printf("It is %s's turn: ", player2->name);
                        scanf("%d", &option);
                        clear_stdin();
                    }
                    for (int elem = 0; elem < total_turns; elem++)
                    {
                        if (used_options[elem] == option)
                        {
                            option = -1;
                        }
                    }
                } while (option > 9 || option < 1);
                previousTurn = turn;
                turn = 2;
            }
            else
            {
                do
                {
                    if (player1->weapon == '0')
                    {
                        printf("It is %s's turn: ", player1->name);
                        scanf("%d", &option);
                        clear_stdin();
                    }
                    else
                    {
                        printf("It is %s's turn: ", player2->name);
                        scanf("%d", &option);
                        clear_stdin();
                    }
                    for (int elem = 0; elem < total_turns; elem++)
                    {
                        if (used_options[elem] == option)
                        {
                            option = -1;
                        }
                    }
                } while (option > 9 || option < 1);
                previousTurn = turn;
                turn = 1;
            }
            used_options[total_turns] = option;
            if (previousTurn == 1)
            {
                option == 1 ? board[0][0] = 'X' : FALSE;
                option == 2 ? board[0][1] = 'X' : FALSE;
                option == 3 ? board[0][2] = 'X' : FALSE;
                option == 4 ? board[1][0] = 'X' : FALSE;
                option == 5 ? board[1][1] = 'X' : FALSE;
                option == 6 ? board[1][2] = 'X' : FALSE;
                option == 7 ? board[2][0] = 'X' : FALSE;
                option == 8 ? board[2][1] = 'X' : FALSE;
                option == 9 ? board[2][2] = 'X' : FALSE;
                total_turns++;
            }
            else
            {
                option == 1 ? board[0][0] = '0' : FALSE;
                option == 2 ? board[0][1] = '0' : FALSE;
                option == 3 ? board[0][2] = '0' : FALSE;
                option == 4 ? board[1][0] = '0' : FALSE;
                option == 5 ? board[1][1] = '0' : FALSE;
                option == 6 ? board[1][2] = '0' : FALSE;
                option == 7 ? board[2][0] = '0' : FALSE;
                option == 8 ? board[2][1] = '0' : FALSE;
                option == 9 ? board[2][2] = '0' : FALSE;
                total_turns++;
            }
            if (checkforwin(board, rows, columns))
            {
                printBoard(board);
                if (previousTurn == 1)
                {
                    if (player1->weapon == 'X')
                    {
                        player1->score++;
                        printf("%s won! Score is : %d | %d\n", player1->name, player1->score, player2->score);
                    }
                    else
                    {
                        player2->score++;
                        printf("%s won! Score is : %d | %d\n", player2->name, player1->score, player2->score);
                    }
                }
                else
                {
                    if (player1->weapon == '0')
                    {
                        player1->score++;
                        printf("%s won! Score is : %d | %d\n", player1->name, player2->score, player1->score);
                    }
                    else
                    {
                        player2->score++;
                        printf("%s won! Score is : %d | %d\n", player2->name, player2->score, player1->score);
                    }
                }
                running = FALSE;
                printf("%sPlay again %s(%sY%s/%sN%s)? ", YELLOW_BOLD, RESET_COLORS, GREEN_BOLD_INTENSE, RESET_COLORS, RED_BOLD_INTENSE, RESET_COLORS);
                scanf("%c", &play_again);
                clear_stdin();
                play_again = upper(play_again);
                if (play_again == 'Y')
                    runningMain = TRUE;
                else
                    runningMain = FALSE;
            }
            else if (total_turns == (rows * columns))
            {
                printBoard(board);
                printf(YELLOW_BOLD_INTENSE);
                printf("Game is a draw!\n");
                running = FALSE;
                printf("%sPlay again %s(%sY%s/%sN%s)? ", YELLOW_BOLD, RESET_COLORS, GREEN_BOLD_INTENSE, RESET_COLORS, RED_BOLD_INTENSE, RESET_COLORS);
                scanf("%c", &play_again);
                clear_stdin();
                play_again = upper(play_again);
                if (play_again == 'Y')
                    runningMain = TRUE;
                else
                    runningMain = FALSE;
            }
        }
        free(used_options);
    }
}
bool checkforwin(char **board, int rows, int columns)
{
    for (int row = 0; row < rows; row++)
    {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2])
            return TRUE;
    }
    for (int col = 0; col < columns; col++)
    {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col])
            return TRUE;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return TRUE;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return TRUE;
    return FALSE;
}
void pauseTerm(void)
{
    printf("%sTerminal Paused... %sPress ENTER to continue...%s\n", YELLOW_BOLD, GREEN_BOLD, RESET_COLORS);
    getchar();
}
void printBoard(char **board)
{
    system(clear);
    printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡆⠀⠀⠀⠀⠀⠀⠀⠀⣾⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n", BOARD_COLOR);
    printf("      %s%c%s  %s⢸⡇⠀⠀⠀%s%c%s    %s⣿⡇  %s%c%s          \n", BOARD_COLOR_LETTERS, board[0][0], RESET_COLORS, BOARD_COLOR, BOARD_COLOR_LETTERS, board[0][1], RESET_COLORS, BOARD_COLOR, BOARD_COLOR_LETTERS, board[0][2], RESET_COLORS);
    printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n", BOARD_COLOR);
    printf("⠀⠀⢀⣀⣀⣀⣀⣀⣀⣸⣇⣀⣀⣀⣀⣀⣀⣀⣀⣿⣇⣀⣀⣀⣀⣀⣀⡀⠀⠀   \n");
    printf("⠀⠀⠙⠛⠛⠛⠛⠛⠛⢻⡟⠛⠛⠛⠛⠛⠛⠛⠛⣿⡟⠛⠛⠛⠛⠛⠛⠃⠀⠀   \n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf("      %s%c%s  %s⢸⡇   %s%c%s    %s⣿⡇  %s%c%s         \n", BOARD_COLOR_LETTERS, board[1][0], RESET_COLORS, BOARD_COLOR, BOARD_COLOR_LETTERS, board[1][1], RESET_COLORS, BOARD_COLOR, BOARD_COLOR_LETTERS, board[1][2], RESET_COLORS);
    printf("%s⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n", BOARD_COLOR);
    printf("⠀⠀⢀⣀⣀⣀⣀⣀⣀⣸⣇⣀⣀⣀⣀⣀⣀⣀⣀⣿⣇⣀⣀⣀⣀⣀⣀⡀⠀⠀   \n");
    printf("⠀⠀⠈⠉⠉⠉⠉⠉⠉⢹⡏⠉⠉⠉⠉⠉⠉⠉⠉⣿⡏⠉⠉⠉⠉⠉⠉⠁⠀⠀   \n");
    printf("      %s%c%s  %s⢸⡇   %s%c%s    %s⣿⡇⠀ %s%c%s           \n", BOARD_COLOR_LETTERS, board[2][0], RESET_COLORS, BOARD_COLOR, BOARD_COLOR_LETTERS, board[2][1], RESET_COLORS, BOARD_COLOR, BOARD_COLOR_LETTERS, board[2][2], RESET_COLORS);
    printf("⠀%s⠀⠀⠀⠀⠀⠀⠀⠀⢸⡇⠀⠀⠀⠀⠀⠀⠀⠀⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n", BOARD_COLOR);
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠸⠇⠀⠀⠀⠀⠀⠀⠀⠀⢿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀   \n");
    printf(RESET_COLORS);
}
bool fileExists(char *filename)
{
    FILE *file;
    file=fopen(filename, "rb");
    if (file)
    {
        fclose(file);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void recordWrite(FILE **recordFile, PLAYER player1, PLAYER player2)
{
    fwrite(&player1, sizeof(PLAYER), 1, *recordFile);
    fwrite(&player2, sizeof(PLAYER), 1, *recordFile);
}
void recordRead(FILE *recordFile, PLAYER *player1, PLAYER *player2)
{
    fread(player1, sizeof(PLAYER), 1, recordFile);
    fread(player2, sizeof(PLAYER), 1, recordFile);
}
unsigned short int gameMenu(void) {
    system(clear);
    unsigned short int option;
    printf(PURPLE_BOLD);
    printf("1. Human VS Human\n");
    printf("2. Human VS Bot\n");
    do
    {
        printf("?");
        printf(GREEN);
        scanf("%hu", &option);
        clear_stdin();
        printf(RESET_COLORS);
    } while (option > USHRT_MAX || option < 0);
    return option;
}
bool initPlayer(PLAYER *player1, PLAYER *Bot)
{
    system(clear);
    do
    {
        printf(PURPLE_BOLD);
        printf("Player name: ");
        printf(GREEN);
        fgets(player1->name, PLAYER_NAME_SIZE, stdin);
        strcpy(Bot->name, "Bot");
        if (!strcmp(player1->name, Bot->name))
        {
            printf(RED_BOLD);
            printf("Player's name shouldn't be Bot!\n");
            printf(RESET_COLORS);
        }
    } while (!strcmp(player1->name, Bot->name));
    removeNewline(player1->name, PLAYER_NAME_SIZE);
    printf(PURPLE_BOLD);
    printf("%s choose your weapon, X or 0:", player1->name);
    printf(GREEN);
    scanf("%c", &player1->weapon);
    clear_stdin();
    printf(RESET_COLORS);
    player1->weapon = upper(player1->weapon);
    if (player1->weapon == 'X')
    {
        Bot->weapon = '0';
    }
    else
    {
        player1->weapon = '0';
        Bot->weapon = 'X';
    }
    player1->score = 0;
    Bot->score = 0;
    return TRUE;
}
unsigned short int gameBotloop(PLAYER *player1, PLAYER *Bot, char **board, int rows, int columns)
{
    bool runningMain = TRUE, running;
    int turn, previousTurn;
    int option, total_turns = 0;
    int *used_options;
    char play_again;
    while (runningMain)
    {
        system(clear);
        running = TRUE;
        turn = 1;
        total_turns = 0;
        used_options = malloc(sizeof(int) * (rows * columns));
        if (!used_options)
        {
            fprintf(stderr, RED_BOLD);
            fprintf(stderr, "Error allocating memory!\n");
            exit(EXIT_FAILURE);
        }
        board[0][0] = '1';
        board[0][1] = '2';
        board[0][2] = '3';
        board[1][0] = '4';
        board[1][1] = '5';
        board[1][2] = '6';
        board[2][0] = '7';
        board[2][1] = '8';
        board[2][2] = '9';
        while (running)
        {
            printBoard(board);
            if (turn == 1)
            {
                do
                {
                    if (player1->weapon == 'X')
                    {
                        printf("It is %s's turn: ", player1->name);
                        scanf("%d", &option);
                        clear_stdin();
                    }
                    else
                    {
                        option=botLogic(used_options, option, total_turns, board, rows, columns);
                    }
                    for (int elem = 0; elem < total_turns; elem++)
                    {
                        if (used_options[elem] == option)
                        {
                            option = -1;
                        }
                    }
                } while (option > 9 || option < 1);
                previousTurn = turn;
                turn = 2;
            }
            else
            {
                do
                {
                    if (player1->weapon == '0')
                    {
                        printf("It is %s's turn: ", player1->name);
                        scanf("%d", &option);
                        clear_stdin();
                    }
                    else
                    {
                        option=botLogic(used_options, option, total_turns, board, rows, columns);

                    }
                    for (int elem = 0; elem < total_turns; elem++)
                    {
                        if (used_options[elem] == option)
                        {
                            option = -1;
                        }
                    }
                } while (option > 9 || option < 1);
                previousTurn = turn;
                turn = 1;
            }
            used_options[total_turns] = option;
            if (previousTurn == 1)
            {
                option == 1 ? board[0][0] = 'X' : FALSE;
                option == 2 ? board[0][1] = 'X' : FALSE;
                option == 3 ? board[0][2] = 'X' : FALSE;
                option == 4 ? board[1][0] = 'X' : FALSE;
                option == 5 ? board[1][1] = 'X' : FALSE;
                option == 6 ? board[1][2] = 'X' : FALSE;
                option == 7 ? board[2][0] = 'X' : FALSE;
                option == 8 ? board[2][1] = 'X' : FALSE;
                option == 9 ? board[2][2] = 'X' : FALSE;
                total_turns++;
            }
            else
            {
                option == 1 ? board[0][0] = '0' : FALSE;
                option == 2 ? board[0][1] = '0' : FALSE;
                option == 3 ? board[0][2] = '0' : FALSE;
                option == 4 ? board[1][0] = '0' : FALSE;
                option == 5 ? board[1][1] = '0' : FALSE;
                option == 6 ? board[1][2] = '0' : FALSE;
                option == 7 ? board[2][0] = '0' : FALSE;
                option == 8 ? board[2][1] = '0' : FALSE;
                option == 9 ? board[2][2] = '0' : FALSE;
                total_turns++;
            }
            if (checkforwin(board, rows, columns))
            {
                printBoard(board);
                if (previousTurn == 1)
                {
                    if (player1->weapon == 'X')
                    {
                        player1->score++;
                        printf("%s won! Score is : %d | %d\n", player1->name, player1->score, Bot->score);
                    }
                    else
                    {
                        Bot->score++;
                        printf("%s won! Score is : %d | %d\n", Bot->name, player1->score, Bot->score);
                    }
                }
                else
                {
                    if (player1->weapon == '0')
                    {
                        player1->score++;
                        printf("%s won! Score is : %d | %d\n", player1->name, Bot->score, player1->score);
                    }
                    else
                    {
                        Bot->score++;
                        printf("%s won! Score is : %d | %d\n", Bot->name, Bot->score, player1->score);
                    }
                }
                running = FALSE;
                printf("%sPlay again %s(%sY%s/%sN%s)? ", YELLOW_BOLD, RESET_COLORS, GREEN_BOLD_INTENSE, RESET_COLORS, RED_BOLD_INTENSE, RESET_COLORS);
                scanf("%c", &play_again);
                clear_stdin();
                play_again = upper(play_again);
                if (play_again == 'Y')
                    runningMain = TRUE;
                else
                    runningMain = FALSE;
            }
            else if (total_turns == (rows * columns))
            {
                printBoard(board);
                printf(YELLOW_BOLD_INTENSE);
                printf("Game is a draw!\n");
                running = FALSE;
                printf("%sPlay again %s(%sY%s/%sN%s)? ", YELLOW_BOLD, RESET_COLORS, GREEN_BOLD_INTENSE, RESET_COLORS, RED_BOLD_INTENSE, RESET_COLORS);
                scanf("%c", &play_again);
                clear_stdin();
                play_again = upper(play_again);
                if (play_again == 'Y')
                    runningMain = TRUE;
                else
                    runningMain = FALSE;
            }
        }
        free(used_options);
    }
}
unsigned short int botLogic(int *used_options, int option, int total_turns, char **board, int rows, int columns) {
    int right=option+1, left=option-1, above=option-columns, below=option+columns;
    bool middle=FALSE;
    unsigned char sos_choice;
    unsigned short int sos_option=0;

    for (int row = 0; row < rows; row++)
    {
        if (board[row][0] == board[row][1]) {
            sos_choice=board[row][2];
            if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
                break;
            }
        }
        if (board[row][1] == board[row][2]) {
            sos_choice=board[row][0];
            if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
                break;
            }
        }
        if (board[row][0] == board[row][2]) {
            sos_choice=board[row][1];
            if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
                break;
            }
        }
    }
    for (int col = 0; col < columns; col++)
    {
        if (board[0][col] == board[1][col]) {
            sos_choice=board[2][col];
            if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
                break;
            }
        }
            
        if (board[1][col] == board[2][col]) {
            sos_choice=board[0][col];
            if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
                break;
            }
        }
        if (board[0][col] == board[2][col]) {
            sos_choice=board[1][col];
            if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
                break;
            }
        }
    }
    if (board[0][0] == board[1][1])
        sos_choice=board[2][2];
        if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
            }
    if(board[1][1] == board[2][2])
        sos_choice=board[0][0];
        if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
            }

    if (board[0][2] == board[1][1])
        sos_choice=board[2][0];
        if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
            }
    if (board[1][1] == board[2][0])
        sos_choice=board[0][2];
        if (sos_choice!='X' && sos_choice!='0') {
                sos_option=atoi(&sos_choice);
            }
    printf("|%c|",sos_choice);
    for (short int elem=0;elem<total_turns;elem++) {
        if (right==used_options[elem]) {
            right=0;
        }
        if (left==used_options[elem]) {
            left=0;
        }
        if (above==used_options[elem]) {
            above=0;
        }
        if (below==used_options[elem]) {
            below=0;
        }
        if (5==used_options[elem]) {
            middle=TRUE;
        }
        if (sos_option==used_options[elem]) {
            sos_option=0;
        }
    }
    // Using the right, left, above, below technique
    if (!middle) {
        return 5;
    }
    if (sos_option) {
        return sos_option;
    }
    if (right && option%3) {
        return right;
    }
    if (left && (option+2)%3) {
        return left;
    }
    if (above) {
        return above;
    }
    if (below) {
        return below;
    }
}