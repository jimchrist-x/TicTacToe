#ifndef __FUNCS__
#define __FUNCS__
#define TRUE 1
#define FALSE 0
#define PLAYER_NAME_SIZE 50
#define LINE_SIZE 30
#define RECORD_FILENAME "records.bin"
#define BOARD_COLOR RED_BOLD_INTENSE
#define BOARD_COLOR_LETTERS GREEN_BOLD_INTENSE
#ifdef _WIN32
#define clear "cls"
#define web "start https://www.wikihow.com/Play-Tic-Tac-Toe"
#else
#define clear "clear"
#define web "xdg-open https://www.wikihow.com/Play-Tic-Tac-Toe"
#endif
struct player
{
    int score;
    unsigned char name[PLAYER_NAME_SIZE];
    char weapon;
};
typedef struct player PLAYER;
bool initPlayers(PLAYER *player1, PLAYER *player2);
bool removeNewline(unsigned char *buffer, int size);
void clear_stdin(void);
char upper(char c);
unsigned short int startMenu(void);
void printLine(int size);
unsigned short int gameloop(PLAYER *player1, PLAYER *player2, char **board, int rows, int columns);
bool checkforwin(char **board, int rows, int columns);
void pauseTerm(void);
void printBoard(char **board);
bool fileExists(char *filename);
void recordWrite(FILE **recordFile, PLAYER player1, PLAYER player2);
void recordRead(FILE *recordFile, PLAYER *player1, PLAYER *player2);
unsigned short int gameMenu(void);
bool initPlayer(PLAYER *player1, PLAYER *Bot);
unsigned short int gameBotloop(PLAYER *player1, PLAYER *Bot, char **board, int rows, int columns);
unsigned short int botLogic(int *used_options, int option, int total_turns, char **board, int rows, int columns);
#endif